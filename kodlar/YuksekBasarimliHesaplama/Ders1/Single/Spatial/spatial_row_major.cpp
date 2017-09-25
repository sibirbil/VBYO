#include<iostream>

using namespace std;

#define N 10000
int main () {
  int i, j;
  clock_t start, end;
  
  double** b = new double*[N];
  for (i = 0; i < N; i++) { 
    b[i] = new double[N];
    for (j = 0; j < N; j++) {
      b[i][j] = i * j + 0.0f;
    }
  }

  double* column_sum = new double[N];  
  for (i = 0; i < N; i++) { 
    column_sum[i] = 0.0;
  }
  
  start = clock();
  for (j = 0; j < N; j++) {
    for (i = 0; i < N; i++) { 
      column_sum[i] += b[j][i];
    }
  }
  end = clock();
  cout << "row major version took " << ((double)(end - start)) / CLOCKS_PER_SEC << endl; 

  for (i = 0; i < N; i++) {
    delete [] b[i];
  } 
  delete [] b;
  delete [] column_sum;
  return 0;
}
