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
    char rec_chars[1000];
    char *position1, *position2;
    char nameof_File[100];
    char str_response_OK[]="HTTP/1.1 200 OK\r\n\r\n";
    unsigned short int port_No=5000;
    char str_HTMLStart[]="<HTML> <BOOY>" ;
    char str_HTMLEnd[]="</BOOY></HTML>"; 
    char str_file_name[]="Filename= ";
    char str_no_GET[] ="No GET command found!";
    char str_no_HTTP[]="No HTTP found!";
    char str_file_Found[]="<br> File Found";
    char str_file_not_Found[]="<br> File not found!";
    FILE *file_dp;
    char my_Char;
  
    server_Socket=socket(AF_INET,SOCK_STREAM,0);
    server_Struct.sin_family=AF_INET;
    server_Struct.sin_addr.s_addr=htonl(INADDR_ANY);
    server_Struct.sin_port=htons(port_No);
    length=sizeof(server_Struct);
   
    
    printf("\n Server is now binding....");
    bind(server_Socket,(struct sockaddr *)&server_Struct,length);
   
    printf("\n Server listen....");
    //printf("\n Server mit IP %s on port %d ",ip_Adress,port_No);
    listen(server_Socket,5);
    
    while(1){
        
        printf("\n Server accept.....");
        fflush(stdout);
        accept_Socket=accept(server_Socket,(struct sockaddr *)&client_Struct, &length);
      
        printf(" \n connected to %s",inet_ntoa(client_Struct.sin_addr));
        
        count=read(accept_Socket,rec_chars,sizeof(rec_chars));
        rec_chars[count]=0;
        write(accept_Socket,str_response_OK,strlen(str_response_OK));
        write(accept_Socket,str_HTMLStart,strlen(str_HTMLStart));
        
        if(position1=strstr(rec_chars,"GET"))
        {
            if(position2=strstr(rec_chars,"HTTP"))
            {
                length=position2-position1-5;                  // THERE COULD BE AN ERROR
                strncpy(nameof_File,position1+4,(length+1));  // THERE COULD BE AN ERROR
                nameof_File[length]=0;
                printf("\n GET command for File %s found",nameof_File);
                write(accept_Socket,str_file_name,strlen(str_file_name));
                write(accept_Socket,nameof_File,length);
                file_dp=fopen(nameof_File,"rt");
                if(file_dp==NULL)
                 {
                     printf("\n Datein %s existier nicht",nameof_File);
                      write(accept_Socket,str_HTMLStart,strlen(str_HTMLStart));
                     write(accept_Socket,str_file_not_Found,strlen(str_file_not_Found));
                     write(accept_Socket,str_HTMLEnd,strlen(str_HTMLEnd));
                 }
                 else
                 {
                     printf("\n Datei %s existiert ",nameof_File);
                     
                     
                     do{
                         my_Char=fgetc(file_dp);
                         if(!feof(file_dp))
                         {
                            write(accept_Socket,&my_Char,1);
                         }
                     }while(!feof(file_dp));
                   fclose(file_dp);
                     
                    }
            }
            else 
            {
                printf("\n HTTP-Parser has found no HTTP command");
                write (accept_Socket,str_no_HTTP,strlen(str_no_HTTP));
            }
            
        }
        else{
            printf("\n HTTP-Parser has found no GET command");
                write (accept_Socket,str_no_GET,strlen(str_no_GET));
        }
        
        printf("\n");
        
        write(accept_Socket,str_HTMLEnd,strlen(str_HTMLEnd));
        close(accept_Socket);
        }
       return (0); 
    }
   
    
    
   
