#pragma comment(lib,"ws2_32.lib")
#include<cstdio>
#include<iostream>
#include<WinSock2.h>
#include<Windows.h>
/* ADD libwsock32.a in linker in setting -> compiler--> linker option in codeblocks */
using namespace std;

int main(void)
{

 /********************* Initialise Winsock Library*******************/
    long response;  /*Hilfsvariable für rückgabewerte*/
    WSADATA wsaData; /*Struct für Versionsdaten WSADATA*/

    response=WSAStartup(MAKEWORD(2,0),&wsaData); /* Intialise winsock libraray 2,0 is version & WSADATA structure */
    if(response==0)
        {
        cout<<"\n";
        cout<<"WSAstartup sucess .... \t\t"<<endl;
        cout<<"Version of wsaData you are using = "<<wsaData.wVersion<<endl;
        cout<<"Highest version you can use on ur system= "<<wsaData.wHighVersion<<endl; // Gives the highest version avialble on
                                                                                        // ur system
        cout<<"\n\n\n";
        }
    else
        {
        cout<<"WSAtartup was error ... \t\t"<<WSAGetLastError()<<endl; ////WSAGetLastError gibt den letzten fehler
                                                                       //Socket Deskriptoren
        }


/************************************************************************/

/**********************CREATE NEW SOCKET*********************************/


    SOCKET sok_slisten,sok_client; // Socket anforderen bzw.  kommunikationspunkt einrichten
    sok_slisten=socket(AF_INET,SOCK_STREAM,0);  // Create a socket TCP
    if(sok_slisten!=INVALID_SOCKET)
        {
        cout<<"socket was sucess... \t\t"<<endl;
        }
    else
        {
            //WSAGetLastError gibt den letzten fehler
         cout<<"socket was error.... \t\t"<<WSAGetLastError()<<endl;
        }
/*************************************************************************/



/*********************** Bind to a socket  *******************************/


    sockaddr_in server_Info,client_Info;
    char recv_Data_from_Client[100];
    char sent_Data_to_Cleint[100]="msg: \"Server is avialable\" ";
    int countn=0;

    server_Info.sin_addr.s_addr=inet_addr("127.0.0.1"); //inet_addr(converst the string to network byte order
    server_Info.sin_family=AF_INET;
    server_Info.sin_port=htons(5000);
    int serverinfolen=sizeof(server_Info);
    int clientinfolen=sizeof(client_Info);

    response= bind(sok_slisten,(struct sockaddr*)&server_Info,serverinfolen); // u have to cast bcoz socketaddr_in is just for better
                                                                              // usage than sockaddr
    if(response!=SOCKET_ERROR)
        {
        cout<<"bind was sucess... \t\t"<<endl;
        }
    else
        {
            //WSAGetLastError gibt den letzten fehler
         cout<<"bind was error...... \t\t"<<WSAGetLastError()<<endl;
        }

/**************************************************************************/


/********************* NOW Listen *****************************************/

   response= listen(sok_slisten,SOMAXCONN); //warteschlage  mit max clients
    if(response!=SOCKET_ERROR)
        {
        cout<<"listen was sucess... \t\t"<<endl;
        }
    else
        {
        cout<<"listen was error...... \t\t"<<WSAGetLastError()<<endl; //WSAGetLastError gibt den letzten fehler
        }

/***********************************************************************/


/************** Entering While loop and Accept *************************/

while(1){


   sok_client=accept( sok_slisten,(struct sockaddr*)&client_Info,&clientinfolen);

    if(sok_client!=SOCKET_ERROR)
    {
       cout<<"Client accepted: "<<inet_ntoa(client_Info.sin_addr)<<" "<<ntohs(client_Info.sin_port)<<endl;
    }


//countn= recv(sok_client,recv_Data_from_Client,strlen(recv_Data_from_Client),0);
//cout<<"Recieved Data from client " <<hap<<endl;

/*Send to the Socket*/
response= send(sok_client,sent_Data_to_Cleint,100,0);
if(response==SOCKET_ERROR)
{
    cout<<"Error while send......";
}
response= recv(sok_client,recv_Data_from_Client,sizeof(recv_Data_from_Client),0);
recv_Data_from_Client[response]='\0';
if(response==SOCKET_ERROR)
{
    cout<<"Error while send......";
}
else{

    cout<<response<<" Bytes recieved"<<"  msg: ---> "<<recv_Data_from_Client<<endl;

}
}


/***********************************************************************/

/*******Close sockets********/
if(closesocket(sok_client)!=0){
    cout<<"Error while closing socket"<<endl;

}
if(closesocket(sok_slisten!=0)){
    cout<<"Error while closing socket"<<endl;

}
/*****************************/



/****Clean up WSA Library*****/
if(WSACleanup()!=0){
 cout<<"Cleanup failed "<<endl;
}
/*****************************/
    return 0;
}
