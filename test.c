#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include<unistd.h>

#define NUM_THREADS 5
pthread_mutex_t mutex;

void *thread_function(void *arg)
{
    pthread_mutex_init(&mutex,NULL);
    int thread_number = *(int *)arg;

    // if(thread_number != 0 && thread_number != 3)
    //     sleep(1);
    if(thread_number)
        sleep(1);

    int *result = malloc(sizeof(int));
    *result = thread_number * thread_number;

    pthread_mutex_lock(&mutex);
    if(thread_number == 3)
    {
        printf("hello there\n");
        pthread_mutex_unlock(&mutex);
        return NULL;
    }
    else
    {
        printf("Thread %d is running...\n", thread_number);
        pthread_mutex_unlock(&mutex);
    }
    return (void *)result;
}

int main()
{
    pthread_t threads[NUM_THREADS];
    int thread_args[NUM_THREADS];
    int i, rc;
    void *status;

    for (i = 0; i < NUM_THREADS; i++) {
        thread_args[i] = i;
        rc = pthread_create(&threads[i], NULL, thread_function, &thread_args[i]);
        if (rc) {
            printf("ERROR: Return code from pthread_create() is %d\n", rc);
            return -1;
        }
    }

    for (i = 0; i < NUM_THREADS; i++) {
        rc = pthread_join(threads[i], &status);
        if (rc) {
            printf("ERROR: Return code from pthread_join() is %d\n", rc);
            return -1;
        }
        if(status)
        {
            printf("Thread %d returned %d.\n", i, *(int *)status);
            free(status);
        }
        else
        {
            pthread_mutex_destroy(&mutex);
            return 0;
        }
    }
    pthread_mutex_destroy(&mutex);

    return 0;
}

