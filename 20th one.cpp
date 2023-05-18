#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#define RANGE 1000000000
#define BASE 500000000
int rICrange = RANGE;
int rICbase = BASE;
int rOOCrange = RANGE;
int rOOCbase = BASE;
int wICrange = RANGE;
int wICbase = BASE;
int wOOCrange = RANGE;
int wOOCbase = BASE;
int keepgoing = 1;
int totalReads = 0;
int totalWrites = 0;
int read_count = 0;
sem_t mutex, rw_mutex;
void threadSleep(int range, int base) {
        struct timespec t;
        t.tv_sec = 0;
        t.tv_nsec = (rand() % range) + base;
        nanosleep(&t, 0);
}
void *readers(void *args) {
        int id = *((int *) args);   
        threadSleep(rOOCrange, rOOCbase);
        while (keepgoing) {
                sem_wait(&mutex);
                totalReads++;
                read_count++;
                if(read_count == 1)
                        sem_wait(&rw_mutex);
                sem_post(&mutex);                
                printf("Reader %d starting to read\n", id);
                threadSleep(rICrange, rICbase);
                printf("Reader %d finishing reading\n", id);       
                sem_wait(&mutex);
                read_count--;
                if(read_count == 0)
                        sem_post(&rw_mutex);
                sem_post(&mutex);                
                threadSleep(rOOCrange, rOOCbase);
        }
        printf("Reader %d quitting\n", id);
}
void *writers(void *args) {
        int id = *((int *) args);        
        threadSleep(wOOCrange, wOOCbase);
        while (keepgoing) {
                sem_wait(&rw_mutex);                
                totalWrites++;
                printf("Writer %d starting to write\n", id);
                threadSleep(wICrange, wICbase);
                printf("Writer %d finishing writing\n", id);                
                sem_post(&rw_mutex);               
                threadSleep(wOOCrange, wOOCbase);
        }
        printf("Writer %d quitting\n", id);
}
int main(int argc, char **argv) {
        int numRThreads = 0;
        int numWThreads = 0;        
        if (argc == 11) {
                rICrange = atoi(argv[1]);
                rICbase = atoi(argv[2]);
                rOOCrange = atoi(argv[3]);
                rOOCbase = atoi(argv[4]);
                wICrange = atoi(argv[5]);
                wICbase = atoi(argv[6]);
                wOOCrange = atoi(argv[7]);
                wOOCbase = atoi(argv[8]);
                numRThreads = atoi(argv[9]);
                numWThreads = atoi(argv[10]);
                 }
        else {
                printf("Usage: %s <reader in critical section sleep range> <reader in critical section sleep base> \n\t <reader out of critical section sleep range> <reader out of critical section sleep base> \n\t <writer in critical section sleep range> <writer in critical section sleep base> \n\t <writer out of critical section sleep range> <writer out of critical section sleep base> \n\t <number of readers> <number of writers>\n", argv[0]);
                exit(-1);
        }
        pthread_t RThreads[numRThreads];
        pthread_t WThreads[numWThreads];
        int R_id[numRThreads];
        int W_id[numWThreads];
        sem_init(&mutex, 0, 1);
        sem_init(&rw_mutex, 0, 1);
        int i;
        for(i = 0; i < numRThreads; i++) {
                R_id[i] = i + 1;
                pthread_create(&RThreads[i], 0, readers, &R_id[i]);
        }
        for(i = 0; i < numWThreads; i++) {
                W_id[i] = i + 1;
                pthread_create(&WThreads[i], 0, writers, &W_id[i]);
        }
        char buf[256];
        scanf("%s", &buf);
        keepgoing = 0;
        for(i = 0; i < numRThreads; i++)
                pthread_join(RThreads[i], 0);        
        for(i = 0; i < numWThreads; i++)
                pthread_join(WThreads[i], 0);       
        printf("Total number of reads: %d\nTotal number of writes: %d\n",
                        totalReads, totalWrites);
}
