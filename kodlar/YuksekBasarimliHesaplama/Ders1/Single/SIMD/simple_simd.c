/* compiled with -msse2, etc*/

//#include <mmintrin.h>  /* MMX */
//#include <xmmintrin.h> /* SSE */
#include <emmintrin.h> /* SSE2 */
//#include <pmmintrin.h> /* SSE3 */
//#include <tmmintrin.h> /* SSSE3 */
//#include <smmintrin.h> /* SSE4.2 SSE4.1 */

#include<sys/time.h>
#include<time.h>
#include<stdio.h>

int main() {
  int N = 1024 * 1024 * 256;
  clock_t start_t, end_t, total_t;

  float z1[] = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};
  float z2[] = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};
  float z3[8];
  float z4[8];
  float tmp[8];

    
  int i, j;
  for(i=0; i<8; i++) {
    z3[i] = z4[i] = tmp[i] = 0;
  }

  start_t = clock();
  for (j=0;j<N; j++) {
    for(i=0; i<8; i++) {
      z3[i] += z1[i] + z2[i];
    }
  }
  end_t = clock();
  printf("time = %lf\n", (double)(end_t - start_t) / CLOCKS_PER_SEC);

  start_t = clock();
  for (j=0; j<N; j++) {
    __m128 *v_z1 = (__m128 *)z1;
    __m128 *v_z2 = (__m128 *)z2;
    __m128 *v_z3 = (__m128 *)z4;
    __m128 *v_tmp = (__m128 *)tmp;
    
    for(i=0; i<2; i++) {
      *v_tmp = _mm_add_ps(*v_z1, *v_z2);
      *v_z3 = _mm_add_ps(*v_z3, *v_tmp);
      v_z1++;
      v_z2++;
      v_z3++;
    }
  }
  end_t = clock();

  printf("time = %lf\n", (double)(end_t - start_t) / CLOCKS_PER_SEC);

  for (i=0; i<8; i++) {
    if (z3[i] != z4[i]) {printf("Wrong.\n");}
    printf("%d %f %f\n", i, z3[i], z4[i]);
  }
  printf("Correct, results matched.\n");
  return 0;
}
