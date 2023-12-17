/*
 *  synchronized counter
 *  based on Operating Systems: Three Easy Pieces by R. Arpaci-Dusseau and A. Arpaci-Dusseau
 * 
 *  This example uses locks and a condition to synchronize a child thread and
 *  the parent.  The child generates matrices and the parent computes the
 *  average when the matrix is ready for processing.
 *
 *  Wes J. Lloyd
 *  University of Washington, Tacoma
 *  TCSS 422 - Operating Systems
 *  Spring 2020
 */

// Include libraries required for this module only
#include <stdio.h>
#include <pthread.h>
#include "counter.h"

// SYNCHRONIZED COUNTER METHOD IMPLEMENTATION
// Based on Three Easy Pieces

void init_counter(counter_t *c)  {
  c->value = 0;
  pthread_mutex_init(&c->lock, NULL);
}

int inc_counter(counter_t *c)  {
  pthread_mutex_lock(&c->lock);
  int rc = ++c->value;
  pthread_mutex_unlock(&c->lock);
  return rc;
}

int get_counter(counter_t *c)  {
  pthread_mutex_lock(&c->lock);
  int rc = c->value;
  pthread_mutex_unlock(&c->lock);
  return rc;
}


