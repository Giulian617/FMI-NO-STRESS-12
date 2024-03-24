#include <iostream>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int N;
  cin >> N;
  int answer = 0;
  for (int i = 0; i < N; i++) {
    int h1, h2, is_doubled;
    cin >> h1 >> h2 >> is_doubled;
    answer += (is_doubled + 1) * (h2 - h1);
  }

  cout << answer << "\n";

  return 0;
}