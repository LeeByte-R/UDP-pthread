/**
* @file
* @author Lee Byte
* @version 1.0
*
* @section LICENSE
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License as
* published by the Free Software Foundation; either version 2 of
* the License, or (at your option) any later version.
*
* @section DESCRIPTION
* c queue
* 
* @mainpage 
* c queue implement \n
* change typedef [***] data_type; for apply different data type \n
* change QUEUE_CAPACITY for give max size of queue \n
* the real max size of queue is QUEUE_CAPACITY - 1 because one element would be sacrificed on circular queue
*/


#ifndef QUEUE_H
#define QUEUE_H
#include <stdbool.h>
#include "common.h"

#define QUEUE_CAPACITY 4  ///< max size of queue, real max size of queue is QUEUE_CAPACITY - 1

typedef buffer* data_type;  ///< change typedef [***] data_type; for apply different data type

/**
 * queue structure
*/
typedef struct{
  data_type elements[QUEUE_CAPACITY];  ///< elements of queue
  int front;  ///< index front + 1 is first element of queue
  int back;   ///< index back is end element of queue
} queue;

/**
 * construct queue
 *
 * @param q queue pointer to initialize
 */
void queue_init(queue *q);

/**
 * push data at end of queue
 *
 * @param q queue pointer to push
 * @param d data to push
 * @return whether queue_push success
 */
bool queue_push(queue *q, data_type d);

/**
 * pop data at first of queue \n
 * if queue is empty, return value will be undetermined. check size of queue before use.
 *
 * @param q queue pointer to pop
 * @return data of top of queue
 */
data_type queue_pop(queue *q);

/**
 * peek data at first of queue \n
 * if queue is empty, return value will be undetermined. check queue is not empty before use.
 *
 * @param q queue pointer to peek
 * @return data of end node of queue
 */
data_type queue_peek(queue *q);

/**
 * get size of queue

 *
 * @param q queue pointer
 * @return size of queue

 */
int queue_size(queue *q);

/**
 * check if queue is empty
 *
 * @param q queue pointer
 * @return whether queue is empty
 */
bool queue_is_empty(queue *q);

/**
 * check if queue is full
 *
 * @param q queue pointer
 * @return whether queue is full
 */
bool queue_is_full(queue *q);

#endif // QUEUE_H