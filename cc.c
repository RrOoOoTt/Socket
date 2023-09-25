#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
 
int main(int argc,char *argv[])
{
  int sockfd;
  struct sockaddr_in servaddr;
  sockfd = socket(AF_INET,SOCK_STREAM,0);
  memset(&servaddr,0,sizeof(servaddr));
  servaddr.sin_addr.s_addr = inet_addr(argv[1]);
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(atoi(argv[2]));

  connect(sockfd, (struct sockaddr *)&servaddr,sizeof(servaddr));
  char buffer[1024];
  while(1)
  {
    fgets(buffer,1024,stdin);
    send(sockfd,buffer,strlen(buffer),0);
    printf("发送：%s\n",buffer);
    memset(buffer,0,sizeof(buffer));
    recv(sockfd,buffer,sizeof(buffer),0);
    printf("接收：%s\n",buffer);
  }
  close(sockfd);
}
