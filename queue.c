# include "queue.h"

void queue_init(queue *q){
  q->front = 0;
  q->back = 0;
}

bool queue_push(queue *q, data_type d){
  if(queue_is_full(q))
    return false;

  q->back = (q->back + 1) % QUEUE_CAPACITY;
  q->elements[q->back] = d;
  
  return true;
}

data_type queue_pop(queue *q){
  if(queue_is_empty(q))
    return q->elements[0];
  
  q->front = (q->front + 1) % QUEUE_CAPACITY;
  
  return q->elements[q->front];
}

data_type queue_peek(queue *q){
  if(queue_is_empty(q))
    return q->elements[0];

  return q->elements[(q->front + 1) % QUEUE_CAPACITY];
}

int queue_size(queue *q)
{
  int size;
  
  if(q->front < q->back)
    size = q->back - q->front;
  else
    size = QUEUE_CAPACITY - (q->front - q->back);
  
  return size;
}

bool queue_is_empty(queue *q)
{
  return (q->front == q->back);
}

bool queue_is_full(queue *q)
{
  return ((q->back + 1) % QUEUE_CAPACITY == q->front);
}

