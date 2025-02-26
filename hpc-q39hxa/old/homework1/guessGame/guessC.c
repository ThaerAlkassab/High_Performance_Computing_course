#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void human_guess(){
    int guess = 0;
    int num = 0;
    int answer;
    
    printf("Guess a number \n");
    
    srand(time(0));
    answer = rand() % 100 + 1;
    
    for (; guess != answer; num++){
        fprintf(stdout, "Enter guess: ");
        fscanf(stdin,"%d",&guess);
        if(guess < answer)
            fprintf(stdout,"Higher\n");
        if(guess > answer)
            fprintf(stdout,"Lower\n");
    }
    fprintf(stdout,"Correct! total guesses: %d \n", num);
}

void cpu_guess(){
    int guess = 0;
    int lower = 1;
    int maxi = 101;
    int num = 0;
    int answer;

    
    printf("Select a number \n");
    fscanf(stdin,"%d",&answer);
    
    srand(time(0));
    
    for (; guess != answer; num++){
        int a = maxi - lower;
        guess = (rand() % (a + 1)) + lower;
        printf("CPU guess %d \n", guess);
        if(guess < answer){
            fprintf(stdout,"Higher\n");
            lower = guess;
        }
        if(guess > answer){
            fprintf(stdout,"Lower\n");
            maxi = guess;
        }
    }
    fprintf(stdout,"Correct! total guesses: %d \n", num);
}

void cpu_vs_cpu(){
    int guess = 0;
    int lower = 1;
    int maxi = 101;
    int num = 0;
    int answer;

    answer = rand() % 100 + 1;
    printf("CPU1 number is %d\n", answer);
    
    srand(time(0));
    
    for (; guess != answer; num++){
        int a = maxi - lower;
        guess = (rand() % (a + 1)) + lower;
        printf("CPU guess %d \n", guess);
        if(guess < answer){
            fprintf(stdout,"Higher\n");
            lower = guess;
        }
        if(guess > answer){
            fprintf(stdout,"Lower\n");
            maxi = guess;
        }
    }
    fprintf(stdout,"Correct! total guesses: %d \n", num);
}

int main()
{
    int mode;
    printf("1) Human guess \n");
    printf("2) cpu guess \n");
    printf("3) cpu vs cpu \n");
    fscanf(stdin,"%d",&mode);
    
    if (mode == 1){
        human_guess();
    }
    else{
        if (mode == 2){
            cpu_guess();
        }
        else{
            cpu_vs_cpu();
        }
    }
    return 0;
}