#include<stdio.h>
#include<sys/socket.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#define PORT 8081
#define REQ 5
int main(int argc,char **argv){
int FTP_socket;
	FTP_socket=socket(AF_INET,SOCK_STREAM,0);//domain, type, protocol
	if(FTP_socket<0){
	perror("Socket coudn't creat\n");
	exit(0);
	}
	struct sockaddr_in remote_address,client_address;
	remote_address.sin_family=AF_INET;
	remote_address.sin_port=htons(PORT);
	remote_address.sin_addr.s_addr=INADDR_ANY;
	if(bind(FTP_socket,(struct sockaddr*) &remote_address,sizeof(remote_address))<0)
{
	printf("bind error\n");
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	if(listen(FTP_socket,REQ)<0)//REQ request can handle at a time
{printf("listen error\n");
		perror("listen");
		exit(EXIT_FAILURE);
	} 
	int client_socket;
socklen_t client=sizeof(client_address);
int k=0;
printf("Listening...\n");
while(1){
client_socket=accept(FTP_socket,(struct sockaddr*)&client_address,&client);
char buffer[1024];
FILE *fp;
char filename[64];
    sprintf (filename, "file%d.txt", k);
    k++;
read(client_socket,buffer,1024);
fp=fopen(filename,"w");
fprintf(fp,"%s",buffer);

printf("file successfully received\n");
printf("the new file created is %s\n",filename);
fclose(fp);
}
return 0;
}

