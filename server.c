#include <stdio.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main()
{
	struct sockaddr_in addr;
	int sockfd,new_sock,fd,n;
	char buffer[1024],fname[50];

	sockfd=socket(PF_INET,SOCK_STREAM,0);

	addr.sin_family=AF_INET;
	addr.sin_port=htons(7891);
	addr.sin_addr.s_addr=inet_addr("127.0.0.1");

	bind(sockfd,(struct sockaddr*)&addr,sizeof(addr));

	printf("Server is online");

	listen(sockfd,5);

	new_sock=accept(sockfd,NULL,NULL);
	
	recv(new_sock,fname,50,0);
	printf("\nRequesting for file:%s\n",fname);

	fd=open(fname,O_RDONLY);

	if(fd<0)
	{
		send(new_sock,"\nFile Not Found\n",15,0);
	}
	else
	{
		while((n=read(fd,buffer,sizeof(buffer)))>0)
		{
			send(new_sock,buffer,n,0);
		}
	}

	printf("File Content Sent");
	close(sockfd);
	return 0;

}