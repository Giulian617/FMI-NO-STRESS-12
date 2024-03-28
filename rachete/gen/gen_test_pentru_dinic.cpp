#include <bits/stdc++.h>

using namespace std;

int main(){
    ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);
        
    // cele comentate sunt pentru testele mici

    // const int nmin = 1;
    // const int nmax = 2; // categorii
    // const int fmax = 2; // cate chestii poti cupla de acelasi tip
    // const int pmax = 3; // cate piese maxim exista din fiecare

    const int nmin = 120;
    const int nmax = 150; // categorii
    const int fmax = 1000; // cate chestii poti cupla de acelasi tip
    const int pmax = 1000; // cate piese maxim exista din fiecare

    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

    int n1 = uniform_int_distribution<int>(nmin, nmax)(rng);
    int n2 = uniform_int_distribution<int>(nmin, nmax)(rng);
    int n3 = uniform_int_distribution<int>(nmin, nmax)(rng);
    cout << n1 << " " << n2 << " " << n3 << "\n";

    vector<int> v1, v2, v3;

    for(int i = 0; i < n1; i++){
        v1.push_back(uniform_int_distribution<int>(1, pmax)(rng));
        cout << v1.back();
        if(i != n1 - 1)
            cout << " ";
    }
    cout << "\n";

    for(int i = 0; i < n2; i++){
        v2.push_back(uniform_int_distribution<int>(1, pmax)(rng));
        cout << v2.back();
        if(i != n2 - 1)
            cout << " ";
    }
    cout << "\n";

    for(int i = 0; i < n3; i++){
        v3.push_back(uniform_int_distribution<int>(1, pmax)(rng));
        cout << v3.back();
        if(i != n3 - 1)
            cout << " ";
    }
    cout << "\n";

    vector<tuple<int, int, int, int>> vec;

    for(int i = 1; i <= n1; i++)
        for(int j = 1; j <= n2; j++)
            if(uniform_int_distribution<int>(0, 4)(rng) != 0)
                vec.emplace_back(1, i, j, uniform_int_distribution<int>(1, min({fmax, v1[i - 1], v2[j - 1]}))(rng));

    for(int i = 1; i <= n2; i++)
        for(int j = 1; j <= n3; j++)
            if(uniform_int_distribution<int>(0, 4)(rng) != 0)
                vec.emplace_back(2, i, j, uniform_int_distribution<int>(1, min({fmax, v2[i - 1], v3[j - 1]}))(rng));

    shuffle(vec.begin(), vec.end(), rng);

    cout << vec.size() << "\n";
    for(auto [a, b, c, d] : vec)
        cout << a << " " << b << " " << c << " " << d << "\n";

    return 0;
}
