#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
// #include <unistd.h>
#define MAX 10

sem_t empty;          // Counting Semaphore to keep track of empty cells
sem_t full;           // Counting Semaphore to keep track of cells with Data
pthread_mutex_t lock; // Mutex/BinarySemaphore to lock and unlock Queue
int array[MAX];
int head = 0;
int tail= 0;

void printQueue(){
    int i=tail;
}

void *produce() {
  while (true) {
    // Generate Value
    int i = rand() % 10;
    sem_wait(&empty);
    pthread_mutex_lock(&lock);
    printf("---------------Beginning of Critical Section---------------\n");
    array[head] = i;
    head = (head+1)%MAX;
    printQueue();
    printf("----------------Ending of Critical Section---------------\n");
    sem_post(&full);
    pthread_mutex_unlock(&lock);
  }
}

int main(int argc, char const *argv[]) {
  pthread_t *producer = NULL;
  pthread_t *consumer = NULL;

  pthread_mutex_init(&lock, NULL);
  sem_init(&empty, 0, MAX);
  sem_init(&full, 0, 0);

  int i = 0;
  printf("Enter the number of Producers you want to create: ");
  scanf("%d", &i);
  producer = (pthread_t *)calloc(sizeof(pthread_t), i);
  printf("Enter the number of Consumers you want to create: ");
  scanf("%d", &i);
  consumer = (pthread_t *)calloc(sizeof(pthread_t), i);

  return 0;
}
