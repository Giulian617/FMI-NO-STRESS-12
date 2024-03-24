#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <cmath>
#include <numeric>
#include <limits>

using namespace std;
using f64 = double;
using Cricle = pair<int, int>;
using Interval = pair<f64, f64>;

const f64 INF = numeric_limits<f64>::infinity();

tuple<int, int, vector<Cricle>> read_input(istream& in) {
  in.tie(nullptr);
  int N, W, H;
  in >> N >> W >> H;
  vector<Cricle> circles(N);
  for (auto& [x, r] : circles) {
    in >> x >> r;
  }
  return {W, H, circles};
}

vector<Interval> get_intervals(const vector<Cricle>& circles, int H) {
  vector<Interval> intervals;
  for (const auto& [x, r] : circles) {
    if (2 * r >= H) {
      f64 d = sqrt((f64)r * r - (f64)H * H / (f64)4);
      intervals.emplace_back(x - d, x + d);
    }
  }
  return intervals;
}

int count_min_intervals(vector<Interval>& intervals, const Interval& target) {
  intervals.emplace_back(INF, INF);
  int N = intervals.size();
  vector<int> order(N);
  iota(order.begin(), order.end(), 0);
  sort(order.begin(), order.end(), [&](const int lhs, const int rhs) {
    return intervals[lhs].first < intervals[rhs].first;
  });
  vector<int> answer;
  f64 current_left = target.first;
  int candidate = -1;
  for (int i = 0; i < N; ) {
    if (intervals[order[i]].first <= current_left) {
      if (candidate == -1 || intervals[candidate].second < intervals[order[i]].second) {
        candidate = order[i];
      }
      i++;
    } else {
      current_left = intervals[candidate].second;
      answer.push_back(candidate);
      if (intervals[order[i]].first > intervals[answer.back()].second || 
          intervals[answer.back()].second >= target.second) {
        break;
      }
    }
  }
  if (answer.empty() || intervals[answer.back()].second < target.second) {
    return -1;
  }

  return answer.size();
}

int main() {
  ios_base::sync_with_stdio(false);

  auto [W, H, circles] = read_input(std::cin);
  auto intervals = get_intervals(circles, H);

  int answer = count_min_intervals(intervals, make_pair((f64)0, (f64)W));
  if (answer == -1) {
    cout << "Imposibil\n";
  } else {
    cout << answer << "\n";
  }

  return 0;
}