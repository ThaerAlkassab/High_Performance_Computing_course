#include <stdio.h>
#include <omp.h>
#define N 100

int main( int argc, char ** argv )
{
    int i, sum, max, values[N];
    
    #pragma omp parallel for private(i) schedule(static,8)
    for( i = 0; i < N; i++ )
        values[i] = 2*i-1;
        
    sum = 0;
    #pragma omp parallel for private(i) schedule(static,8) reduction(+:sum)
    for(i=0;i<N;i++)
        sum += values[i];
    
    max = 0;
    #pragma omp parallel private(i)
    {
        #pragma omp for reduction(max:max)
        for( i = 0; i < N; i++ )
            if(values[i] > max )
                max = values[i];
    }
    printf("Sum: %d, Max: %d\n", sum, max );
    return 0;
}
