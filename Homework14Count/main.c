#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int countTotal = 100; // Count limit
int threadTotal = 10; // Number of threads

void *count_numbers(void *arg) {
    int index = *(int *)arg;
    free(arg); // Free allocated memory for thread ID

    int portion = countTotal / threadTotal;

    // Compute the range for this thread
    int start = portion * index + 1;
    int end = (index == threadTotal - 1) ? countTotal : (portion * (index + 1));

    // Print the assigned numbers
    for (int i = start; i <= end; i++) {
        printf("Thread ID %ld, count %d\n", pthread_self(), i);
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[threadTotal];

    for (int i = 0; i < threadTotal; i++) {
        int *arg = malloc(sizeof(int)); // Allocate memory for each thread's index
        *arg = i;
        pthread_create(&threads[i], NULL, count_numbers, arg);
    }

    for (int i = 0; i < threadTotal; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
