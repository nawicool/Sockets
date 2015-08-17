#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>

int main(void)
{
    int socket_no; // The return Socket no from OS
    int length;   // Length of the Struct
    int count;   // No. of bytes
    int reply;   // Reply wheater connected or not
    struct sockaddr_in my_address; // AF_INET Family
    char rec_mesg[65000];   // MAX size for reading 
    unsigned short int port_no=80;  //PORT no
    FILE *myFile;  // File to save
    char ip_address[]="46.30.212.64"; // IP address
    char command[]="GET http://ztech.at/index.html HTTP/1.1\r\n Host:PC\r\n\r\n";  // HTTP command
    socket_no=socket(AF_INET,SOCK_STREAM,0); // Genrate a scokt
    my_address.sin_family=AF_INET;    //Set the struct values
    my_address.sin_addr.s_addr=inet_addr(ip_address);  // IP adress
    my_address.sin_port=htons(port_no);  //Port no.
    length=sizeof(my_address);  // size of addr struct
    reply =connect(socket_no,(struct sockaddr*)&my_address,length); // connect
    
    printf("\n 1. --> Connecting to IP %s on Port %d",ip_address,port_no);
    
    
    if(reply==-1)
    {
        
        perror("2.  --> Not able to connect: ");  // unable to connect
        
    }
    else  // if connection was ok
    {
        
        /* write to a buffer */
        printf("\n 3. --> Connected");
        printf(" 4. --> Sending HTTP-command \n\n %s",command);
        count=write(socket_no,command,sizeof(command));     // writing a command on socket buffer and return no. chrachters sent 
        printf(" 5---> %d command chrachters were sent",count); 
        
        /* Now read from buffer*/
        count=read(socket_no,rec_mesg,sizeof(rec_mesg));
        rec_mesg[count]=  '\0';   // Put 0 at end of the string
        printf("\n 6---> %d command chrachters recieved",count);
        printf("\n\n 7---->\n %s",rec_mesg);
        
        /*Now only if i got the right response i will save it to the file */
        if (strstr(rec_mesg,"200 OK")==NULL) {
            printf("\n 8---> Sever hasn't send any data but only header");
          }
          
          
          else{
          printf("\n 9---> Server sent the data with header");
          
          /* Now save the data to external file */
          myFile=fopen("data.html","wt");
          if(myFile==NULL){
              
              printf("\n ---> Unable to open the file ");
          }
         else {
                  
         char *start_Without_Header;  // save without header
         start_Without_Header =strstr(rec_mesg,"\r\n\r\n");   // Returns the pointer to the first of string
         if(start_Without_Header!=NULL){
         fprintf(myFile,"%s",start_Without_Header);
         fclose(myFile);
         }
          else{
              printf("\nError while elminating the Header\n");
              }
         }
    }
   }
  
    close(socket_no);
    printf("\n 10 --> closing ....\t\n\n");
    
}
