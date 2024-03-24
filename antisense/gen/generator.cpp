#include <iostream>
#include <vector>
#include <cstring>
#include <random>
#include <assert.h>

using namespace std;

const int MAX_N = 500'000'000;
const int MAX_T = 1'000'000'000;

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " N l r" << std::endl;
    return 1;
  }

  int N = atoi(argv[1]);

  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<int> dis(-MAX_N, MAX_N);

  int l = dis(gen) % N, r = dis(gen) % N;
  if (l > r) {
    swap(l, r);
  }

  vector<int> A(N);
  for (int i = 0; i < N; i++) {
    A[i] = dis(gen);
    if (i >= l && i <= r) {
      if (dis(gen) % 10 < 7) {
        A[i] = abs(A[i]);
      } 
    } else {
      if (dis(gen) % 10 < 7) {
        A[i] = -abs(A[i]);
      }
    }
  }

  vector<int> first_arr, second_arr;
  first_arr.reserve(N);
  second_arr.reserve(N);
  for (int& a : A) {
    // write x as sum of two numbers
    int first = dis(gen), second = a + first;
    first_arr.push_back(first);
    second_arr.push_back(second);
  }

  cout << N << "\n";
  for (const int& x : first_arr) {
    cout << x << " ";
    assert(abs(x) <= MAX_T);
  }
  cout << "\n";
  for (const int& x : second_arr) {
    cout << x << " ";
    assert(abs(x) <= MAX_T);
  }
  cout << "\n";

  return 0;
}