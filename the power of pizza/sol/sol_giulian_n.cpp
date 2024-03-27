#include<bits/stdc++.h>
using namespace std;
int Z,h1,h2,pizza,ans;
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin>>Z;
    for(int i=1; i<=Z; i++)
    {
        cin>>h1>>h2>>pizza;
        if(pizza==1)
            ans+=(h2-h1)*2;
        else
            ans+=(h2-h1);
    }
    cout<<ans;
    return 0;
}
