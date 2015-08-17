#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>

int main(void){
    
    int server_Socket, accept_Socket;
    unsigned int length, count;
    struct sockaddr_in server_Struct, client_Struct;
    char got_charachter[1000];
    char web_Site[1000];
    unsigned short int port_No=5000;
    char ip_Adress[]="INADDR_ANY";
    
    
    printf("\nStarting socket\n");
    server_Socket=socket(AF_INET,SOCK_STREAM,0);
    
    
server_Struct.sin_family=AF_INET;
server_Struct.sin_addr.s_addr=htonl(INADDR_ANY);
server_Struct.sin_port=htons(port_No);
length=sizeof(server_Struct);
   
    
    printf("\n Server is now binding....");
    bind(server_Socket,(struct sockaddr *)&server_Struct,length);
   
    printf("\n Server listen....");
    printf("\n Server mit IP %s on port %d ",ip_Adress,port_No);
    listen(server_Socket,5);
    
    while(1){
        
        printf("\n Server accept.....");
        accept_Socket=accept(server_Socket,(struct sockaddr *)&client_Struct, &length);
      
        printf(" connected to %s",inet_ntoa(client_Struct.sin_addr));
        
        count=read(accept_Socket,got_charachter,sizeof(got_charachter));
        got_charachter[count]=0;
        printf("server got the charachters %s",got_charachter);
        
        
        sprintf(web_Site,"HTTP/1.1 200 OK\r\n\r\n\
        <html><body><center><h1> You IP is %s</h1></center>",\
        inet_ntoa(client_Struct.sin_addr));
        
        printf("\n\n Sever send %s",web_Site);
        write(accept_Socket,web_Site,strlen(web_Site));
        
          sprintf(web_Site,"<h1> You r welcome <em>%s</em></h1></body></html>",\
          got_charachter);
          
           
        printf("\n\n Sever send %s",web_Site);
        write(accept_Socket,web_Site,strlen(web_Site));
        
         
        printf("\n\n server close()....");
        close(accept_Socket);
    
        
        
        
    }
    
    
    
    
    
    return (0);
}
