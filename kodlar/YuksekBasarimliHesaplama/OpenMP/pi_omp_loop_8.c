/*
  
  This program will numerically compute the integral of
  
  4/(1+x*x) 
  
  from 0 to 1.  The value of this integral is pi -- which 
  is great since it gives us an easy way to check the answer.
  
  The is the original sequential program.  It uses the timer
  from the OpenMP runtime library
  
  History: Written by Tim Mattson, 11/99.
  
*/
#include <stdio.h>
#include <omp.h>
static long num_steps = 1024 * 1024 * 1024;
double step;
int main () {
  int i, t;
  double x, pi, sum = 0.0;
  double start_time, run_time;
  
  step = 1.0/(double) num_steps;
 
  for(t = 1; t <= 16; t*=2) { 
    pi = 0;
    start_time = omp_get_wtime();
#pragma omp parallel num_threads(t) private(x) 
    {
#pragma omp for reduction(+:sum) 
      for (i = 0; i < num_steps; i++){
	x = (i + 0.5)*step;
	sum = sum + 4.0/(1.0+x*x);
      }      
    }
    pi = step * sum;
    run_time = omp_get_wtime() - start_time;
    printf("pi with %d threads: %.16lf in %lf seconds\n",t , pi,run_time);
  }
}	  





