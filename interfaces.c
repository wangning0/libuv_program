/** 
 * 系统网络接口信息可以通过调用 ``uv_interface_addresses`` 来获得
 * 
*/

#include<stdio.h>

#include <uv.h>

int main(int argc, char *argv[])
{
    char buf[512];
    uv_interface_address_t *info;
    int count, i;

    uv_interface_addresses(&info, &count);
    i = count;

    printf("Number of interfaces: %d\n", count);
    while(i--)
    {
        uv_interface_address_t interface = info[i];
        printf("Name is %s\n", interface.name);
        printf("Internal? %d\n", interface.is_internal);

        if(interface.address.address4.sin_family == AF_INET)
        {
            uv_ip4_name((struct sockaddr_in *)&interface.address.address4.sin_addr, buf, sizeof(buf));
            printf("IPv4 address: %s\n", buf);
        }
        else if(interface.address.address4.sin_family == AF_INET6)
        {
            uv_ip6_name((struct sockaddr_in6 *)&interface.address.address4.sin_addr, buf, sizeof(buf));
            printf("IPv6 address: %s\n", buf);
        }
        printf("\n");
    }

    uv_free_interface_addresses(info, count);
}