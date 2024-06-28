#ifndef PRIME_DATA_H
#define PRIME_DATA_H

#include <stdatomic.h>
#include <pthread.h>

#define NUM_THREADS 4
#define CHUNK_SIZE 2000 // Each thread will process a chunk of 2000 numbers

typedef atomic_int AtomicInt;
typedef pthread_mutex_t Mutex;

typedef struct {
    AtomicInt total_primes;
    Mutex input_mutex;
    struct {
        struct PrimeData* shared_data;
    } thread_args[NUM_THREADS];
} PrimeData;

#endif // PRIME_DATA_H
