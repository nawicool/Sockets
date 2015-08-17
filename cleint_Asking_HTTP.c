#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>

int main(void)
{
    int socket_no;
    int length;
    int count;
    int reply;
    struct sockaddr_in my_address;
    char rec_mesg[65000];
    unsigned short int port_no=80;
    char ip_address[]="46.30.212.64";
    char command[]="GET http://ztech.at/index.html HTTP/1.1\r\n Host:PC\r\n\r\n";
    socket_no=socket(AF_INET,SOCK_STREAM,0);
    my_address.sin_family=AF_INET;
    my_address.sin_addr.s_addr=inet_addr(ip_address);
    my_address.sin_port=htons(port_no);
    length=sizeof(my_address);
    reply =connect(socket_no,(struct sockaddr*)&my_address,length);
    
    printf("\n 1. --> Connecting to IP %s on Port %d",ip_address,port_no);
    
    
    if(reply==-1)
    {
        
        perror("2.  --> Not able to connect: ");
        
    }
    else
    {
        
        printf("\n 3. --> Connected");
        printf(" 4. --> Sending HTTP-command \n\n %s",command);
        count=write(socket_no,command,sizeof(command));
        printf(" 5---> %d command chrachters were sent",count);
        count=read(socket_no,rec_mesg,sizeof(rec_mesg));
        rec_mesg[count]=  '\0'; 
        printf("\n 6---> %d command chrachters recieved",count);
        printf("\n\n 7---->\n %s",rec_mesg);
        if (strstr(rec_mesg,"200 OK")==NULL) {
            printf("\n 8---> Sever hasn't send any data");
          }
          else{
          printf("\n 9---> Server sent the data");
    }
    }
    close(socket_no);
    printf("\n 10 --> closing ....\t\n\n");
    
}
