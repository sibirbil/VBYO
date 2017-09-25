//copmile with: g++ prefetch.cpp  -std=c++11 -O3
//run: ./a.out

#include <iostream>
#include <chrono>
using namespace std;

#define N 1024 * 1024 * 1024

int unroll_8(int* a, int* b, int& sum) {
  sum = 0;
  for (int i = 0; i < N-8; i+=8){
    sum += a[i]*b[i];
    sum += a[i+1]*b[i+1];
    sum += a[i+2]*b[i+2];
    sum += a[i+3]*b[i+3];
    sum += a[i+4]*b[i+4];
    sum += a[i+5]*b[i+5];
    sum += a[i+6]*b[i+6];
    sum += a[i+7]*b[i+7];
  }
  for (int i = N-8; i < N; i++)
    sum = sum + a[i]*b[i];
}

int prefetch(int* a, int* b, int& sum, int d) {
  sum = 0;

  for (int i = 0; i < d; i += 8){
    __builtin_prefetch (&a[i], 0, 1);
    __builtin_prefetch (&b[i], 0, 1);
  }
  
  for (int i = 0; i < N - d; i+=8){
    __builtin_prefetch (&a[i+d], 0, 1);
    __builtin_prefetch (&b[i+d], 0, 1);
    sum += a[i]*b[i];
    sum += a[i+1]*b[i+1];
    sum += a[i+2]*b[i+2];
    sum += a[i+3]*b[i+3];
    sum += a[i+4]*b[i+4];
    sum += a[i+5]*b[i+5];
    sum += a[i+6]*b[i+6];
    sum += a[i+7]*b[i+7];
  }
  for (int i = N-d; i < N; i++)
    sum = sum + a[i]*b[i];
}

int main() {
  cout << "An integer is " << sizeof(int) << " bytes "<< endl;

  int* a = new int[N];
  int* b = new int[N];
  
  for(int i = 0; i < N; i++) {
    a[i] = rand();
    b[i] = rand();
  }
  
  int sum;
  auto t1 = std::chrono::high_resolution_clock::now();
  unroll_8(a, b, sum);
  auto t2 = std::chrono::high_resolution_clock::now();
  cout << sum << " u8 " << chrono::duration_cast<chrono::milliseconds>(t2-t1).count() << " milliseconds\n";

  cout << "-----------------------------------------" << endl;
  cout << "Starting prefetching: " << endl;

  for(int k = 8; k <= 1024 * 64; k += 8) { 
    t1 = std::chrono::high_resolution_clock::now();
    prefetch(a, b, sum, k);
    t2 = std::chrono::high_resolution_clock::now();
    cout << sum << " " << k << " " << chrono::duration_cast<chrono::milliseconds>(t2-t1).count() << " milliseconds\n";
  }
  return 0;
}
