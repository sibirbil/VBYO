
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
//#include "random.h"

int main (int argc, char** argv)
{
   long Ncirc = 0;
   double pi, x, y;
   double rmax = RAND_MAX;
   long num_trials = atoi(argv[1]);

   //   seed(-1, 1);  // The circle and square are centered at the origin

   double start = omp_get_wtime();
#pragma omp parallel
   {
#pragma omp for private(x,y) 
     for(int i=0;i<num_trials; i++) {
       x = rand()/rmax;
       y = rand()/rmax;
       if (x*x + y*y <= 1) {
#pragma omp atomic
	 Ncirc++;
       }
     }
   }
   
    pi = 4.0 * ((double)Ncirc/(double)num_trials);
    double end = omp_get_wtime();
    printf("\n %ld trials, pi is %lf (time %lf)\n",num_trials, pi, end - start);

    return 0;
}
	  





