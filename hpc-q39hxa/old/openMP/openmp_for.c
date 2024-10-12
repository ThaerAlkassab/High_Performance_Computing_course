#include <omp.h>
#include <stdio.h>

#define N 100

int main(int argc, char ** argv)
{
    int i;
    char values[N+1]; //int
    values[N]="\0";
    #pragma omp parallel for private(i) schedule(static,8)
    for (i=0;i<N;i++)
    {
        values[i] = (char) (48+omp_get_thread_num()); 
    }
    /*
    for(i=0;i<N;i++)
    {
        printf("%d",values[i]);
    }*/
    printf("%s",values);
    printf("\n");
    return 0;
}