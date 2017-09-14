#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#define PORT 8081

int main(int argc,char**argv)
{
struct sockaddr_in server_address;
int client_socket;
client_socket=socket(AF_INET,SOCK_STREAM,0);
if (client_socket < 0)
	{
		printf("\n Socket creation error \n");
		return -1;
	}
server_address.sin_family=AF_INET;
server_address.sin_addr.s_addr=INADDR_ANY;
server_address.sin_port=htons(PORT);
if(inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr)<=0) 
	{
		printf("\nInvalid address/ Address not supported \n");
		return -1;
	}
if(connect(client_socket,(struct sockaddr*)&server_address,sizeof(server_address))<0){
		printf("\nConnection Failed \n");
		return -1;
	}
char buffer[1024];
FILE *f;
f=fopen("sfile.txt","r");
fscanf(f,"%s",buffer);
write(client_socket,buffer,100);
fclose(f);
printf("the file was sent successfully\n");
}
