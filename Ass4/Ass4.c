#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define MAX 10

sem_t empty;          // Counting Semaphore to keep track of empty cells
sem_t full;           // Counting Semaphore to keep track of cells with Data
pthread_mutex_t lock; // Mutex/BinarySemaphore to lock and unlock Queue
int array[MAX];       // Data Buffer
int head = 0;         // Variable To keep track of head of Queue
int tail = 0;         // Variable to keep track of tail of Queue

int isEmpty(int array[]) { // Boolean Function, return 1 if queue empty
  if (tail == head) {      // This can either mean queue is either empty or Full
    return 1;              // But this function will only be called by consumers
  }
  return 0;
}

void printQueue() { // Prints the entire Queue fom front to rear
  int i = head;
  while (1) {
    printf("%d\t", array[i]);
    i = (i + 1) % MAX;
    if (i == tail)
      break;
  }
  printf("\n");
}

void *produce() { // Infintite Loop that produces random number between 0-9 and
                  // pushes onto Buffer(Queue)
  while (1) {
    // Generate Value
    int i = rand() % 10;
    sem_wait(&empty);
    pthread_mutex_lock(&lock);
    printf("---------------Beginning of Critical Section of "
           "Producer---------------\n");
    printf("Producers just produced %d\n", i);
    array[tail] = i;
    tail = (tail + 1) % MAX;
    printQueue();
    printf("----------------Ending of Critical Section of "
           "Producer---------------\n\n");
    sleep((rand() % 2) + 1);
    sem_post(&full);
    pthread_mutex_unlock(&lock);
  }
}

void *consume() { // Infintite Loop that consumers from Buffer(Queue)
  while (1) {
    sem_wait(&full);
    pthread_mutex_lock(&lock);
    // Beginning of Critical Section of Consumer
    printf("---------------Beginning of Critical Section of "
           "Consumer---------------\n");
    int i = array[head];
    head = (head + 1) % MAX;
    printf("Consumers just consumed %d\n", i);
    if (!isEmpty(array))
      printQueue();
    else
      printf("Queue Empty\n");
    printf("----------------Ending of Critical Section of "
           "Consumer---------------\n\n");
    sleep((rand() % 2) + 1);
    // Ending of Critical Section of Consumer
    sem_post(&empty);
    pthread_mutex_unlock(&lock);
  }
}

int main(int argc, char const *argv[]) {
  int i, p, k;
  pthread_t *producer = NULL;
  pthread_t *consumer = NULL;

  // Initializing the MUTEXes and Semaphores
  pthread_mutex_init(&lock, NULL);
  sem_init(&empty, 0, MAX);
  sem_init(&full, 0, 0);

  // Declaring and Initializing the amount of particular threads
  printf("Enter the number of Producers you want to create: ");
  scanf("%d", &p);
  producer = (pthread_t *)calloc(sizeof(pthread_t), p);
  printf("Enter the number of Consumers you want to create: ");
  scanf("%d", &k);
  consumer = (pthread_t *)calloc(sizeof(pthread_t), k);
  int small = p < k ? p : k; // Contains the smaller number between no. of
                             // Producers and no. of Consumers
  printf("Creating the thread Jobs i.e launching them to their respective "
         "runtimes\n");
  printf("Attempt to create Producers and Consumers together\n");
  for (i = 0; i < small; i++) {       //Create Producers and Consumers together
    pthread_create(&producer[i], NULL, produce, NULL);
    pthread_create(&consumer[i], NULL, consume, NULL);
  }
  if (p < k) {
    for (i = small; i < k; i++)       //The remaining producers threads are created
      pthread_create(&consumer[i], NULL, consume, NULL);
  } else if (p > k) {
    for (i = small; i < p; i++)       //The remaining consumers threads are created
      pthread_create(&producer[i], NULL, produce, NULL);
  }
  printf("The Threads are all created now\n");
  for (i = 0; i < p; i++)
    pthread_join(producer[i], NULL);
  for (i = 0; i < k; i++)
    pthread_join(consumer[i], NULL);
  return 0;
}
