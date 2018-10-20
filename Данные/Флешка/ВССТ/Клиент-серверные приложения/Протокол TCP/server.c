#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <netinet/in.h>
char message1[] = "123456789\n";
char mmm[1024] ="da";
char ch;
unsigned int sz;
int main()
{
    int sock, listener;
    struct sockaddr_in addr;
    char buf[1024];
    int bytes_read, bytes_read1, bytes_read2;
    listener = socket(AF_INET, SOCK_STREAM, 0);
    if(listener < 0)
    {
        perror("socket");
        exit(1);
    }
    
    addr.sin_family = AF_INET;
    addr.sin_port = htons(27017);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
  
        perror("bind");
        exit(2);
    }
    listen(listener, 1);
	
    while(1)
    {
    sz=sizeof(addr);
    sock = accept(listener, (struct sockaddr *)&addr, &sz);
    //printf ("\n");
        if(sock < 0)
        {
            perror("accept");
            exit(3);
        }
  
        while(1)
    
        {
            bytes_read = recv(sock, buf, 1024, 0);
	    if(bytes_read <= 0) break;
	    printf(buf);
            send(sock, buf, bytes_read, 0);
	    break;
	}
	    
	while(1) 
	{
	    bytes_read1 = recv(sock, buf, 1024, 0);
	    if(bytes_read1 <= 0) break;
	    printf(buf);
	    send(sock, message1, sizeof(message1), 0);
	    break;
	}
    
        
	while(1) 
	{
	    bytes_read2 = recv(sock, ch, 1024, 0);
	    if(bytes_read1 <= 0) break;
	    if (strcmp(ch,mmm)==0) {
		printf("Cервер остановлен по требованию клиента");
		break;
		} 
	}
	close(sock);
	break;
    }
    
    return 0;
}
