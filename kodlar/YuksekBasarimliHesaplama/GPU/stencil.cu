#include <stdio.h>
#include <omp.h>
#include "common.h"

#define RADIUS        512
#define BLOCK_SIZE    512
#define NUM_ELEMENTS  1024000

__global__ void stencil_1d_device(int *in, int *out, int N) {
  int index = threadIdx.x + (blockIdx.x * blockDim.x);
  if(index < N) {
    // Apply the stencil
    int result = 0;
    for (int i = index ; i < index + 2*RADIUS + 1; i++)
      result += in[i];
    
    // Store the result
    out[index] = result;
  }
}

__global__ void stencil_1d_shared(int *in, int *out, int N) {
  __shared__ int temp[BLOCK_SIZE + 2 * RADIUS];
  int gindex = threadIdx.x + (blockIdx.x * blockDim.x) + RADIUS;
  if(gindex < N + RADIUS) {
    int lindex = threadIdx.x + RADIUS;
    
    // Read input elements into shared memory
    temp[lindex] = in[gindex];
    if (threadIdx.x < RADIUS) {
      temp[lindex - RADIUS] = in[gindex - RADIUS];
      temp[lindex + BLOCK_SIZE] = in[gindex + BLOCK_SIZE];
    }	
    
    // Make sure all threads get to this point before proceeding!
    __syncthreads();
    
    // Apply the stencil
    int result = 0;
    for (int offset = -RADIUS ; offset <= RADIUS ; offset++)
      result += temp[lindex + offset];
    
    // Store the result
    out[gindex-RADIUS] = result;
  }
}

int main() {
  unsigned int i;
  int h_in[NUM_ELEMENTS + 2 * RADIUS], h_out[NUM_ELEMENTS];
  int *d_in, *d_out;
  
  // Initialize host data
  for( i = 0; i < (NUM_ELEMENTS + 2*RADIUS); ++i )
    h_in[i] = 1; // With a value of 1 and RADIUS of 3, all output values should be 7
  
  // Allocate space on the device
  cudaCheck( cudaMalloc( &d_in, (NUM_ELEMENTS + 2*RADIUS) * sizeof(int)) );
  cudaCheck( cudaMalloc( &d_out, NUM_ELEMENTS * sizeof(int)) );
  
  //Timing structures
  cudaEvent_t start,stop;
  float elapsedTime;
  cudaEventCreate(&start);
  cudaEventCreate(&stop);
  
  // Copy input data to device
  cudaCheck( cudaMemcpy( d_in, h_in, (NUM_ELEMENTS + 2*RADIUS) * sizeof(int), cudaMemcpyHostToDevice) );
  
  cudaEventRecord(start,0);
  cudaCheck( cudaMemcpy( d_in, h_in, (NUM_ELEMENTS + 2*RADIUS) * sizeof(int), cudaMemcpyHostToDevice) );
  stencil_1d_shared<<< (NUM_ELEMENTS + BLOCK_SIZE - 1)/BLOCK_SIZE, BLOCK_SIZE >>> (d_in, d_out, NUM_ELEMENTS);
  cudaCheck( cudaMemcpy( h_out, d_out, NUM_ELEMENTS * sizeof(int), cudaMemcpyDeviceToHost) );
  cudaEventRecord(stop,0);
  cudaEventSynchronize(stop);
  cudaEventElapsedTime(&elapsedTime,start,stop);
  
  // Verify every out value is 2*RADIUS + 1
  for( i = 0; i < NUM_ELEMENTS; ++i ) {
    if (h_out[i] != 2 * RADIUS + 1) {
      printf("Element h_out[%d] == %d != %d\n", i, h_out[i], 2*RADIUS+1);
      break;
    }
  }
  if (i == NUM_ELEMENTS) printf("SUCCESS GPU_SHARED in %f mseconds!\n", elapsedTime);
  
  cudaEventRecord(start,0);
  cudaCheck( cudaMemcpy( d_in, h_in, (NUM_ELEMENTS + 2*RADIUS) * sizeof(int), cudaMemcpyHostToDevice) );
  stencil_1d_device<<< (NUM_ELEMENTS + BLOCK_SIZE - 1)/BLOCK_SIZE, BLOCK_SIZE >>> (d_in, d_out, NUM_ELEMENTS);
  cudaCheck( cudaMemcpy( h_out, d_out, NUM_ELEMENTS * sizeof(int), cudaMemcpyDeviceToHost) );
  cudaEventRecord(stop,0);
  cudaEventSynchronize(stop);
  
  cudaEventElapsedTime(&elapsedTime,start,stop);
  // Verify every out value is 2*RADIUS + 1
  for( i = 0; i < NUM_ELEMENTS; ++i ) {
    if (h_out[i] != 2 * RADIUS + 1) {
      printf("Element h_out[%d] == %d != %d\n", i, h_out[i], 2*RADIUS+1);
      break;
    }
  }
  if (i == NUM_ELEMENTS) printf("SUCCESS GPU_DEVICE in %f mseconds!\n", elapsedTime);
  
  double startt = omp_get_wtime();
#pragma omp parallel for
  for(int i = 0; i < NUM_ELEMENTS; i++) {
    int sum = 0;
    for(int j = i; j < i + 2*RADIUS + 1; j++) {
      sum += h_in[j];
    }
    h_out[i] = sum;
  }
  double endt = omp_get_wtime();
  
  for( i = 0; i < NUM_ELEMENTS; ++i ) {
    if (h_out[i] != 2 * RADIUS + 1) {
      printf("Element h_out[%d] == %d != %d\n", i, h_out[i], 2*RADIUS+1);
      break;
    }
  }
  if (i == NUM_ELEMENTS) printf("SUCCESS CPU in %f mseconds!\n", 1000 * (endt - startt));
  // Free out memory
  cudaFree(d_in);
  cudaFree(d_out);
  
  return 0;
}

