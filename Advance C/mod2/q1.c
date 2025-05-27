#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>

int N;


bool isPrime(int num) {
    if (num <= 1) return false;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0)
            return false;
    }
    return true;
}


void* threadA_func(void* arg) {
    int count = 0, num = 2, sum = 0;
    while (count < N) {
        if (isPrime(num)) {
            sum += num;
            count++;
        }
        num++;
    }
    printf("Thread A: Sum of first %d prime numbers is %d\n", N, sum);
    pthread_exit(NULL);
}


void* threadB_func(void* arg) {
    time_t start = time(NULL);
    while (time(NULL) - start < 100) {
        printf("Thread 1 running\n");
        sleep(2);
    }
    pthread_exit(NULL);
}


void* threadC_func(void* arg) {
    time_t start = time(NULL);
    while (time(NULL) - start < 100) {
        printf("Thread 2 running\n");
        sleep(3);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t threadA, threadB, threadC;

    printf("Enter value of N: ");
    scanf("%d", &N);

    pthread_create(&threadA, NULL, threadA_func, NULL);
    pthread_create(&threadB, NULL, threadB_func, NULL);
    pthread_create(&threadC, NULL, threadC_func, NULL);

    pthread_join(threadA, NULL);
    pthread_join(threadB, NULL);
    pthread_join(threadC, NULL);

    return 0;
}
