#include <pthread.h>
#include <stdio.h>

void my_function() {
  pthread_mutex_t my_mutex;
  pthread_mutex_init(&my_mutex, NULL);

  // Use the mutex for mutual exclusion
  pthread_mutex_lock(&my_mutex);
  // Critical section
//   pthread_mutex_unlock(&my_mutex);

  // Destroy the mutex when no longer needed
//   pthread_mutex_destroy(&my_mutex);
}

int main() {
  my_function();

  return 0;
}
