#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <pthread.h>
#include "prime_data.h"


bool isPrime(int n) {
    if (n <= 1) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

void* calculate_primes(void* args) {
    PrimeData* shared_data = (PrimeData*)args;
    int chunk[CHUNK_SIZE];
    bool has_more_numbers = true;
    
    while (has_more_numbers) {
        int count = 0;
        
        pthread_mutex_lock(&(shared_data->input_mutex));
        while (count < CHUNK_SIZE && scanf("%d", &chunk[count]) != EOF) {
            count++;
        }
        has_more_numbers = (count > 0);
        pthread_mutex_unlock(&(shared_data->input_mutex));
        
        for (int i = 0; i < count; i++) {
            if (isPrime(chunk[i])) {
                atomic_fetch_add(&(shared_data->total_primes), 1);
            }
        }
    }
    
    pthread_exit(NULL);
}


int main() {
    PrimeData shared_data;
    atomic_init(&shared_data.total_primes, 0);
    pthread_mutex_init(&shared_data.input_mutex, NULL);
    
    pthread_t threads[NUM_THREADS];
    
    for (int i = 0; i < NUM_THREADS; i++) {
        shared_data.thread_args[i].shared_data = &shared_data;
        pthread_create(&threads[i], NULL, calculate_primes, &shared_data);
    }
    
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    
    printf("%d total primes.\n", atomic_load(&shared_data.total_primes));
    
    pthread_mutex_destroy(&shared_data.input_mutex);
    return 0;
}
