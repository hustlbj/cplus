//本文件仅供学习源码使用，不能编译。。。。。
/** 
* 套接口地址结构
*/
/*IPv4 32-bit 地址结构体*/
struct in_addr {
	in_addr_t s_addr; //32-bit IPv4 address
};

/*IPv4套接口地址接口*/
struct sockaddr_in {
	uint8_t sin_len; //length of structure (16)
	sa_family_t sin_family; //AF_INET
	in_port_t sin_port; //16-bit TCP or UDP port 
	struct in_addr sin_addr; //32-bit IPv4 address, network byte ordered
	char sin_zero[8]; //unused
};

/***********************************************************************/
/*从进程到内核传递套接口地址结构的4个套接口函数
* bind connect sendto sendmsg
* 从内核到进程传递套接口地址结构的5个函数
* accept recvfrom recvmsg getpeername getsockname
* (sockaddr_in)serv.(in_addr)sin_addr.(in_addr_t)s_addr
* 通用套接口地址接口 <sys/socket.h> struct sockaddr
*/
struct sockaddr {
	uint8_t sa_len;
	sa_family_t sa_family; //AF_XXX
	char sa_data[14]; //protocol-specific address
};
/* ANSI C函数原型bind(int, struct sockaddr *, socklen_t)
*/
struct sockaddr_in serv;
int sockfd;
bind(sockfd, (struct sockaddr * )&serv, sizeof(serv));
/***********************************************************************/

/* IPv6套接口地址结构，头文件在<netinet/in.h>中

*/
struct in6_addr {
	uint8_t s6_addr[16]; //128-bit IPv6 address, network byte ordered
};
struct sockaddr_in6 {
	uint8_t sin6_len; //length of this struct (24)
	sa_family_t sin6_family; //AF_INET6
	in_port_t sin6_port; //transport layer port, network byte ordered
	uint32_t sin6_flowin; //priority & flow label, network byte ordered
	struct in6_addr sin6_addr; //IPv6 address, netwrork byte ordered

};
/* 4种套接口地址结构IPv4, IPv6, Unix域, 数据链路
* AF_INET, AF_INET6, AF_LOCAL, AF_LINK
* sockaddr_in, sockaddr_in6, sockaddr_un, sockaddr_dl
* -------*-------*-------*-------*-------*-------*-------*-------*------>
* len    |AF_INET|   sin_port    |     struct in_addr sin_addr   |
* -------*-------*-------*-------*-------*-------*-------*-------*------>
* len    |AF_INET6|  sin6_port   |        uint32_t sin6_flowin   |    128-bit struct sin6_addr 
* -------*-------*-------*-------*-------*-------*-------*-------*------>
* len    |AF_LOCAL|    path max 104 bits
* -------*-------*-------*-------*-------*-------*-------*-------*------>
* len    |AF_LINK| 
* -------*-------*-------*-------*-------*-------*-------*-------*------>
*/

/*网络字节序 <netinet/in.h>
* 小端little-endian字节序，将低序字节存储在低地址
* 大端big-endian字节序，将高序字节存储在低地址
*            <-------内存增大方向------
* 小端字节序：高序字节 | 低序字节
* 大端字节序：低序字节 | 高序字节
* 主机系统中两种格式都存在，把某给定系统所使用的字节序成为主机字节序
* 网络字节序采用大端模式
* htons, htonl, ntohs, ntohl
*/

/**
* 字节操纵函数，b开头和mem开头, <strings.h>, <string.h>
* b代表byte，起源于BSD，由几乎任何支持套接口函数的系统提供，
* mem代表memory，起源于ANSI C，由任何支持ANSI C库的系统提供
* bzero, bcopy, bcmp, 以const修饰参数，表明所限定的内筒不能由函数改动
* memset将目标中指定数据的字节置为c, memcpy的两个参数位置被bcopy的对调, memcmp
*/

/**
* 地址转换函数 <arpa/inet.h>
* inet_aton, inet_addr和inet_ntoa在点分十进制串与32位网络字节序之间转换IPv4地址
* inet_pton和inet_ntop对IPv4和IPv6地址都能处理
*/
string cp = "202.114.0.242";
inet_pton(AF_INET, cp, &foo.sin_addr);
//替代
foo.sin_addr.s_addr = inet_addr(cp);

char str[INET_ADDRSTRLEN];
ptr = inet_ntop(AF_INET, &foo.sin_addr, str, sizeof(str));
//替代
ptr = inet_ntoa(foo.sin_addr);

/**
* socket函数的协议族(地址族)family：AF_INET, AF_INET6, AF_LOCAL(AF_UNIX), AF_ROUTE, AF_KEY
* socket函数的套接口类型type：SOCK_STREAM, SOCK_DGRAM, SOCK_RAW
*/

/**
* fork函数和exec函数
* Unix中派生进程的唯一方法fork <unistd.h>, pid_t fork(void)
* 返回：在子进程中为0，在父进程中为子进程ID，-1表示出错
* 子进程只有一个父进程，可以通过getppif得到
* 父进程有许多子进程，如果想跟踪所有子进程ID，必须记住fork返回值
*/