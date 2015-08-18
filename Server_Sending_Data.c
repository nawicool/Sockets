#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>

int main(void){
    
    int server_Socket, accept_Socket;
    unsigned int length, count,file_size;
    struct sockaddr_in server_Struct, client_Struct;
    char my_Char;
    char rec_chars[1000];
    char send_char[1000];
    char *position1, *position2;
    char nameof_File[100];

    unsigned short int port_No=5000;
    
    char str_response_OK[]="HTTP/1.1 200 OK\r\n\r\n";
    char str_response_Error[]="HTTP/1.1 501 Not implemented OK\r\n\r\n";
    char str_accept_Range[]="Accept Range: bytes\r\n";
    char str_content_len[]="Content-Length:";
    char str_File_len[20];
    char str_http_typ_png[]="Content-Type: image/png\r\n";
    char str_http_typ_html[]="Content-Type: text/html\r\n";
    char str_empty_line[]="\r\n";
    char str_HTMLStart[]="<HTML> <BOOY>" ;
    char str_HTMLEnd[]="</BOOY></HTML>"; 
    FILE *file_dp;
   
    server_Socket=socket(AF_INET,SOCK_STREAM,0);
    server_Struct.sin_family=AF_INET;
    server_Struct.sin_addr.s_addr=htonl(INADDR_ANY);
    server_Struct.sin_port=htons(port_No);
    length=sizeof(server_Struct);
   
    
    printf("\n Server is now binding....");
    bind(server_Socket,(struct sockaddr *)&server_Struct,length);
   
    printf("\n Server listen....");
    listen(server_Socket,5);
    
    while(1){
        
        printf("\n Server accept.....");
        fflush(stdout);
        accept_Socket=accept(server_Socket,(struct sockaddr *)&client_Struct, &length);
      
        printf(" \n connected to %s",inet_ntoa(client_Struct.sin_addr));
        
        count=read(accept_Socket,rec_chars,sizeof(rec_chars));
        rec_chars[count]=0;
      
      if(position1=strstr(rec_chars,"GET"))
        {
            if(position2=strstr(rec_chars,"HTTP"))
            {
                length=position2-position1-5;                  // THERE COULD BE AN ERROR
                strncpy(nameof_File,position1+4,(length+1));  // THERE COULD BE AN ERROR
                nameof_File[length]=0;
                printf("\n GET command for File %s found",nameof_File);
               
                file_dp=fopen(nameof_File,"rb");
                if(file_dp==NULL)
                 {
                  printf("\n Datein %s existier nicht",nameof_File);
                  strcpy(send_char,str_response_OK);
                  strcat(send_char,str_HTMLStart);
                  strcat(send_char,"<br> File not exists");
                  strcat(send_char,str_HTMLEnd);
                  write(accept_Socket,send_char,strlen(send_char));
                      
                 }
                 else
                 {
                    file_size=-1;
                     do{
                         fgetc(file_dp);
                         file_size++;
                         
                         }while(!feof(file_dp));
                     
                  
                  printf("\n File size =%d Bytes",file_size);
                  sprintf(str_File_len,"%d\r\n",file_size);
                  strcpy(send_char,str_response_OK);
                  strcat(send_char,str_accept_Range);
                  strcat(send_char,str_content_len);
                  strcat(send_char,str_File_len);
                  
                  if(strstr(nameof_File,".png"))
                  {
                      strcat(send_char,str_http_typ_png);
                  }
                  else 
                  {
                      strcat(send_char,str_http_typ_html);
                  }
                      
                      strcat(send_char,str_empty_line);
                      
                      printf("\n Server send Pakethead: \n%s",send_char);
                      write(accept_Socket,send_char,strlen(send_char));
                      printf("Server: Send datei %s\n",nameof_File);
                      rewind(file_dp);
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
                printf("\n HTTP-Parser has found no HTTP-Befehl command");
                write (accept_Socket,str_response_Error,strlen(str_response_Error));
            }
            
        }
        else{
            printf("\n HTTP-Parser has found no GET command");
            write (accept_Socket,str_response_Error,strlen(str_response_Error));
      
        }
        close(accept_Socket);
        }
       return (0); 
    }
   
    
    
   
