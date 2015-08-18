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
    char send_chars[1000];
    char response[]="HTTP/1.1 200 OK\r\n\r\n";
    unsigned short int port_No=5000;
    char *position;
  
  char HTTP_Implem[]="HTTP/1.1 501 sorry, not implemented \r\n\r\n";
  char HTMLFORM[]= "<HTML>\n <BODY><center>\n <FORM ACTION =\"ServerHTTPPost\" METHOD=\"post\">\n\
                    Please enter the text and send\n\
                    <br>\n <INPUT TYPE= \" text \" NAME=\"enter_text\">\n\
                    <br>\n <INPUT TYPE =\" submit \" VALUE=\"send_it\">\n\
                    </FORM></center>\n </BODY>\n </HTML>\n";
char  HTMLStart[]="<HTML> <BOOY> <center><hl>  your Input:  ";
char  HTMLEnd[]="</hl></center></BOOY></HTML>"; 
  
 
  
    
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
        printf("\n server got the charachters %s",rec_chars);
        
        while(strstr(rec_chars,"\r\n\r\n")==NULL)
        {
            printf("\n Trying to read the command.......");
            count=count+read(accept_Socket,&rec_chars[count],sizeof(rec_chars)-count);
            rec_chars[count]=0;
            
        }
        
        if(strstr(rec_chars,"GET")!=NULL)
         {
             printf("\n\n GET found! \n\n %s ",rec_chars);
             strcpy(send_chars,response);
             strcat(send_chars,HTTP_Implem);
             write(accept_Socket,send_chars,strlen(send_chars));
         }
         else if(strstr(rec_chars,"POST")!=NULL)
         {
             printf("\n\n Post command found");
             position=strstr(rec_chars,"enter_text");
             while(position==NULL){
                 printf(" Reading......");
                 count=count+read(accept_Socket,&rec_chars[count],sizeof(rec_chars));
                 rec_chars[count]=0;
                 position=strstr(rec_chars,"enter_text");
             }
             printf("\n\n reciev \n\n %s", rec_chars);
             position=position+8;
             printf("\n\n Data in form %s",position);
             strcpy(send_chars,response);
             strcat(send_chars,HTMLStart);
             strcat(send_chars,position);
             strcat(send_chars,HTMLEnd);
             printf("\n\n sent %s",send_chars);
             write(accept_Socket,send_chars,strlen(send_chars));
         }
         else
         {
             printf("\n NO known commands were found");
             printf("\n\n send \n \n %s",HTTP_Implem);
             write(accept_Socket,HTTP_Implem,sizeof(HTTP_Implem));
             
                      }
                      printf("\n\n");
    close(accept_Socket);
        
    }
   
    
    
    return (0);
}
