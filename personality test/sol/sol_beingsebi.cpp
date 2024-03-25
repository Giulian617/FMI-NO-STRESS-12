#include <bits/stdc++.h>
using namespace std;
vector<int> v;
pair<int, int> desc(int x)
{
    pair<int, int> ans = {-1, -1};
    for (int i = 2, t; i * i <= x; i++)
    {
        t = 0;
        while (x % i == 0)
            x /= i, t++;
        ans = max(ans, {t, i});
    }
    if (x != 1)
        ans = max(ans, {1, x});
    return ans;
}
int main()
{
    int n;
    cin >> n;
    v.resize(n);
    assert(1 <= n && n <= 10000);
    for (int &i : v)
    {
        cin >> i;
        assert(2 <= i && i <= 100000);
    }
    sort(v.begin(), v.end(), [](int a, int b)
         {
             auto sa = desc(a), sb = desc(b);
             if (sa.first != sb.first)
                 return sa.first > sb.first;
             if (sa.second != sb.second)
                 return sa.second > sb.second;
             return a > b;
         });
    cout << v[0];
}
