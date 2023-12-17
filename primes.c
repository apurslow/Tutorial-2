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
#define OUTPUT 0

counter_t primessearch;
counter_t primescnt;
int genprimes = 1000;

// 
int bdone = 0;
//protects bdone variable 
pthread_mutex_t donelock;
//used to signal when prime generation is done
pthread_cond_t donecond;
//ensures order of primes printed to screen in order
pthread_mutex_t orderlock;


//finds a prime number
bool findPrime(int threadid)
{
  //acquire order lock
  pthread_mutex_lock(&orderlock);

  int n = inc_counter(&primessearch);
  int halfOfn = n / 2;

  for (int i=2; i<=halfOfn; i++)
    if (n % i == 0)
    {
      //release order lock if not prime
      pthread_mutex_unlock(&orderlock);

      return false;
    }
//acquire done lock
pthread_mutex_lock(&donelock);
if (bdone==0)
{

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
}
//release order lock
pthread_mutex_unlock(&orderlock);

 //check if incrementing primescnt will reach genprimes 
if (inc_counter(&primescnt) == genprimes)
{
//if so set bdone to 1 and signal donecond
bdone=1;
pthread_cond_signal(&donecond);
}
//release done lock
pthread_mutex_unlock(&donelock);
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
  //initialize order lock
  pthread_mutex_init(&orderlock,NULL);
  pthread_t p1, p2, p3, p4;
  init_counter(&primessearch);
  init_counter(&primescnt);
  //initialize done lock and done condition variable
  pthread_mutex_init(&donelock,NULL);
  pthread_cond_init(&donecond,NULL);

  if (argc == 2)
    genprimes = atoi(argv[1]);

  pthread_create(&p1, NULL, (void *) generatePrimes, 1);  // CREATE PRIME GENERATOR THREAD 1
  pthread_create(&p2, NULL, (void *) generatePrimes, 2);  // CREATE PRIME GENERATOR THREAD 2
  pthread_create(&p3, NULL, (void *) generatePrimes, 3);  // CREATE PRIME GENERATOR THREAD 3
  pthread_create(&p4, NULL, (void *) generatePrimes, 4);  // CREATE PRIME GENERATOR THREAD 4
  // pthread_create(&p5, NULL, (void *) generatePrimes, 5);  // CREATE PRIME GENERATOR THREAD 5
  // pthread_create(&p6, NULL, (void *) generatePrimes, 6);  // CREATE PRIME GENERATOR THREAD 6
  // pthread_create(&p7, NULL, (void *) generatePrimes, 7);  // CREATE PRIME GENERATOR THREAD 7
  // pthread_create(&p8, NULL, (void *) generatePrimes, 8);  // CREATE PRIME GENERATOR THREAD 8

  // pthread_join(p1, NULL);
  // pthread_join(p2, NULL);
  // pthread_join(p3, NULL);
  // pthread_join(p4, NULL);
  // pthread_join(p5, NULL);
  // pthread_join(p6, NULL);
  // pthread_join(p7, NULL);
  // pthread_join(p8, NULL);

  //Wait for any threads to signal donecond
  pthread_mutex_lock(&donelock);
  while (bdone==0)
  pthread_cond_wait(&donecond, &donelock);

  printf("\b \n");

  return 0;
}
