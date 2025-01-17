#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int chopstick[5] =  {1,1, 1, 1, 1}; // Represents the availability of each chopstick


// Custom wait function
void wait(int *s) {
    while (*s <= 0) {
        // Do nothing, wait until semaphore becomes positive
    }
    (*s)--;
}

// Custom signal function
void signal(int *s) {
    (*s)++;
}

void eat(int ph)
{
    printf("%d is eating now....\n",ph);
}


void *philos(void *n) {
    int ph = *(int *)n;
    printf("%d wants to eat\n", ph);
    printf("%d waits for left chopstick\n", ph);
    wait(&chopstick[ph]);
    printf("%d took left one\n", ph);
    printf("%d waits for right chopstick\n", ph);
    wait(&chopstick[(ph + 1) % 5]);
    printf("%d picked right\n", ph);
    printf("%d begins to eat\n", ph);
    eat(ph);
    sleep(2);
    printf("%d finishes eating\n", ph);
    signal(&chopstick[(ph + 1) % 5]);
    printf("%d leaves right\n", ph);
    signal(&chopstick[ph]);
    printf("%d leaves left one\n", ph);
}




int main() {
    int i, n[5];
    pthread_t T[5];

    for (i = 0; i < 5; i++) {
        n[i] = i;
        pthread_create(&T[i], NULL, philos, (void *)&n[i]);
    }

    for (i = 0; i < 5; i++) {
        pthread_join(T[i], NULL);
    }

    return 0;
}
