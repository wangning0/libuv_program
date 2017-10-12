#include <stdio.h>
#include <unistd.h>

#include <uv.h>

void hare(void *arg)
{
    int tracklen = *((int*)arg);
    while(--tracklen
    {
        sleep(1);
        fprintf(stdout, "Hare another step\n");
    }
    fprintf(stdout, "Hare done step\n");
}

void tortoise(void *arg)
{
    int tracklen = *((int*)arg);
    while(--tracklen)
    {
        sleep(3);
        fprintf(stdout, "tortoise another step\n");
    }
    fprintf(stdout, "tortoise done step\n");
}

int main()
{
    int tracklen = 10;
    uv_thread_t hare_id;
    uv_thread_t tortoise_id;
    uv_thread_create(&hare_id, hare, &tracklen);
    uv_thread_create(&tortoise_id, tortoise, &tracklen);

    uv_thread_join(&hare_id);
    uv_thread_join(&tortoise_id);
}