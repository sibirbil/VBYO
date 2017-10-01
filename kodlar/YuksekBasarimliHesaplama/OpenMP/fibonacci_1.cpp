#include <random>
#include <iostream>
#include <algorithm>
#include "omp.h"

#define N 1024 * 1024

using namespace std;

int fibo(int n) {
  if(n < 2) return n;
  return (fibo(n-1) + fibo(n-2));
}

int main(int argc, char** argv) {
  cout << "Main is started " << endl;
  
  std::default_random_engine e1(11);
  std::uniform_int_distribution<int> uniform_dist(1, 20);

  cout << "Tasks are being generated " << endl;
  int* tasks = new int[N];
  for(int i = 0; i < N; i++) {
    tasks[i] = uniform_dist(e1);
  }

  cout << "Tasks are being executed " << endl;
  double t1 = omp_get_wtime();
  int sum = 0;
  for(int i = 0; i < N; i++) {
    sum += fibo(tasks[i]);
  }
  double t2 = omp_get_wtime() - t1;
  cout << sum << " " << t2 << " seconds" << endl;

  cout << endl << "random: " << endl;
  for(int t = 1; t <= 32; t *= 2) {
    double t1 = omp_get_wtime();
    omp_set_num_threads(t);
    sum = 0;
#pragma omp parallel for reduction(+:sum) schedule(runtime)
    for(int i = 0; i < N; i++) {
      sum += fibo(tasks[i]);
    }
    double t2 = omp_get_wtime() - t1;
    cout << sum << " " << t2 << " seconds with " << t << " threads" << endl;
  }
  
  cout << endl << "sorted decreasing: " << endl;
  sort(tasks, tasks + N, std::greater<int>());
  for(int t = 1; t <= 32; t *= 2) {
    double t1 = omp_get_wtime();
    omp_set_num_threads(t);
    sum = 0;
#pragma omp parallel for reduction(+:sum) schedule(runtime)
    for(int i = 0; i < N; i++) {
      sum += fibo(tasks[i]);
    }
    double t2 = omp_get_wtime() - t1;
    cout << sum << " " << t2 << " seconds with " << t << " threads" << endl;
  }
  
  cout << endl << "sorted increasing: " << endl;
  sort(tasks, tasks + N, std::less<int>());
  for(int t = 1; t <= 32; t *= 2) {
    double t1 = omp_get_wtime();
    omp_set_num_threads(t);
    sum = 0;
#pragma omp parallel for reduction(+:sum) schedule(runtime)
    for(int i = 0; i < N; i++) {
      sum += fibo(tasks[i]);
    }
    double t2 = omp_get_wtime() - t1;
    cout << sum << " " << t2 << " seconds with " << t << " threads" << endl;
  }
  
  return 0;
}
