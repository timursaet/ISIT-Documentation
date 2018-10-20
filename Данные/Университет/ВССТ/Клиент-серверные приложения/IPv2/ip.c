/*  ip2.c  */
// Этот листинг выдает локальный (127.0.0.1) и локальный-приватный (например, 192.168.ххх.ххх) IP-адреса компьютера, на котором он будет запущен.
#include <net/if.h>
#include <stdio.h>
#include <string.h>
#include <linux/socket.h>
//#include <linux/ioctl.h>
#include <linux/types.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <inttypes.h>
#include <netdb.h>

struct ifparam {
 __u32 ip;  // IP адрес
 __u32 mask;  // маска подсети
} ifp;
int getifconf(__u8 *intf, struct ifparam *ifp)
{
 int fd;
 struct sockaddr_in s;
 struct ifreq ifr; // см. <linux/if.h>
 memset((void *)&ifr, 0, sizeof(struct ifreq));
 if((fd = socket(AF_INET,SOCK_DGRAM,0)) < 0)  return (-1);
 sprintf(ifr.ifr_name,"%s",intf);
/*
* Определяем IP адрес сетевого интерфейса
*/
 if(ioctl(fd, SIOCGIFADDR, &ifr) < 0) {
  perror("ioctl SIOCGIFADDR");
  return -1;
 }
 memset((void *)&s, 0, sizeof(struct sockaddr_in));
 memcpy((void *)&s, (void *)&ifr.ifr_addr, sizeof(struct sockaddr));
 memcpy((void *)&ifp->ip, (void *)&s.sin_addr.s_addr, sizeof(__u32));
 return 0;
}
int main()
{
/*
* Получаем параметры сетевого интерфейса eth0
*/
 if(getifconf("wlp2s0", &ifp) < 0) {
  perror("getifconf");
  return -1;
 }
// Получаем локальный IP-адрес (127.0.0.1 или loopback)
  char *ac = "localhost";
  struct hostent *hosten= gethostbyname(ac);
int cnt;
u_long IpAddr;
for( cnt=0 ; hosten->h_addr_list[cnt] != NULL ; cnt++ ) {
  int Ip1,Ip2,Ip3,Ip4;
  IpAddr=ntohl(*((u_long *)(hosten -> h_addr_list[cnt])));
// 0xff - это в 16-ричном формате число 255
  Ip1=(int)( IpAddr>>24 ) & 0xff;
  Ip2=(int)( IpAddr>>16 ) & 0xff;
  Ip3=(int)( IpAddr>>8 ) & 0xff;
  Ip4=(int)( IpAddr&0xff );
  printf("Локальный IP-адрес (loopback) \%d = \%d.\%d.\%d.\%d\n",cnt,Ip1,Ip2,Ip3,Ip4);
 }
// Получаем приватный (он тоже называется локальным) IP-адрес
int IpAddr_my;
  // Исправьте следующую строчку в целях корректности
  for( cnt=0 ; hosten->h_addr_list[cnt] != NULL ; cnt++ ) {
  int Ip1,Ip2,Ip3,Ip4;
  IpAddr_my = ifp.ip;
  Ip1=(int)( IpAddr_my>>24 ) & 0xff;
  Ip2=(int)( IpAddr_my>>16 ) & 0xff;
  Ip3=(int)( IpAddr_my>>8 ) & 0xff;
  Ip4=(int)( IpAddr_my & 0xff);
// Почему IP-адрес выводится в обратном порядке, но результат получается правильный?
  printf("Приватный IP-адрес \%d = \%d.\%d.\%d.\%d\n",cnt,Ip4,Ip3,Ip2,Ip1);
 }
/*
* Отобразим полученные параметры сетевого интерфейса
*/
 printf("IpAddr: %lu\n", IpAddr);
 printf("IP адрес (__U32): %"PRIi32"\n",ifp.ip);
 return 0;
}

