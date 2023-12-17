/*
 *  primes module
 *  Primary module providing control flow for the primes program
 * 
 *  University of Washington, Tacoma
 *  TCSS 422 - Operating Systems
 *  Spring 2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>
#include <time.h>
#include <stdbool.h>
#include "counter.h"
#include "primes.h"
#define OUTPUT 1

counter_t primessearch;
counter_t primescnt;
int genprimes = 1000;

bool findPrime(int threadid)
{
  int n = inc_counter(&primessearch);
  int halfOfn = n / 2;
  for (int i=2; i<=halfOfn; i++)
    if (n % i == 0)
    {
      return false;
    }

#if OUTPUT

      switch (threadid)
      {
        case 1:
          printf("\033[0;31m%d,",n);
          break;
        case 2:
          printf("\033[0;32m%d,",n);
          break;
        case 3:
          printf("\033[0;33m%d,",n);
          break;
        case 4:
          printf("\033[0;34m%d,",n);
          break;
        case 5:
          printf("\033[0;35m%d,",n);
          break;
        case 6:
          printf("\033[0;36m%d,",n);
          break;
        case 7:
          printf("\033[1;32m%d,",n);
          break;
        case 8:
          printf("\033[1;34m%d,",n);
      }

#endif
  inc_counter(&primescnt);
  return true;
}

void * generatePrimes(int threadid)
{
  while (get_counter(&primescnt) < genprimes)
  { 
      findPrime(threadid);
  }  
  return NULL;
}

int main (int argc, char * argv[])
{
  pthread_t p1, p2, p3, p4, p5, p6, p7, p8;
  init_counter(&primessearch);
  init_counter(&primescnt);

  if (argc == 2)
    genprimes = atoi(argv[1]);

  pthread_create(&p1, NULL, (void *) generatePrimes, 1);  // CREATE PRIME GENERATOR THREAD 1
  pthread_create(&p2, NULL, (void *) generatePrimes, 2);  // CREATE PRIME GENERATOR THREAD 2
  pthread_create(&p3, NULL, (void *) generatePrimes, 3);  // CREATE PRIME GENERATOR THREAD 3
  pthread_create(&p4, NULL, (void *) generatePrimes, 4);  // CREATE PRIME GENERATOR THREAD 4
  pthread_create(&p5, NULL, (void *) generatePrimes, 5);  // CREATE PRIME GENERATOR THREAD 5
  pthread_create(&p6, NULL, (void *) generatePrimes, 6);  // CREATE PRIME GENERATOR THREAD 6
  pthread_create(&p7, NULL, (void *) generatePrimes, 7);  // CREATE PRIME GENERATOR THREAD 7
  pthread_create(&p8, NULL, (void *) generatePrimes, 8);  // CREATE PRIME GENERATOR THREAD 8

  pthread_join(p1, NULL);
  pthread_join(p2, NULL);
  pthread_join(p3, NULL);
  pthread_join(p4, NULL);
  pthread_join(p5, NULL);
  pthread_join(p6, NULL);
  pthread_join(p7, NULL);
  pthread_join(p8, NULL);

  printf("\b \n");

  return 0;
}
