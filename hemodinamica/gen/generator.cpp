#include <iostream>
#include <vector>
#include <random>
using namespace std;

int main(int argc, char* argv[]) {
  if (argc != 3) {
    cerr << "Usage: " << argv[0] << " <N> <M>" << endl;
    return 1;
  }

  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<int> distrib(0, 1);

  int N, M;
  N = atoi(argv[1]);
  M = atoi(argv[2]);
  vector<vector<int>> A(N, vector<int>(M)), B(N, vector<int>(M));
  for (auto& row : A) {
    for (auto& x : row) {
      x = distrib(gen);
    }
  }
  for (auto& row : B) {
    for (auto& x : row) {
      x = distrib(gen);
    }
  }

  cout << N << " " << M << "\n";
  for (auto& row : A) {
    for (auto& x : row) {
      cout << x << " ";
    }
    cout << "\n";
  }
  for (auto& row : B) {
    for (auto& x : row) {
      cout << x << " ";
    }
    cout << "\n";
  }
  return 0;
}