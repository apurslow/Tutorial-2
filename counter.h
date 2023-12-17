/*
 *  counter header
 *  Function prototypes, data, and constants for synchronized counter module
 *
 *  University of Washington, Tacoma
 *  TCSS 422 - Operating Systems
 *  Fall 2016
 */

// SYNCHRONIZED COUNTER

// counter structures 
typedef struct __counter_t {
  int value;
  pthread_mutex_t  lock;
} counter_t;

// counter methods
void init_counter(counter_t *c);
int inc_counter(counter_t *c);
int get_counter(counter_t *c);



