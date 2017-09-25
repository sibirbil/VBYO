#include <stdio.h>
#include <omp.h>
#include <iostream>
using namespace std;

int main ()  {
  int id = omp_get_thread_num();
  cout << "Hello " << id << endl;
}
