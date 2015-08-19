#pragma comment(lib,"ws2_32.lib")
#include<cstdio>
#include<iostream>
#include<WinSock2.h>
#include<Windows.h>

using namespace std;

int main(void)
{
long recievce;
char sendbuf[100];
char recbuf[100];
WSADATA wsaData;
SOCKET sConnect;
sockaddr_in conpar;

recievce=WSAStartup(MAKEWORD(2,0),&wsaData);
if(recievce==0)
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

sConnect=socket(AF_INET,SOCK_STREAM,0);

if(sConnect!=INVALID_SOCKET)
        {
        cout<<"socket was sucess... \t\t"<<endl;
        }
    else
        {
            //WSAGetLastError gibt den letzten fehler
         cout<<"socket was error.... \t\t"<<WSAGetLastError()<<endl;
        }

conpar.sin_addr.s_addr=inet_addr("127.0.01");
conpar.sin_family=AF_INET;
conpar.sin_port=htons(5000);
int conparlen=sizeof(conpar);


recievce=connect(sConnect,(struct sockaddr*)&conpar,conparlen);
if(recievce!=SOCKET_ERROR)
        {
        cout<<"connect was sucess... \t\t"<<endl;
        }
    else
        {
            //WSAGetLastError gibt den letzten fehler
         cout<<"connect was error.... \t\t"<<WSAGetLastError()<<endl;
        }

while(1){

   memset(&sendbuf,0,sizeof(sendbuf));
   memset(&recbuf,0,sizeof(recbuf));

   recievce=recv(sConnect,recbuf,sizeof(recbuf),0);
   recbuf[recievce]='\0';
   if(recievce==SOCKET_ERROR)
   {
     cout<<"Error at recievce "<< WSAGetLastError()<<endl;

   }
   else
    {
    cout<<recievce<<"Bytes recieved --> "<<recbuf<<endl;


   }

   cout<<"Now Sending :::::";
   cin.getline(sendbuf,100);

   recievce=send(sConnect,sendbuf,strlen(sendbuf),0);
  if(recievce==SOCKET_ERROR)
   {
     cout<<"Error at Send  "<< WSAGetLastError()<<endl;

   }
   else
    {
    cout<<recievce<<" Bytes Sent : msg -->"<<recbuf<<endl;


   }
}
closesocket(sConnect);
WSACleanup();



    return 0;
}
