#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>
#include <signal.h>

int N;


void sigint_handler(int sig) {
    printf("\nSIGINT (Ctrl+C) caught. Ignoring termination...\n");
}


bool isPrime(int num) {
    if (num <= 1) return false;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0)
            return false;
    }
    return true;
}


void* threadA_func(void* arg) {
    clock_t start = clock();
    int count = 0, num = 2, sum = 0;
    while (count < N) {
        if (isPrime(num)) {
            sum += num;
            count++;
        }
        num++;
    }
    clock_t end = clock();
    double time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Thread A: Sum of first %d primes is %d (Time: %.2fs)\n", N, sum, time_taken);
    pthread_exit(NULL);
}


void* threadB_func(void* arg) {
    time_t start_time = time(NULL);
    time_t current_time;
    do {
        printf("Thread 1 running\n");
        sleep(2);
        current_time = time(NULL);
    } while (current_time - start_time < 100);
    printf("Thread 1 finished (Ran for 100s)\n");
    pthread_exit(NULL);
}


void* threadC_func(void* arg) {
    time_t start_time = time(NULL);
    time_t current_time;
    do {
        printf("Thread 2 running\n");
        sleep(3);
        current_time = time(NULL);
    } while (current_time - start_time < 100);
    printf("Thread 2 finished (Ran for 100s)\n");
    pthread_exit(NULL);
}

int main() {
    
    signal(SIGINT, sigint_handler);

    pthread_t threadA, threadB, threadC;

    printf("Enter value of N: ");
    scanf("%d", &N);

    
    printf("\nStarting Thread A...\n");
    pthread_create(&threadA, NULL, threadA_func, NULL);

    printf("Starting Thread B...\n");
    pthread_create(&threadB, NULL, threadB_func, NULL);

    printf("Starting Thread C...\n");
    pthread_create(&threadC, NULL, threadC_func, NULL);

    
    pthread_join(threadA, NULL);
    pthread_join(threadB, NULL);
    pthread_join(threadC, NULL);

    printf("All threads completed.\n");
    return 0;
}
