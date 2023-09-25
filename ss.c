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
  int listenfd;
  listenfd = socket(AF_INET,SOCK_STREAM,0);
  struct sockaddr_in servaddr;
  memset(&servaddr,0,sizeof(servaddr));
  servaddr.sin_family = AF_INET;  
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(atoi(argv[1])); 
  bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
  listen(listenfd,5);
  int  clientfd;
  int  socklen=sizeof(struct sockaddr_in);
  struct sockaddr_in clientaddr;
  clientfd=accept(listenfd,(struct sockaddr *)&clientaddr,(socklen_t*)&socklen);
  char buffer[1024];
    memset(buffer,0,sizeof(buffer));
    while(1)
{
    recv(clientfd,buffer,sizeof(buffer),0);
    printf("接收：%s\n",buffer);
    memset(buffer,0,sizeof(buffer));
    strcpy(buffer,"ok");
    send(clientfd,buffer,strlen(buffer),0);
    printf("发送：%s\n",buffer);
				}
  close(listenfd); close(clientfd);
}
