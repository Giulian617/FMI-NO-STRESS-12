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

  i64 answer = A.front() - B.front();
  for (int l = 0; l < N; l++) {
    for (int r = l; r < N; r++) {
      i64 sum = 0;
      for (int i = l; i <= r; i++) {
        sum += A[i] - B[i];
      }
      answer = max(answer, sum);
    }
  }

  cout << answer << "\n";

  return 0;
}