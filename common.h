#ifndef COMMON_H
#define COMMON_H

#include <stdint.h>
#include <unistd.h>
#include <netinet/in.h>

#define BUF_SIZE 64

typedef struct{
  uint8_t data[BUF_SIZE];
  int data_len;
  socklen_t address_len;
  struct sockaddr_in cin;
} buffer;

#endif // COMMON_H
