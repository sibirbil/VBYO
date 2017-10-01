//copmiel with: gcc prefetch_binary.c -DDO_PREFETCH -o with-prefetch -std=c11 -O3
//              gcc prefetch_binary.c -o no-prefetch -std=c11 -O3
//run with: perf stat -e L1-dcache-loads,L1-dcache-load-misses,LLC-loads,LLC-load-miss

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "omp.h"

int binarySearch(int *array, int number_of_elements, int key) {
  int low = 0, high = number_of_elements-1, mid;
  while(low <= high) {
    mid = (low + high)/2;
#ifdef DO_PREFETCH
    // low path
    __builtin_prefetch (&array[(mid + 1 + high)/2], 0, 1);
    // high path
    __builtin_prefetch (&array[(low + mid - 1)/2], 0, 1);
#endif
    
    if(array[mid] < key)
      low = mid + 1; 
    else if(array[mid] == key)
      return mid;
    else if(array[mid] > key)
      high = mid-1;
  }
  return -1;
}
int main() {
  int SIZE = 1024*1024*512;
  int *array =  malloc(SIZE*sizeof(int));
  for (int i=0;i<SIZE;i++){
    array[i] = i;
  }
  int NUM_LOOKUPS = 1024*512;
  srand(10);
  int *lookups = malloc(NUM_LOOKUPS * sizeof(int));
  for (int i = 0; i < NUM_LOOKUPS;i++){
    lookups[i] = rand() % SIZE;
  }

  double t1 = omp_get_wtime();
  for (int i=0; i < NUM_LOOKUPS;i++){
    int result = binarySearch(array, SIZE, lookups[i]);
  }
  printf("%.2f seconds\n", omp_get_wtime() - t1);
  
  free(array);
  free(lookups);
}
