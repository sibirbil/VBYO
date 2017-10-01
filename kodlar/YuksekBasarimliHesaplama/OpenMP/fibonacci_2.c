#include <omp.h>
#include <stdlib.h>
#include <stdio.h>

#define N 43
int seq_fib(int n)  {
   int x, y;
   if (n < 2) {
      return n;
   } else {
      x = seq_fib(n - 1);
      y = seq_fib(n - 2);
      return x + y;
   }
}

int par_fib(int n) {
  int x, y;
  if (n < 2) {
    return n;
  }

#pragma omp task shared(x) 
  x = par_fib(n - 1);
  
#pragma omp task shared(y) 
  y = par_fib(n - 2);
  
#pragma omp taskwait
  return x + y;
}

int main()  {
  double start, end;
  start = omp_get_wtime();
  int result = seq_fib(N);
  end = omp_get_wtime();
  printf("seq took %lf secs : result %d\n", end - start, result);

  int t;
  for(t = 1; t <= 32; t *= 2) {
    omp_set_num_threads(t);
    start = omp_get_wtime();
    int result;
#pragma omp parallel
    {
#pragma omp single
      result = par_fib(N);
    }
    end = omp_get_wtime();
    printf("%d threads took %f secs : result %d\n", t, end - start, result);
  }
  return 0;
}

