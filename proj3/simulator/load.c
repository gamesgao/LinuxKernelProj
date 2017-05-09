#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <math.h>
#include <sys/mman.h>
long getCurrentTime()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        return -1;
    }
    int cpu = floor(atof(argv[1]) * 1000);
    int mem = atoi(argv[2]);
    int alloc_size = mem * 1024 * 1024;
    char *fakemem = malloc(alloc_size);
    if(fakemem == NULL){
        perror("malloc");
        return -1;
    }
    for(int i=0;i<alloc_size;i++){
        fakemem[i] = 0;
    }
    printf("CPU: %d\n", cpu);
    printf("Mem: %d\n", mem);
    while (1)
    {
        long currTime = getCurrentTime();
        long passTime = 0;
        while (passTime < cpu)
        {
            passTime = getCurrentTime() - currTime;
        }
        usleep((1000 - cpu)*1000);
    }
    return 0;
}