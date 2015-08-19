# Sockets 
1. client_first.c --> simple client socket programm with descriptions
2. client_Asking_HTTP.c--> client asking for HTTP data from apache server on port 80
3. Client_Asking_HTTP_Saving.c --> client ask for HTTP data and save on file. It also eliminate the header.
4. simple_server.c --> This is a simple server which accept the connection but do nothing
5. client_for_simple_server.c ---> This is a simple client used for simple server (above file). 
6. HTTP_HTML_Server.c --> simple HTTP_HTML server which gives the html code as response.
7. HTTP_HTML_Server_DynamicHTML.c --> shows the ip adress of client in html (90% same as above).
8. parser_HTTP_GET.c --> parse the HTTP GET and gives the filename on the screen.
9. server_Post_reply.c --> server read the get command and send the form and read the data inside the form.
10. Server_read_the_file.c --> server read the file name and give the output.
11. Server_read_and_SendFile_by_char.c --> server reads the file and send it chrachter by charachter using fgetc()
12. Server_Send_Data.c -->sends data to the clients different formats.
13. winSock_Server.cpp & winSock_Client.cpp --> simple windows tcp server client.

Use "telnet IP_ADD PORTNO" command if u  have command line system to test the server.
