#include <stdio.h>

#include <uv.h>

uv_loop_t *loop;


void recur_getip(struct addrinfo *ai)
{
    if(ai)
    {
        char addr[17] = {'\0'};
        uv_ip4_name((struct sockaddr_in*)ai->ai_addr, addr, 16);
        printf("%s\n", addr);
        if(ai->ai_next)
        {
            recur_getip(ai->ai_next);
        }
    }
}

void on_resolved(uv_getaddrinfo_t* req, int status, struct addrinfo *res)
{
    if(status < 0)
    {
        printf("void address. \n");
        return ;
    }
    recur_getip(res);
    uv_freeaddrinfo(res);
}

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        printf("Usage: %s ip\n", argv[0]);
        return 1;
    }
    loop = uv_default_loop();
    
    struct addrinfo hints;
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = 0;
    hints.ai_flags = AI_PASSIVE;

    uv_getaddrinfo_t resolver;
    int r = uv_getaddrinfo(loop, &resolver, on_resolved, argv[1], NULL, &hints);

    if(r)
    {
        printf("get address info error \n");
        return 1;
    }
    uv_run(loop, UV_RUN_DEFAULT);
    return 0;
}