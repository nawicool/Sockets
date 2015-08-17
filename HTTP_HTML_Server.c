#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>

int main(void){
    int server_Socket, accept_Socket;
    unsigned int length, count;
    struct sockaddr_in server_Struct, client_Struct;
    char got_Text[1000];
    char web_site[]="HTTP/1.1 200 OK\r\n\r\n\
                     <html><body><h1> Web site out of order\
                     </h1></body></html>";
                     
    unsigned short int port_No=5000;
    char ip_Server[]="INADDR_ANY";
    
    
    printf("\n Server: socket init........");
    server_Socket=socket(AF_INET,SOCK_STREAM,0);
    
    
    server_Struct.sin_family=AF_INET;
    server_Struct.sin_addr.s_addr=htonl(INADDR_ANY);
    server_Struct.sin_port=htons(port_No);
    length=sizeof(server_Struct);
    
    printf("\n Server: Socket binding......");
    bind(server_Socket,(struct sockaddr *) &server_Struct,length);
    
    printf("\n Server : Socket listen()....on ip %s on port %d",ip_Server,port_No);
    listen(server_Socket,3);
   
   
    while(1){
        
        
    printf("\n Server accept........Loop");
    accept_Socket=accept(server_Socket,(struct sockaddr *) &client_Struct, &length);
    printf("Connected with %s",inet_ntoa(client_Struct.sin_addr));
    
    count=read(accept_Socket,got_Text,sizeof(got_Text));
    got_Text[count]=0;
    //unsigned short int a=ntohs(client_Struct.sin_addr.s_addr);
    printf("\n\n Server: got \n\n %s",got_Text);
    printf("\n\n Server: sent \n\n %s ",web_site);
    write(accept_Socket,web_site,sizeof(web_site));
   
    printf("\n\n Server ::::::: closed:::::::::::::::::::::::::::::::::::::\n\n");
    close(accept_Socket);
}    
    
    
    
    
    
    
    
    
    return (0);
}
