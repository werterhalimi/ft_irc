// Server side C/C++ program to demonstrate Socket
// programming
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 6667
int main(int argc, char const* argv[])
{
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = { 0 };
    char* hello = ":servername 001 shalimi :Welcome to the BeyondIRC IRC Network shalimi!shalimi@127.0.0.1\r\n:servername 002 shalimi :Your host is test.salut.com, running version 0.0.1\r\n:servername 003 shalimi :This server was created 20:12:31 Jan 16 2013\r\n:servername 004 shalimi :test.salut.com 2.0 ras\r\n";
	char *hello2  = "221    RPL_UMODEIS fuck off";
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
  
    // Forcefully attaching socket to the port 8080

	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR , &opt, sizeof(opt)))
	{
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
  
    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr*)&address,
             sizeof(address))
        < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((new_socket
         = accept(server_fd, (struct sockaddr*)&address,
                  (socklen_t*)&addrlen))
        < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }
	int i = 0;
   	valread = read(new_socket, buffer, 513);
	printf("%i %s\n", i++, buffer);
   // send(new_socket, hello1, strlen(hello1), 0);
    //send(new_socket, hello2, strlen(hello2), 0);
    //send(new_socket, hello3, strlen(hello3), 0);
	send(new_socket, hello, strlen(hello), 0);
	while (1) 
	{
		valread = read(new_socket, buffer, 513);
		buffer[valread] = 0;
		if (strncmp("PRIVMSG", buffer, 4) == 0)
		{
			printf("prv\n");
			char * msg = ":user PRIVMSG #test :Now I'm logged in\r\n";
			send(new_socket, msg, strlen(msg), 0);
		}
		if (strncmp("PING", buffer, 4) == 0)
		{
			printf("pong\n");
			send(new_socket, ":servername PONG 127.0.0.1\r\n", strlen(":servername PONG 127.0.0.1\r\n"), 0);
		}
		char * msg = "@account=hax0r :user PRIVMSG #atheme :Now I'm logged in\r\n";
		send(new_socket, msg, strlen(msg), 0);
		printf("valread: %i\n", valread);
		printf("%i %s\n", i++, buffer);
	}
    // closing the connected socket
    close(new_socket);
    // closing the listening socket
    shutdown(server_fd, SHUT_RDWR);
    return 0;
}
