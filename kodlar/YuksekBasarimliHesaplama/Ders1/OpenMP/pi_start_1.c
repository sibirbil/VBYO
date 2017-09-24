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
#include <stdlib.h>

long long num_steps = 100000000;
double step;
int main (int argc, char** argv)
{
  long long int i;
  double x, pi, sum = 0.0;
  double start_time, run_time;

  step = 1.0/(double) num_steps;
  start_time = omp_get_wtime();
  
  for (i = 0; i < num_steps; i++){
    x = (i + 0.5)*step;
    sum = sum + 4.0/(1.0+x*x);
  }
  
  pi = step * sum;
  run_time = omp_get_wtime() - start_time;
  printf(" pi                  is 3.14159265358979323846264338327950");
  printf("\n pi with %lld steps is %.20lf in %lf seconds\n ",num_steps,pi,run_time);
}	  





