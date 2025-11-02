#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAX 10      // Maximum number of philosophers allowed

int N;              // Number of philosophers
int eatCount;       // How many times each philosopher eats
int state[MAX];
int phil_num[MAX];

sem_t mutex;
sem_t S[MAX];

#define THINKING 0
#define HUNGRY 1
#define EATING 2

void test(int ph_num) {
  if (state[ph_num] == HUNGRY &&
      state[(ph_num + N - 1) % N] != EATING &&
      state[(ph_num + 1) % N] != EATING) {
    
    state[ph_num] = EATING;
    printf("Philosopher %d takes chopsticks %d and %d\n",
           ph_num + 1, ph_num + 1, (ph_num + 1) % N + 1);
    printf("Philosopher %d is Eating\n", ph_num + 1);
    sem_post(&S[ph_num]);
  }
}

void take_chopsticks(int ph_num) {
  sem_wait(&mutex);
  state[ph_num] = HUNGRY;
  printf("Philosopher %d is Hungry\n", ph_num + 1);
  test(ph_num);
  sem_post(&mutex);
  sem_wait(&S[ph_num]);
}

void put_chopsticks(int ph_num) {
  sem_wait(&mutex);
  state[ph_num] = THINKING;
  printf("Philosopher %d puts down chopsticks %d and %d\n",
         ph_num + 1, ph_num + 1, (ph_num + 1) % N + 1);
  printf("Philosopher %d is Thinking\n", ph_num + 1);
  test((ph_num + N - 1) % N);
  test((ph_num + 1) % N);
  sem_post(&mutex);
}

void* philosopher(void* num) {
  int id = *(int*)num;
  for (int i = 0; i < eatCount; i++) {
    sleep(1);
    take_chopsticks(id);
    sleep(2);
    put_chopsticks(id);
  }
  return NULL;
}

int main() {
  pthread_t thread_id[MAX];
  
  printf("Enter number of philosophers (max %d): ", MAX);
  scanf("%d", &N);
  printf("Enter how many times each philosopher should eat: ");
  scanf("%d", &eatCount);
  
  sem_init(&mutex, 0, 1);
  for (int i = 0; i < N; i++) {
    sem_init(&S[i], 0, 0);
    phil_num[i] = i;
  }
  
  printf("\n--- Dining Philosophers Simulation Started ---\n\n");
  
  for (int i = 0; i < N; i++) {
    pthread_create(&thread_id[i], NULL, philosopher, &phil_num[i]);
    printf("Philosopher %d is Thinking\n", i + 1);
  }
  
  for (int i = 0; i < N; i++) {
    pthread_join(thread_id[i], NULL);
  }
  
  printf("\n--- Simulation Complete ---\n");
  return 0;
}
