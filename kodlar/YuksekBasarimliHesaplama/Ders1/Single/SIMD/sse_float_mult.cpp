//compile with -mavx

#include<iostream>
#include<ctime>
#include <immintrin.h> // Header for SSE and AVX.
#include <math.h>// Header for scalar math.
#include <sys/time.h>// Header for timing.
#include <stdlib.h> // Header for malloc.
#include <mm_malloc.h> // Header for _mm_malloc.

using namespace std;

void mulNaive(const float* a, const float* b, float* c, int N) {
  for(int i = 0; i < N; i++) {
    c[i] = a[i] * b[i];
  }
}

//assume N is divisible by 4
void mulUnroll(const float* a, const float* b, float* c, int N) {
  int i = 0;
  for(; i < N; i += 4) {
    c[i] = a[i] * b[i]; 
    c[i+1] = a[i+1] * b[i+1];
    c[i+2] = a[i+2] * b[i+2];
    c[i+3] = a[i+3] * b[i+3];
  }
}

//assume N is divisible by 4
void mulSSE(const float* a, const float* b, float* c, int N) {
  int i = 0;
  for(; i < N; i += 4) {
    __m128 a4 = _mm_load_ps(a + i);
    __m128 b4 = _mm_load_ps(b + i);
    __m128 sum = _mm_mul_ps(a4, b4);
    _mm_store_ps(c + i, sum);
  }
}

//assume N is divisible by 8                                                                                                                                                                                                                                             
void mulAVX(const float* a, const float* b, float* c, int N) {
  int i = 0;
  for(; i < N; i += 8) {
    __m256 a8 = _mm256_load_ps(a + i);
    __m256 b8 = _mm256_load_ps(b + i);
    __m256 sum = _mm256_mul_ps(a8, b8);
    _mm256_store_ps(c + i, sum);
  }
}


int main(int argc, char* argv[]) {
  int N = 1000 * atoi(argv[1]);
  float* a = (float*)_mm_malloc(N * sizeof(float), 32);
  float* b = (float*)_mm_malloc(N * sizeof(float), 32);
  float* c = (float*)_mm_malloc(N * sizeof(float), 32);

  for(int i = 0; i < N; i++) {
    a[i] = i;
    b[i] = i;
    c[i] = i;
  }

  clock_t begin = clock();	
  mulNaive(a,b,c,N);
  clock_t end = clock();
  double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
  cout << "naive version took " << elapsed_secs << " " << c[10] << endl;
  
  begin = clock();	
  mulUnroll(a,b,c,N);
  end = clock();
  elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
  cout << "unroll version took " << elapsed_secs  << " " << c[10] << endl;
  
  begin = clock();	
  mulSSE(a,b,c,N);
  end = clock();
  elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
  cout << "sse version took " << elapsed_secs  << " " << c[10] << endl;

  begin = clock();
  mulAVX(a,b,c,N);
  end = clock();
  elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
  cout << "avx version took " << elapsed_secs  << " " << c[10] << endl;

  _mm_free(a);
  _mm_free(c);
  
  return 1;
}
