#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

/*
// 结构体对象
struct addrinfo {
    int              ai_flags;
    int              ai_family;//AF_INET,AF_INET6或者AF_UNSPEC
    int              ai_socktype;//SOCK_STREAM or SOCK_DGRAM
    int              ai_protocol;//0
    size_t           ai_addrlen;//往下参数在hints中均为0或NULL
    struct sockaddr *ai_addr;
    char            *ai_canonname;
    struct addrinfo *ai_next;
};
*/

/*
int getaddrinfo(const char *node, const char *service,
                       const struct addrinfo *hints,
                       struct addrinfo **res);
*/
int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        printf("usage: %s ip\n", argv[0]);
        return 1;
    }
    struct addrinfo hints;
    struct addrinfo *res, *cur;
    struct sockaddr_in *addr;
    char ipbuf[16];
    int ret;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = 0;
    hints.ai_flags = AI_PASSIVE;

    ret = getaddrinfo(argv[1], NULL, &hints, &res);
    
    if(ret != 0)
    {
        printf("get address info error\n");
        return 1;
    }
    for(cur = res; cur != NULL; cur = cur ->ai_next)
    {
        addr = (struct sockaddr_in*)cur->ai_addr;
        printf("%s\n", inet_ntop(AF_INET, &addr->sin_addr, ipbuf, sizeof(ipbuf)));
    }
    freeaddrinfo(res);
    return 0;
}