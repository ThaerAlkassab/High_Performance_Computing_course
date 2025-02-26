#include <stdio.h>
#include <math.h>
#include <sys/time.h>

#define res_cal 0.68268948119303L //interval a=-1, b=1, mean = 0, std = 1
typedef long double myf;
typedef int myi;

double get_time(){
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return tv.tv_sec + 0.000001 * tv.tv_usec;
}


myf gauss_bell_formula(myf x, myf mean, myf std){
    return  1/(std*sqrt(2*M_PI)) *exp(pow((x-mean)/(std),2) * -0.5); 
}

int main(int argc, char ** argv)
{
    //Initial parameters user input
    myi n = (myi) atoll(argv[1]); // number of intervals (myi)atoll(argv[1])
    myf a = (myf) atoll(argv[2]); // start point
    myf b = (myf) atoll(argv[3]); // end point
    myf mean = (myf) atoll(argv[4]); //mean of the bell
    myf std = (myf) atoll(argv[5]);; //std of the bell
    
    myf h = (b-a)/n; //interval width
    myf res; // result of integral
    myf x1;
    myf x2;
    myi i;

    double start = get_time();
    
    for (i = 1; i < n; i=i+2) { // n/2 iterations
        x1 = a  + i* h;
        x2 = x1 + h;
        res += (4.0*gauss_bell_formula(x1,mean,std)+2.0*gauss_bell_formula(x2,mean,std));
    }
    
    res += (gauss_bell_formula(a,mean,std) + gauss_bell_formula(b,mean,std));
    res *= h/3;

    double end = get_time();    

    //print results
    printf("Results: %18.16Lf\n", (long double)res);
    printf("Error: %18.16Lf\n", (long double)(res - res_cal));
    printf("Time: %8.6f\n", end - start);
    return 0;
}