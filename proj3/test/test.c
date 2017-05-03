#include<stdio.h>

long v = 0;
int main(){
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
    fprintf(fp, "writeval %p 3", &v);
    fflush(fp);
    printf("Now the v is %ld\n", v);
    return 0;
}