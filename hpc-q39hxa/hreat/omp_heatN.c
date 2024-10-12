#include <stdlib.h>
#include <stdio.h>

void printout( double t, double * T, int N )
{
    int i;
    int imax = 10;
    printf("%8.0f ", t); // prints time in s.ms
    for( i = 0; i < imax; i++ )
    {
        int idx = i * (N+1)/(imax-1) -1;
        double Ti = T[ idx ];
        printf("%7.2f ", Ti - 273.0 ); // print temp in C
    }
    printf("\n");
}

int main( int argc, char ** argv )
{
    int		i;	// indexing space
    int		t;	// indexing time
    int		N = 10240000;	// number of cells
    int		time = 512;	// number of timesteps
    int		printtime = time / 20 ;
    
    double	Tinit = 300.0;	// Initial temperature (K)
    double	T1 = 1000.0;	// BC Hot (K)
    double	T2 = 200.0;	// BC Cold (K)
    
    double	dx = 0.01;	// size of cells (m)
                                // L = N*dx
                                // L = 102400 (m)
    double	dt = 0.001;	// time step (s)
                                // tau = time * dt
                                // tau = 1.024 (s)
    double	alpha = 0.03;	// conduction coefficient
    
    double	k = alpha * dt / dx / dx;
    
    double	* T = (double *)malloc( (N+2) * sizeof(double) )+1;
    double	* DT = (double *)malloc( N * sizeof(double) );
//    double	v1, v2, v3;
//    double	* Tnext = (double *)malloc( (N+2) * sizeof(double) )+1;
    
    // setup initial condition
    #pragma omp parallel for schedule(static) private(i)
    for( i = 0; i<N ; i++ )
        T[i] = Tinit;
    
    // boundary conditions
    T[-1] = T1; T[N] = T2;
//    Tnext[-1] = T1; Tnext[N] = T2;
    
    for( t=0; t<time;t++ )
    {
        if( (t % printtime) == 0 )
            printout( t, T, N );
        // calculate change in temperature
        #pragma omp parallel for schedule(static) private(i)
        for( i = 0; i < N ; i++ )
            DT[i] = k*( T[i+1] + T[i-1] - 2*T[i] );
        // update temperature
        #pragma omp parallel for schedule(static) private(i)
        for( i = 0; i < N ; i++ )
            T[i] += DT[i];
//        for( i = 0; i < N ; i++ )
//            Tnext[i] = T[i] + k*( T[i+1] + T[i-1] - 2*T[i] );
//        double * swap = Tnext;
//        Tnext = T;
//        T = swap;
        
    }
    printout( time, T, N );
            
    free( DT );
    free( T - 1 );
    return 0;
}
