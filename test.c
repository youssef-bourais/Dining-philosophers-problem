#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

typedef struct philosopher {
    int id;
    pthread_mutex_t *forks;
} Philosopher;

void *philosopher_action(void *arg)
{
    Philosopher *philosopher = (Philosopher *)arg;

    while (1) {
        int left_fork = philosopher->id - 1;
        int right_fork = philosopher->id % 5;

        pthread_mutex_lock(&philosopher->forks[left_fork]);
        printf("Philosopher %d picks up left fork %d\n", philosopher->id, left_fork);

        pthread_mutex_lock(&philosopher->forks[right_fork]);
        printf("Philosopher %d picks up right fork %d\n", philosopher->id, right_fork);

        printf("Philosopher %d is eating\n", philosopher->id);

        pthread_mutex_unlock(&philosopher->forks[left_fork]);
        printf("Philosopher %d puts down left fork %d\n", philosopher->id, left_fork);

        pthread_mutex_unlock(&philosopher->forks[right_fork]);
        printf("Philosopher %d puts down right fork %d\n", philosopher->id, right_fork);

        printf("Philosopher %d is thinking\n", philosopher->id);

        sleep(1);
    }

    return NULL;
}

int main()
{
    int num_philosophers = 5;
    Philosopher *philosophers = malloc(num_philosophers * sizeof(Philosopher));

    for (int i = 0; i < num_philosophers; i++) {
        philosophers[i].id = i + 1;
        philosophers[i].forks = malloc(2 * sizeof(pthread_mutex_t));
        pthread_mutex_init(&philosophers[i].forks[0], NULL);
        pthread_mutex_init(&philosophers[i].forks[1], NULL);

        pthread_t thread_id;
        pthread_create(&thread_id, NULL, philosopher_action, &philosophers[i]);
    }

    while (1) {
        // The main thread does nothing while the philosopher threads run
        sleep(1);
    }

    return 0;
}
