/*  ip1.c  */
#include <sys/ioctl.h>
#include <net/if.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
struct in_addr addr;
int get_addr(const char *intf, struct in_addr *addr)
{
 int fd;
 if((fd = socket(AF_INET,SOCK_DGRAM,0)) < 0) return -1;
 struct ifreq ifr;
 memset((void *)&ifr, 0, sizeof(struct ifreq));
 sprintf(ifr.ifr_name,"%s",intf);
 if(ioctl(fd, SIOCGIFADDR, &ifr) < 0) // 2- получает адрес устройтсво
 {
 perror("ioctl SIOCGIFADDR");
 return -1;
 }
 *addr = ((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr;
 return 0;
}
int main()
{
char io[30];
printf("Введите имя интерфейса "); scanf("%s",&io);
 if (get_addr(io, &addr) < 0)
 {
 perror("get_addr");
 return -1;
 }
 printf("Приватный IP-адрес %s\n", inet_ntoa(addr));
 return 0;
}
