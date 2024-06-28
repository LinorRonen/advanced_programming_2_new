.PHONY: all clean

all: randomGenerator primeCounter primeCounterThreads

randomGenerator: generator.c
	gcc -o randomGenerator generator.c

primeCounter: primeCounter.c
	gcc -o primeCounter primeCounter.c

primeCounterThreads: primeCounterThreads.c
	gcc -o primeCounterThreads primeCounterThreads.c -pthread

clean:
	rm -f randomGenerator primeCounter primeCounterThreads
