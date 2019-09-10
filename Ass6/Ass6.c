// Assignment 6- Deadlock Free solution to Dining Philosophers Problem (using
// semaphores)
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define MAX_SIZE 10

typedef enum { HUNGRY, THINKING, EATING } e;
e state[MAX_SIZE];
int *eat_count = NULL;
int max = 0;
int n;
sem_t self[MAX_SIZE];
pthread_mutex_t lock;

int test_max(int x) {
  int i = 0;
  if (eat_count[x] < max) {
    return 1;
  } else {
    for (i = 0; i < n; i++) {
      if (eat_count[i] < max) {
        return 0;
      }
    }
    max++;
  }
  return 1;
}
void test(int x) {
  int j;
  // while(1)
  //{
  pthread_mutex_lock(&lock);
  if (state[(x + 1) / n] != EATING && state[(x + (n - 1)) / n] != EATING &&
      state[x] == HUNGRY && test_max(x)) {
    printf("\n Philosopher %d is eating\n", x);
    state[x] = EATING;
    for (j = 0; j < n; j++) {
      printf(" %d ", eat_count[j]);
    }
    eat_count[x]++;
    sem_post(&self[x]);
    // break;
  }
  pthread_mutex_unlock(&lock);
  //}
}

void put_down(int x) {
  pthread_mutex_lock(&lock);
  printf("\n Philosopher %d is Thinking", x);
  state[x] = THINKING;
  pthread_mutex_unlock(&lock);
  test((x + 1) % n);
  test((x + (n - 1)) % n);
}

void pick_up(int x) {
  pthread_mutex_lock(&lock);
  printf("\n Philosopher %d is Hungry", x);
  state[x] = HUNGRY;
  pthread_mutex_unlock(&lock);
  test(x);
  if (state[x] != EATING)
    sem_wait(&self[x]);
}

void *philosophize(void *p) {
  int *i = (int *)p;
  while (1) {
    pthread_mutex_lock(&lock);
    printf("\nPhilosopher %d is thinking", *i);
    state[*i] = THINKING;
    pthread_mutex_unlock(&lock);
    printf("\nPhilosopher %d is going to pick up", *i);
    pick_up(*i);
    sleep(rand() % 4);
    printf("\nPhilosopher %d is going to put down", *i);
    put_down(*i);
    sleep(rand() % 4);
  }
}

int main() {
  printf("\nHow many Philosophers are seated on the table?");
  // printf("1");
  scanf("%d", &n);
  eat_count = (int *)malloc(n * sizeof(int));
  printf("%d", n);
  pthread_t phil[MAX_SIZE];
  int i = 0;

  for (i = 0; i < n; i++) {
    sem_init(&self[i], 0, 0);
    // sem_wait(&self[i]);
  }
  for (i = 0; i < n; i++) {
    eat_count[i] = 0;
  }

  for (i = 0; i < n; i++) {
    int *index = (int *)malloc(sizeof(int));
    *index = i;
    if (pthread_create(&phil[i], NULL, philosophize, (void *)index) == 0) {
      continue;
    } else {
      printf("\nPhilosopher %d couldn't be created.\n", i);
    }
  }
  printf("4");
  for (i = 0; i < n; i++) {
    pthread_join(phil[i], NULL);
  }
  printf("5");
  return 0;
}