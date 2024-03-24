#include <iostream>
#include <vector>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int N;
  cin >> N;
  vector<int> answer;
  int is_swapped = 0;
  for (int i = 0; i < N; i++) {
    int state;
    cin >> state;
    state ^= is_swapped;
    if (state == 1) {
      answer.push_back(i);
      is_swapped ^= 1;
    }
  }

  cout << answer.size() << "\n";
  for (const int &i : answer) {
    cout << i + 1 << " ";
  }
  cout << "\n";

  return 0;
}