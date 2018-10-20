#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <netinet/in.h>
char message[] = "Hello there!\n";
char buf1[sizeof(message)];
char ok[] = "Сообщение от клиента получено и успешно перенаправлено\n";
char neok[] = "Сообщение от клиента не получено\n";
char ee[1024];
int check=0;
int fs, fr;
int main()
{
    int sock;
    struct sockaddr_in addr;
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0)
    {
        perror("socket");
        exit(1);
    }
    addr.sin_family = AF_INET;
    addr.sin_port = htons(27017); //Или любой другой порт
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("connect");
        exit(2); 
    }
	fs=send(sock, message, sizeof(message), 0);
    	fr=recv(sock, buf1, sizeof(message), 0);

	if (fs==fr) {
		printf(buf1);
		fs=send(sock, ok, 1024, 0);
	} else {
		fs=send(sock, neok, 1024, 0);
	}

	fr=recv(sock, buf1, 1024, 0);
    	printf(buf1);


	printf("Завершить программу сервер?\n");
	scanf("%s",ee);
	fs=send(sock, ee, 1024, 0);

    close(sock);
    return 0;
}
