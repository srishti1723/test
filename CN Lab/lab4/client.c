#include <stdio.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main()
{
	int welcome,sockfd,n;
	char buffer[1024],fname[50];
	struct sockaddr_in addr;
	int i;

	sockfd=socket(PF_INET,SOCK_STREAM,0);
	
	addr.sin_family=AF_INET;
	addr.sin_port=htons(7891);
	addr.sin_addr.s_addr=inet_addr("127.0.0.1");

	connect(sockfd,(struct sockaddr*)&addr,sizeof(addr));
	
	printf("\nEnter File Name ");
	scanf("%s",fname);

	send(sockfd,fname,sizeof(fname),0);

	printf("\nReceived File data\n");
	printf("---------------------------------");
	while((n=recv(sockfd,buffer,sizeof(buffer),0))>0)
	{
		buffer[n]='\0';
		printf("%s",buffer);

	}
		
	return 0;

}