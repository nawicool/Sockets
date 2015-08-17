#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>


int main(void){
    
    int server_Socket, new_Socket; // We need two sockets in Server
    unsigned int length;
    struct sockaddr_in server_Struct, client_Struct;  // We need two struct in Server. In client_struct we save the info for client
                                                      //which is given by OS
    unsigned short int port_No=5000;
    char ip_address[]="127.0.0.1";  // You can also use  INADDR_ANY. It will use the IP address
    printf("\n Creating Server:socket.........\n");
    server_Socket =socket(AF_INET,SOCK_STREAM,0);
    server_Struct.sin_family=AF_INET;
    server_Struct.sin_addr.s_addr=inet_addr(ip_address);
    server_Struct.sin_port=htons(port_No);
    length = sizeof(server_Struct);
    
    /* Now we bind the Socket with an IP and a Port number*/
    printf("\n Now binding .......\n");
    if(bind(server_Socket,(struct sockaddr *)&server_Struct,length)==-1){
        perror("\nError while binding\n");
        exit(1);
        
    }
    
    /* Now server starts listening for clients*/
    printf("\n Server now listing......");
    printf("\n My server is listing on Port %s and on Port %d ",ip_address,port_No);
    listen(server_Socket,5);
        /* Now programm waits and look for clients*/
    
     length = sizeof(client_Struct);
    printf("\n Now entering to accept mode");
    
    
    /* 
       Accept  -- the server programm waits here and look for the connection
       What happen when client ask for connection?
       The information from OS i.e. ip adress and port of client  copied to
       the struct in accept. 
       
    */
    new_Socket=accept(server_Socket,(struct sockaddr *) &client_Struct, &length);
    /* Convert binary text to the  Text (ASCII) */
    printf("\n Connection is established with %s ",inet_ntoa(client_Struct.sin_addr) );
    printf("\n Server: Close() ....");
     close(new_Socket);
    close(server_Socket);
   
    printf("\n Sever shutdown");
    return (0);
    
    
}
