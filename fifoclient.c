// fifoclient

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
void client (int readfd, int writefd)
{
	ssize_t n;
	ssize_t len;
	char buf[MAX];
	printf("\nEnter file name\n");
	fgets(buf,MAX,stdin);
	len=strlen(buf);
	if(buf[len-1]=='\n')
		len--;
	printf("\nWrite the file_name %s into pipe",buf);
	write(writefd,buf,len);
	printf("\nreading from pipe the contents of filename and display it\n");
	while((n=read(readfd,buf,MAX))>0)
		write(STDOUT_FILENO,buf,n);
}
int main(int argc,char **argv)
{
	int readfd,writefd;
	writefd=open(FIFO1,O_WRONLY,0);
	readfd=open(FIFO2,O_RDONLY,0);
	printf("\nCall Client");
	client(readfd,writefd);
	close(readfd);
	close(writefd);
	unlink(FIFO1);
	unlink(FIFO2);
}

