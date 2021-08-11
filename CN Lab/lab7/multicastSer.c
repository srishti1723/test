#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main ()
{
	int sock;
	char msg[1024];
	struct sockaddr_in groupaddr;
	struct in_addr localInterface;
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	memset(&groupaddr, 0, sizeof(groupaddr));
	groupaddr.sin_family = AF_INET;
	groupaddr.sin_addr.s_addr = inet_addr("226.1.1.1");
	groupaddr.sin_port = htons(1234);
	localInterface.s_addr = inet_addr("127.0.0.1"); 
	setsockopt(sock, IPPROTO_IP, IP_MULTICAST_IF, (char *)&localInterface,
	sizeof(localInterface));
	printf("Enter message : ");
	fgets(msg, 1024, stdin);
	msg[strlen(msg)-1] = '\0'; 
	sendto(sock, msg, sizeof(msg), 0, (struct sockaddr*)&groupaddr,
	sizeof(groupaddr));
	printf("Message Sent.\n");
	return 0;
}
