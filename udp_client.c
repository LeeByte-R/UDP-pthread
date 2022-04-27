#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <arpa/inet.h>

#define BUF_SIZE 64  

int main()
{  
  struct sockaddr_in sin, cin;
  char buf[BUF_SIZE], addr_p[INET_ADDRSTRLEN];
  int s_fd;
  int port = 54321, n;
  socklen_t len;
  char *str = "hello";

  bzero(&sin, sizeof(sin));
  sin.sin_family = AF_INET;
  inet_pton(AF_INET, "127.0.0.1", &sin.sin_addr);
  sin.sin_port = htons(port);

  if((s_fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1){
    perror("fail to create socket");
    exit(1);
  }

  printf("data to server: %s\n", str);
  if(sendto(s_fd, str, strlen(str) + 1, 0, (struct sockaddr *)&sin, sizeof(sin)) == -1){
    perror("fail to send");
    exit(1);
  }
  
  len = sizeof(cin);

  n = recvfrom(s_fd, buf, BUF_SIZE, 0, (struct sockaddr *)&cin, &len);
  if(n == -1){
    perror("fail to receive");
    exit(1);
  }else{
	printf("data from server: %s\n", buf);
  }

  if(close(s_fd) == -1){
    perror("fail to close");
    exit(1);
  }

  return 0;
}  