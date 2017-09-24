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
static long num_steps = 100000000;
double step;

int main () {
  const int MAX_T = 8;
  int i, t;
  double x, pi;
  double start_time, run_time;
  
  step = 1.0/(double) num_steps;

  for(t = 1; t <= MAX_T; t*=2) {
    start_time = omp_get_wtime();
    omp_set_num_threads(t);
    pi = 0.0;
#pragma omp parallel 
    {
      int i, nt;
      double x, sum = 0;
      
      i = omp_get_thread_num();
      nt = omp_get_num_threads();
      
      for (; i < num_steps; i += nt){
	x = (i + 0.5) * step;
	sum += 4.0/(1.0+x*x);
      }
#pragma omp atomic
      pi += sum;
    }
    
    pi = pi * step;
    
    run_time = omp_get_wtime() - start_time;
    printf("pi with %d threads: %.16lf in %lf seconds\n",t , pi,run_time);
  }	  
}
  
  
  

