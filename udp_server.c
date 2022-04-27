#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <pthread.h>
#include "queue.h"
#include "common.h"

int s_fd;
queue used_q, unused_q;

pthread_mutex_t mutex_usedq   = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_unusedq = PTHREAD_MUTEX_INITIALIZER;

void* process_f(void* arg) {
  char addr_p[INET_ADDRSTRLEN];
  buffer *bpt;

  while(true){
    while(queue_is_empty(&used_q)); // wait until data is already receive
    pthread_mutex_lock(&mutex_usedq);
    bpt = queue_pop(&used_q);
    pthread_mutex_unlock(&mutex_usedq);
    
    /*
    inet_ntop(AF_INET, &(bpt->cin.sin_addr), addr_p, sizeof(addr_p));
    printf("client IP is %s, port is %d\n", addr_p, ntohs(bpt->cin.sin_port));
    printf("content is: %s\n\n", buf);
    */

    /*
    process data
    */
    if(sendto(s_fd, bpt->data, bpt->data_len, 0, (struct sockaddr *)&(bpt->cin), bpt->address_len) == -1){
      perror("fail to send");
      exit(1);
    }

    while(queue_is_full(&unused_q));  // wait until unused_q has at least one position to insert
    pthread_mutex_lock(&mutex_unusedq);
    queue_push(&unused_q, bpt);
    pthread_mutex_unlock(&mutex_unusedq);
  }
  
  pthread_exit(NULL);
}

int main(){
  struct sockaddr_in sin, cin;
  int port = 54321, n;
  socklen_t len;
  buffer *bp;

  bzero(&sin, sizeof(sin));

  sin.sin_family = AF_INET;
  sin.sin_addr.s_addr = INADDR_ANY;
  sin.sin_port = htons(port);

  if((s_fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1){
    perror("fail to create socket");
    exit(1);
  }

  if(bind(s_fd, (struct sockaddr *)&sin, sizeof(sin)) == -1){
    perror("fail to bind");
    exit(1);
  }

  queue_init(&used_q);
  queue_init(&unused_q);

  pthread_t t;
  pthread_create(&t, NULL, process_f, NULL);

  printf("waiting...\n");
  while(1){
    pthread_mutex_lock(&mutex_unusedq);
    
    if(queue_is_empty(&unused_q)){
      bp = (buffer *)malloc(sizeof(buffer));
    }else{
      bp = queue_pop(&unused_q);
    }
    pthread_mutex_unlock(&mutex_unusedq);

    len = sizeof(cin);

    n = recvfrom(s_fd, bp->data, BUF_SIZE, 0, (struct sockaddr *)&cin, &len);
    
    if(n == -1){
      perror("fail to receive");
      exit(1);
    }
    bp->data_len = n;
    bp->cin = cin;
    bp->address_len = len;

    while(queue_is_full(&used_q));  // wait until used_q has at least one position to insert
    pthread_mutex_lock(&mutex_usedq);
    queue_push(&used_q, bp);
    pthread_mutex_unlock(&mutex_usedq);
  }

  pthread_join(t, NULL);

  if(close(s_fd) == -1){
    perror("fail to close");
    exit(1);
  }

  return 0;
}