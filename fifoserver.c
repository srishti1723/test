// fifoserver

#include<stdio.h>
#include<signal.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>
#define FIFO1 "/tmp/fifo.1"
#define FIFO2 "/tmp/fif0.2"
#define MAX 4096
void server(int readfd, int writefd)
{
	int fd;
        ssize_t n;
        char buf[MAX+1];
        printf("\nreading from pipe file name\n");
	if((n=read(readfd,buf,MAX))==0)
		printf("End of the file while reading the path name\n");
	buf[n]='\0';
	printf("%s",buf);
	if((fd=open(buf,O_RDONLY))<0)
	{
		strcpy(buf,"SERVER ERROR");
		n=strlen(buf);
		write(writefd,buf,n);
	}
	else
	{
		printf("reading from pipe the contents of file and wriring to client\n");
		while((n=read(fd,buf,MAX))>0)
		{
			write(writefd,buf,n);
			write(STDOUT_FILENO,buf,n);
		}
		close(fd);
	}
}
int main(int argc,char **argv)
{
        int readfd,writefd;
	printf("Creating pipe1\n");
	if(mkfifo(FIFO1,0777)<0&&(errno!=EEXIST))
	printf("\nCan't create %s\n",FIFO1);
	printf("Creating pipe2\n");
        if(mkfifo(FIFO2,0777)<0&&(errno!=EEXIST))
	{
		unlink(FIFO1);
		printf("Create %s\n",FIFO2);
	}
	readfd=open(FIFO1,O_RDONLY,0);
	writefd=open(FIFO2,O_WRONLY,0);
	server(readfd,writefd);
}
 
