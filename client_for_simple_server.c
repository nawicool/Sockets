#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>

int main(void){
    
    int socket_No;
    int length;
    struct sockaddr_in struct_Cleint;
    int reply;
    unsigned short int port_No=5000;
    char server_IP[]="127.0.0.1";
    socket_No =socket(AF_INET,SOCK_STREAM,0);
    struct_Cleint.sin_family=AF_INET;
    struct_Cleint.sin_addr.s_addr=inet_addr(server_IP);
    struct_Cleint.sin_port=htons(port_No);
    length=sizeof(struct_Cleint);
    
    printf("\n Client: connecting ......");
    reply=connect(socket_No,(struct sockaddr*)  &struct_Cleint,length);
    if(reply==0)
    {
       printf("\n  Connecting to IP %s on port %d",server_IP,port_No) ;
       printf("\n Connection Established");
        
    }
    else
    {
        perror("Connection ERORR!!!!!");
    }
    
    printf("\n closing........");
    close(socket_No);
    printf("\n\n");
    return 0;
}
