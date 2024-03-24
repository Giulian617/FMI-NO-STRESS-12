#include <iostream>
#include <vector>
#include <assert.h>

using namespace std;

int main(int argc, char** argv) {
  int N = atoi(argv[1]), K = atoi(argv[2]);

  int MAX_N = atoi(argv[3]);

  cerr << N << " " << K << " " << MAX_N << "\n";

  assert(1 <= K && K <= N && N <= MAX_N);

  cout << N << " " << K << "\n";

  return 0;
}