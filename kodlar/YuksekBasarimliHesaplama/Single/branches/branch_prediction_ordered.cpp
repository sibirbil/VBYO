#include <algorithm>
#include <vector>
#include <iostream>

// If the data are sorted like shown here the program runs about
// 6x faster (on my test machine, with -O2)


int main() {
  // generate data
  const size_t arraySize = 32768;
  std::vector<int> data(arraySize);

  for (unsigned c = 0; c < arraySize; ++c) {
    data[c] = std::rand() % 256;
  }

  long long sum = 0;
  for (unsigned c = 0; c < arraySize; ++c) {
    for (unsigned i = 0; i < 100000; ++i) {
      if (data[c] >= 128)
	sum += data[c];
    }
  }
  std::cout << "sum = " << sum << std::endl;
}
