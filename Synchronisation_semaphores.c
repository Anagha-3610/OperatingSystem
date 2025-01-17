#include <stdio.h>
#include <pthread.h>

int odd=1,even=2;
typedef struct {
    pthread_mutex_t mutex;
    pthread_cond_t condition;
    int value;
} semaphore;

void semaphore_init(semaphore* sem, int initial_value) {
    pthread_mutex_init(&(sem->mutex), NULL);
    pthread_cond_init(&(sem->condition), NULL);
    sem->value = initial_value;
}

void semaphore_wait(semaphore* sem) {
    pthread_mutex_lock(&(sem->mutex));
    while (sem->value <= 0) {
        pthread_cond_wait(&(sem->condition), &(sem->mutex));
    }
    sem->value--;
    pthread_mutex_unlock(&(sem->mutex));
}

void semaphore_signal(semaphore* sem) {
    pthread_mutex_lock(&(sem->mutex));
    sem->value++;
    pthread_cond_signal(&(sem->condition));
    pthread_mutex_unlock(&(sem->mutex));
}

void* odd_function(void* arg) {
    semaphore* sem = (semaphore*)arg;
    semaphore_wait(sem);

    printf("ODD THREAD\n");
    printf("ODD NUMBER=%d\nCUBE=%d\n",odd,odd*odd*odd);
    odd=odd+2;
    semaphore_signal(sem);

    return NULL;
}

void* even_function(void* arg) {
    semaphore* sem = (semaphore*)arg;
    semaphore_wait(sem);
    printf("EVEN THREAD\n");
    printf("EVEN NUMBER=%d\nSQUARE=%d\n",even,even*even);
    even=even+2;
    semaphore_signal(sem);

    return NULL;
}

int main() {
    semaphore sem;
    semaphore_init(&sem, 1); // Initialize the semaphore with initial value 1
    int n=10;
    pthread_t thread;
    for(int i=0;i<n;i++)
    {
    	pthread_create(&thread, NULL, odd_function, (void*)&sem);
    	pthread_create(&thread, NULL, even_function, (void*)&sem);
    }
    printf("Main thread\n");
    semaphore_wait(&sem);
    semaphore_signal(&sem);

    pthread_join(thread, NULL);

    return 0;
}
