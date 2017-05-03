#include<stdio.h>
#include<stdlib.h>

long v = 0;
int main(int argc,char *argv[]){
    int temp = 409;
    if(argc > 1){
        temp =  atoi(argv[1]);
    }
    printf("temp is %d\n", temp);
    printf("the v address is %p\n", &v);
    printf("Now the v is %ld\n", v);
    printf("Change the val of v by write int to mtest\n");
    FILE* fp;
    if((fp=fopen("/proc/mtest","w"))==NULL)
    {
        printf("The file %s can not be opened.\n","student.txt");
        return -1;
    }
    // long temp =(long) &v;
    printf("writeval %p %x\n", &v, temp);
    fprintf(fp, "writeval %p %x", &v, temp);
    fflush(fp);
    printf("Now the v is %ld\n", v);
    return 0;
}