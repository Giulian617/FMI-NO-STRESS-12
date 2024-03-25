// beingsebi
#include <bits/stdc++.h>
using namespace std;
ifstream f("text.in");
ofstream g("text.out");
#define f cin
#define g cout

vector<int> ans;
int n, s;
int main()
{
    ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    f >> n;
    for (int i = 1, x; i <= n; ++i)
    {
        f >> x;
        x ^= s;
        if (x == 1)
        {
            ans.push_back(i);
            s ^= 1;
        }
    }
    g << ans.size() << '\n';
    for (auto it : ans)
        g << it << ' ';
    return 0;
}
