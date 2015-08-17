#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>

int main(void){
    int socket_nummer; // eine eindeutige  Identifikationsnummer für socket
    int laenge;  //wie vielen Bytes die Adressin formation  des  Sockets  besteht (sockaddr_in)
    struct sockaddr_in adressinfo; // also  die  Adresse  des  angesprochenen  Servers ( IP-Adresse,  Port-Nummer  etc.)
    int ergebnis; //  Ruckgabewert  der  Funktion connect
    
    socket_nummer=socket(AF_INET,SOCK_STREAM,0); // liefet Deskriptor(eine eindeutige zahl für socket)  des Sockets 
    
    /*   AF _ INET --> verwenden  die  Adressfamilie  des  Internet,   TCP  oder UDP  als Transportprotokoll. 
                    --> Man kann auch PF_INET verwenden und hat den gleichen wert wie AF_INET 
        SOCK_STREAM  --> TCP oder verende SOCK_DGRAM für UDP oder SOCK_RAW für ICMP
        
        0 --> Der function socket soll selber wählen den Transportprotokoll. Dieser feld ist für IP Protokoll
              überflüssig. Daher wird als 0 eingegeben. Weil wir SOCK_STREAM verwenden welcher implicit sagt das wir
              TCP verwenden wollen. 
    */
                    
    adressinfo.sin_family=AF_INET;   // Adressfamilie AF _INET 
    adressinfo.sin_addr.s_addr=inet_addr("127.0.0.1"); // Den strucktur in_addr welcher eine IP_adresse von 32 Bit hat 
                                                       // Den grund das dieser eine struct hat ist für einheitliche interface.
                                                        // Aber in AF_INT ist diser struct überflüssig aber man muss es verwenden
    
    adressinfo.sin_port=htons(80);  //Port 80  htons --> wandelt den 80 in BIG ENDIAN was von der Netzwerk protokoll verlangt würde.
    laenge=sizeof(adressinfo);   // Ermittelt den size of struct
   
    ergebnis =connect(socket_nummer,(struct sockaddr*)&adressinfo,laenge); // Verbinden 
    /* 
     socket_nummer --> ober erzeuget socket ni.
     &adressinfo-->  Die Funktion connect ()  erwartet die Adresse  einer Funktion vom Typ struct  sockaddr,  nicht  vom Typ 
     struct  sockaddr _in.  Dieses  Problem kann man durch eine Typumwandlung beseitigen: 
     leange --> length of struct
     
     
     Hinter  dem  Verbindungsaufbau  steckt  ein  Austausch  kurzer  Datenpakete,  in denen  TCP-Kommandos  versendet  
     werden .  Der  Client  schickt  die Meldung  SYN  (=  Synchronisation)  an  den  Server,  dessen  Adresse  und  Port-
     nummer in der Strukturvariablen address_info gespeichert ist. 
    
    */
    if(ergebnis==0){
        
        
        printf("\n Verbindung erfogreich");
    }
    else{
       
       /* 
        Error mittel strerror
        
        
        char *fehlertext;
        fehlertext  =  strerror(ergebnis); 
        printf("%s",fehlertext);
        */
        
        perror("Fehler beim verbindungsaufbau");
        
    }
    
    close(socket_nummer);
    return 0;
}


