#include <iostream>
#include <time.h>
extern "C"
{
#include <immintrin.h>
}
 
using namespace std;
 
int main(){
  const int col = 128, row = 64, num_trails = 100000;
 
  float w[row][col];
  float x[col];
  float y[row];
  float scratchpad[8];
  for (int i=0; i<row; i++) {
    for (int j=0; j<col; j++) {
      w[i][j]=(float)(rand()%1000)/800.0f;
    }
  }
  for (int j=0; j<col; j++) {
    x[j]=(float)(rand()%1000)/800.0f;
  }
 
  clock_t t1, t2;
 
  t1 = clock();
  for (int r = 0; r < num_trails; r++)
    for(int j = 0; j < row; j++)
      {
	float sum = 0;
	float *wj = w[j];
	for(int i = 0; i < col; i++) {
	 sum += wj[i] * x[i];
	}
	y[j] = sum;
  }
  t2 = clock();
  float diff = (((float)t2 - (float)t1) / CLOCKS_PER_SEC ) * 1000;
  cout<<"Time taken: "<<diff<<endl;

    cout << "\t";
  for (int i=0; i<row; i++) {
    cout<<y[i]<<", ";
  }
  cout<<endl;
 
  __m256 ymm0, ymm1, ymm2, ymm3, ymm4, ymm5, ymm6, ymm7,
    ymm8, ymm9, ymm10, ymm11, ymm12, ymm13, ymm14, ymm15;
 
  t1 = clock();
  const int col_reduced = col - col%64;
  const int col_reduced_32 = col - col%32;
  for (int r = 0; r < num_trails; r++)
    for (int i=0; i<row; i++) {
      float res = 0;
      for (int j=0; j<col_reduced; j+=64) {
        ymm8 = __builtin_ia32_loadups256(&x[j]);
        ymm9 = __builtin_ia32_loadups256(&x[j+8]);
        ymm10 = __builtin_ia32_loadups256(&x[j+16]);
        ymm11 = __builtin_ia32_loadups256(&x[j+24]);
        ymm12 = __builtin_ia32_loadups256(&x[j+32]);
        ymm13 = __builtin_ia32_loadups256(&x[j+40]);
        ymm14 = __builtin_ia32_loadups256(&x[j+48]);
        ymm15 = __builtin_ia32_loadups256(&x[j+56]);
 
        ymm0 = __builtin_ia32_loadups256(&w[i][j]);
        ymm1 = __builtin_ia32_loadups256(&w[i][j+8]);
        ymm2 = __builtin_ia32_loadups256(&w[i][j+16]);
        ymm3 = __builtin_ia32_loadups256(&w[i][j+24]);
        ymm4 = __builtin_ia32_loadups256(&w[i][j+32]);
        ymm5 = __builtin_ia32_loadups256(&w[i][j+40]);
        ymm6 = __builtin_ia32_loadups256(&w[i][j+48]);
        ymm7 = __builtin_ia32_loadups256(&w[i][j+56]);
 
        ymm0 = __builtin_ia32_mulps256(ymm0, ymm8 );
        ymm1 = __builtin_ia32_mulps256(ymm1, ymm9 );
        ymm2 = __builtin_ia32_mulps256(ymm2, ymm10);
        ymm3 = __builtin_ia32_mulps256(ymm3, ymm11);
        ymm4 = __builtin_ia32_mulps256(ymm4, ymm12);
        ymm5 = __builtin_ia32_mulps256(ymm5, ymm13);
        ymm6 = __builtin_ia32_mulps256(ymm6, ymm14);
        ymm7 = __builtin_ia32_mulps256(ymm7, ymm15);
 
        ymm0 = __builtin_ia32_addps256(ymm0, ymm1);
        ymm2 = __builtin_ia32_addps256(ymm2, ymm3);
        ymm4 = __builtin_ia32_addps256(ymm4, ymm5);
        ymm6 = __builtin_ia32_addps256(ymm6, ymm7);
        ymm0 = __builtin_ia32_addps256(ymm0, ymm2);
        ymm4 = __builtin_ia32_addps256(ymm4, ymm6);
        ymm0 = __builtin_ia32_addps256(ymm0, ymm4);
 
        __builtin_ia32_storeups256(scratchpad, ymm0);
        for (int k=0; k<8; k++)
          res += scratchpad[k];
      }
      for (int j=col_reduced; j<col_reduced_32; j+=32) {
        ymm8 = __builtin_ia32_loadups256(&x[j]);
        ymm9 = __builtin_ia32_loadups256(&x[j+8]);
        ymm10 = __builtin_ia32_loadups256(&x[j+16]);
        ymm11 = __builtin_ia32_loadups256(&x[j+24]);
 
        ymm0 = __builtin_ia32_loadups256(&w[i][j]);
        ymm1 = __builtin_ia32_loadups256(&w[i][j+8]);
        ymm2 = __builtin_ia32_loadups256(&w[i][j+16]);
        ymm3 = __builtin_ia32_loadups256(&w[i][j+24]);
 
        ymm0 = __builtin_ia32_mulps256(ymm0, ymm8 );
        ymm1 = __builtin_ia32_mulps256(ymm1, ymm9 );
        ymm2 = __builtin_ia32_mulps256(ymm2, ymm10);
        ymm3 = __builtin_ia32_mulps256(ymm3, ymm11);
 
        ymm0 = __builtin_ia32_addps256(ymm0, ymm1);
        ymm2 = __builtin_ia32_addps256(ymm2, ymm3);
        ymm0 = __builtin_ia32_addps256(ymm0, ymm2);
 
        __builtin_ia32_storeups256(scratchpad, ymm0);
        for (int k=0; k<8; k++)
          res += scratchpad[k];
      }
      for (int l=col_reduced_32; l<col; l++) {
        res += w[i][l] * x[l];
      }
      y[i] = res;
    }
  t2 = clock();
  diff = (((float)t2 - (float)t1) / CLOCKS_PER_SEC ) * 1000;
  cout<<"Time taken: "<<diff<<endl;

  cout << "\t";
  for (int i=0; i<row; i++) {
    cout<<y[i]<<", ";
  }
  cout<<endl;

  return 0;
}
