#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Resources & Semaphores to be Used
int readcount = 0; // Total no. of Readers active
sem_t wrt;         // Semaphore for Writers
pthread_mutex_t
    mutex; // Mutex to to make "readcount" operations as critical sections

// Buffer Variables
char buffer[33110];
int writePos = 0;
int readerPos[5];
int readCensus = 3;

void writer() {
  while (1) {
    sem_wait(&wrt);
    printf("Writer Critical Section Start\n");

    // Write into buffer
    int r;
    for (r = rand() % 19 + 1; r > 0; r--) {
      writePos = (writePos + 1) % 33110;
      // if (writePos == 33110)
      //   printf("The Buffer is Full. The Writer can't write no more\n");
      buffer[writePos] = (rand() % 26) + 65;
    }
    printf("Wrote into File\n");

    printf("Writer Critical Section End\n");
    sem_post(&wrt);
    sleep(rand() % 2 + 1);
  }
}

void reader(void *n) {
  int i = *(int *)n;
  readerPos[i] = 0;
  printf("Reader no: %d\n", i);
  while (1) {
    // Establish an increment in Reader Queue
    pthread_mutex_lock(&mutex);
    readcount++;
    printf("Incrementing readcount\n");
    if (readcount == 1) {
      // If first reader, wait the Writer
      sem_wait(&wrt);
      printf("Locking \"wrt\" from Reader\n");
    }
    pthread_mutex_unlock(&mutex);

    // Read from File
    printf("Reader[%d] now reading\n", i);
    int r;
    char c;
    for (r = rand() % 4 + 1; r > 0; r--) {
      c = buffer[readerPos[i]];
      printf("%c", c);
      readerPos[i]++;
      if (readerPos[i] == writePos) {
        printf("\nReader[%d] reached End of Buffer\n", i);
        break;
      }
    }
    printf("\nReader[%d] Read from File\n",i);

    // Done Reading
    pthread_mutex_lock(&mutex);
    printf("Decrementing readcount\n");
    readcount--;
    if (readcount == 0) {
      // If last reader, post the Writer
      printf("UnLocking \"wrt\" from Reader\n");
      sem_post(&wrt);
    }
    pthread_mutex_unlock(&mutex);
    sleep(rand() % 9 + 1);
  }
}

int main(int argc, char const *argv[]) {
  // Initialising Semaphores and MUTEXs
  sem_init(&wrt, 0, 1);
  pthread_mutex_init(&mutex, NULL);

  pthread_t writers;
  pthread_t readers[5];
  int i;
  void *j[5];
  pthread_create(&writers, NULL, (void *)writer, NULL);
  sleep(5);
  for (i = 0; i < 5; i++) {
    int *p = (int *)malloc(sizeof(int));
    *p = i;
    j[i] = (void *)p;
    pthread_create(&readers[i], NULL, (void *)reader, j[i]);
  }
  while (1) {
  }
  return 0;
}
