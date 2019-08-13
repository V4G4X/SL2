#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define FILENAME "buffer.bin"

// Resources & Semaphores to be Used
int readcount = 0; // Total no. of Readers active
sem_t wrt;         // Semaphore for Writers
pthread_mutex_t
    mutex; // Mutex to to make "readcount" operations as critical sections

// Buffer Variables
FILE *FileWriter;      // File Pointer that will be Writing onto Buffer
FILE *(FileReader[3]); // File Pointer(s) that will reading from Buffer
int readCensus = 3;

void writer() {
  while (1) {
    sem_wait(&wrt);
    printf("Writer Critical Section Start\n");

    // Write into file
    int r;
    for (r = rand() % 10; r > 0; r--)
      fprintf(FileWriter, "%c", (rand() % 26) + 65);
    printf("Wrote into File\n");

    printf("Writer Critical Section End\n");
    sem_post(&wrt);
    sleep(rand() % 3);
  }
}

void reader(void *n) {
  int i = *(int *)n;
  printf("Reader no: %d\n", i);
  while (1) {
    // Establish an increment in Reader Queue
    pthread_mutex_lock(&mutex);
    printf("Incrementing readcount\n");
    readcount++;
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
    for (r = rand() % 5; r > 0; r--) {
      c = getc(FileReader[i]);
      if (c == EOF) {
        printf("Reader[%d] reached EOF\n", i);
        break;
      }
      putchar(c);
    }
    printf("Read from File\n");

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
    sleep(rand() % 2);
  }
}

int main(int argc, char const *argv[]) {
  // Initialising Semaphores and MUTEXs
  sem_init(&wrt, 0, 1);
  pthread_mutex_init(&mutex, NULL);

  // Initialising FILE pointers
  FileWriter = fopen(FILENAME, "a");

  pthread_t writers[3];
  pthread_t readers[5];
  int i;
  void *j[3];
  for (i = 0; i < 5; i++) {
    pthread_create(&writers[i], NULL, (void *)writer, NULL);
  }
  for (i = 0; i < 3; i++) {
    FileReader[i] = fopen(FILENAME, "r");
    j[i] = (void *)&i;
    pthread_create(&readers[i], NULL, (void *)reader, j[i]);
  }
  while (1) {
  }
  return 0;
}
