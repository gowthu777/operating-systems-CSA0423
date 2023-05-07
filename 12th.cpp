#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

// define a semaphore for each chopstick
sem_t chopstick[NUM_PHILOSOPHERS];

void *philosopher(void *arg) {
    int philosopher_id = *((int *) arg);
    int left_chopstick = philosopher_id;
    int right_chopstick = (philosopher_id + 1) % NUM_PHILOSOPHERS;

    while (1) {
        // think for a while
        printf("Philosopher %d is thinking...\n", philosopher_id);
        sleep(rand() % 5 + 1);

        // pick up left chopstick
        printf("Philosopher %d is picking up left chopstick %d...\n", philosopher_id, left_chopstick);
        sem_wait(&chopstick[left_chopstick]);

        // pick up right chopstick
        printf("Philosopher %d is picking up right chopstick %d...\n", philosopher_id, right_chopstick);
        sem_wait(&chopstick[right_chopstick]);

        // eat for a while
        printf("Philosopher %d is eating...\n", philosopher_id);
        sleep(rand() % 5 + 1);

        // put down right chopstick
        printf("Philosopher %d is putting down right chopstick %d...\n", philosopher_id, right_chopstick);
        sem_post(&chopstick[right_chopstick]);

        // put down left chopstick
        printf("Philosopher %d is putting down left chopstick %d...\n", philosopher_id, left_chopstick);
        sem_post(&chopstick[left_chopstick]);
    }
}

int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int philosopher_args[NUM_PHILOSOPHERS];
    int rc, t;

    // initialize the semaphores
    for (t = 0; t < NUM_PHILOSOPHERS; t++) {
        rc = sem_init(&chopstick[t], 0, 1);
        if (rc) {
            printf("Error: return code from sem_init() is %d\n", rc);
            exit(1);
        }
    }

    // create the threads
    for (t = 0; t < NUM_PHILOSOPHERS; t++) {
        philosopher_args[t] = t;
        rc = pthread_create(&philosophers[t], NULL, philosopher, (void *) &philosopher_args[t]);
        if (rc) {
            printf("Error: return code from pthread_create() is %d\n", rc);
            exit(1);
        }
    }

    // wait for the threads to finish (which will never happen)
    for (t = 0; t < NUM_PHILOSOPHERS; t++) {
        rc = pthread_join(philosophers[t], NULL);
        if (rc) {
            printf("Error: return code from pthread_join() is %d\n", rc);
            exit(1);
        }
    }

    return 0;
}

