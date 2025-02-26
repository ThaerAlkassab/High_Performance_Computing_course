#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char * argv[])
{
    int numtasks, rank, dest, source, rc, count, tag = 1;
    char inmsg,outmsg='x';
    MPI_Status Stat;
    
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    srand( time(NULL));
    
    if (rank ==0)
    {
        int answer = rand() % 100 + 1;
        int guess;
        int num = 0;
        int hint = 1; //hint -1 means lower, 0 is correct, +1 higher
        
        dest = 1;
        source = 1;
        printf("R%d: My  number is %d, guess it. \n",rank,answer);
        
        for(; guess != answer; num++){
        
            rc = MPI_Recv(&guess,1,MPI_INT,source,tag,MPI_COMM_WORLD,&Stat);
            printf("R%d received %d\n",rank,guess,source);
            if (guess < answer)
            {
                hint = 1;
                rc = MPI_Send(&hint,1,MPI_INT,dest,tag,MPI_COMM_WORLD);
            }
            if (guess > answer)
            {
                hint = -1;
                rc = MPI_Send(&hint,1,MPI_INT,dest,tag,MPI_COMM_WORLD);
            }
        }
        hint = 0;
        rc = MPI_Send(&hint,1,MPI_INT,dest,tag,MPI_COMM_WORLD);
        fprintf(stdout,"Correct! total guesses: %d \n", num);

        
        
    }
    else if (rank == 1)
    {
        
        int lower = 1;
        int maxi = 101;
    
        int guess;
        int hint = -2;
        
        while(hint != 0){
        
            int a = maxi - lower;
        
            guess = (rand() % (a + 1)) + lower;

            dest = 0;
            source = 0;

            printf("R%d: Sending guess %d\n",rank,guess,dest);
            rc = MPI_Send(&guess,1,MPI_INT,dest,tag,MPI_COMM_WORLD);
        
            rc = MPI_Recv(&hint,1,MPI_INT,source,tag,MPI_COMM_WORLD,&Stat);
            //print("R%d: I got a %d\n",rank,hint)
    	    if(hint == 1){
                printf("higher\n");
                lower = guess;  
            }
            if(hint == -1){
                printf("lower\n");
                maxi = guess;
            }
        }
    }
    MPI_Finalize();
    return 0;
}