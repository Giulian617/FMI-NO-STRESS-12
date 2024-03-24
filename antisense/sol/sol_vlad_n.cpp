#include <iostream>
#include <vector>
using namespace std;
using i64 = int64_t;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int N;
  cin >> N;

  vector<int> A(N), B(N);
  for (int &x : A) {
    cin >> x;
  }
  for (int &x : B) {
    cin >> x;
  }

  vector<int> C(N);
  for (int i = 0; i < N; ++i) {
    C[i] = A[i] - B[i];
  }

  i64 answer = C.front(), current_sum = 0;
  for (const int x : C) {
    current_sum += x;
    answer = max(answer, current_sum);
    current_sum = max(current_sum, (i64)0);
  }

  cout << answer << "\n";

  return 0;
}