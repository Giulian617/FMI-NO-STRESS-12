#include<bits/stdc++.h>
using namespace std;
int N,L,W;
struct cerc
{
    double c,r;
    cerc(int x, int y) : c(double(x)), r(double(y))
    {
        r=sqrt(r*r-double(W)*W/4.0);
    }
    bool operator < (cerc &a) const
    {
        return c-r<a.c-a.r;
    }
};
void solve()
{
    vector<cerc>v;
    for(int i=0;i<N;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        if(y*2>=W) v.push_back(cerc(x, y));
    }
    N=v.size();
    if(N==0)
    {
        printf("Imposibil\n");
        return;
    }
    sort(v.begin(),v.end());
    double Left=0;
    int poz=0, cnt=0;
    while(poz<N)
    {
        double R=Left;
        while(poz<N && v[poz].c-v[poz].r<=Left)
        {
            if (v[poz].r + v[poz].c > R)
            {
                R = v[poz].r + v[poz].c;
            }
            poz++;
        }
        if(R==Left)
            { printf("Imposibil\n"); return; }
        Left=R;
        cnt++;
        if(Left >= L)
            { printf("%d\n",cnt); return; }
    }
    printf("Imposibil\n");
    return;
}

int main()
{
    scanf("%d%d%d",&N,&L,&W);
    solve();
    return 0;
}