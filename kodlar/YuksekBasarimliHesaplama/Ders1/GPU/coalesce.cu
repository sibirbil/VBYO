#include <stdio.h>
#include "common.h"

#define TIMES 1024
#define N (1024 * 1024)

__global__ void dummy(int *a, int *b) {
  int index = blockDim.x * threadIdx.x + blockIdx.x;
  
  int sum = 0;
  for(int i = 0; i < TIMES; i++) {
    sum += a[(index + i) % N];
  }

  b[index] = sum;
}

//dummy kernel; each thread adds some portion of a and store it in b
__global__ void dummy2(int *a, int *b) {
  int index = blockDim.x * blockIdx.x + threadIdx.x;

  int sum = 0;
  for(int i = 0; i < TIMES; i++) {
    sum += a[(index + i) % N];
  }

  b[index] = sum;
}

int main() {
  /******************************************************************************/
  //Preparing the memory
  int *a, *b;
  int *d_a, *d_b;
  size_t size = N * sizeof( int );
  
  cudaCheck(cudaMalloc( (void **) &d_a, size ));
  cudaCheck(cudaMalloc( (void **) &d_b, size ));
  
  /* allocate space for host copies of a, b, c and setup input values */
  a = (int *)malloc( size );
  b = (int *)malloc( size );
  
  for(int i = 0; i < N; i++ ) {
    a[i] = 1;
    b[i] = 0;
  }
  /******************************************************************************/
  
  /******************************************************************************/
  //Timing
  cudaEvent_t start,stop;
  float elapsedTime;
  
  cudaEventCreate(&start);
  cudaEventCreate(&stop);
  
  cudaEventRecord(start,0);
  /* copy inputs to device */
  /* fix the parameters needed to copy data to the device */
  cudaCheck(cudaMemcpy(d_a, a, size, cudaMemcpyHostToDevice));
  cudaCheck(cudaMemset(d_b, 0, size));
  /* launch the kernel on the GPU */
  /* insert the launch parameters to launch the kernel properly using blocks and threads */
  dummy<<<1024, 1024>>>(d_a, d_b);
  
  /* copy result back to host */
  /* fix the parameters needed to copy data back to the host */
  cudaDeviceSynchronize();
  cudaCheck(cudaPeekAtLastError());
  cudaCheck(cudaMemcpy(b, d_b, size, cudaMemcpyDeviceToHost ));
  cudaEventRecord(stop,0);
  cudaEventSynchronize(stop);
  cudaEventElapsedTime(&elapsedTime,start,stop);
  /******************************************************************************/
  for( int i = 0; i < N; i++) {
    if(b[i] != TIMES) {
      printf("GPU Error: value b[%d] = %d\n", i, b[i]);
      break;
    }
  }
  printf("GPU time is: %lf seconds\n", elapsedTime / 1000);
  
  cudaEventRecord(start,0);
  /* copy inputs to device */
  /* fix the parameters needed to copy data to the device */
  cudaCheck(cudaMemcpy(d_a, a, size, cudaMemcpyHostToDevice));
  cudaCheck(cudaMemset(d_b, 0, size));
  /* launch the kernel on the GPU */
  /* insert the launch parameters to launch the kernel properly using blocks and threads */
  dummy2<<<1024, 1024>>>(d_a, d_b);

  /* copy result back to host */
  /* fix the parameters needed to copy data back to the host */
  cudaDeviceSynchronize();
  cudaCheck(cudaPeekAtLastError());
  cudaCheck(cudaMemcpy(b, d_b, size, cudaMemcpyDeviceToHost ));
  cudaEventRecord(stop,0);
  cudaEventSynchronize(stop);
  cudaEventElapsedTime(&elapsedTime,start,stop);
  /******************************************************************************/
  for( int i = 0; i < N; i++) {
    if(b[i] != TIMES) {
      printf("GPU Error: value b[%d] = %d\n", i, b[i]);
      break;
    }
  }
  printf("GPU time is: %lf seconds\n", elapsedTime / 1000);


  /* clean up */
  free(a);
  free(b);
  cudaFree( d_a );
  cudaFree( d_b );
  
  return 0;
} /* end main */
