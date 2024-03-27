#include <iostream>
using namespace std;
const int DIM=305;
int l,L,H,Q1,Q2,x1,x2,y1,y2,z1,z2,v;
long long ans,a[DIM][DIM][DIM],sp[DIM][DIM][DIM];
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin>>l>>L>>H>>Q1>>Q2;
    for(int q=1;q<=Q1;q++)
    {
        cin>>x1>>y1>>z1>>x2>>y2>>z2>>v;
        a[x1][y1][z1]+=v;
        a[x2+1][y1][z1]-=v;
        a[x1][y2+1][z1]-=v;
        a[x2+1][y2+1][z1]+=v;
        a[x1][y1][z2+1]-=v;
        a[x2+1][y1][z2+1]+=v;
        a[x1][y2+1][z2+1]+=v;
        a[x2+1][y2+1][z2+1]-=v;
    }
    for(int i=1;i<=l;i++)
        for(int j=1;j<=L;j++)
            for(int k=1;k<=H;k++)
                a[i][j][k]=a[i-1][j][k]+a[i][j-1][k]+a[i][j][k-1]-a[i-1][j-1][k]-a[i-1][j][k-1]-a[i][j-1][k-1]+a[i-1][j-1][k-1]+a[i][j][k];
    for(int i=1;i<=l;i++)
        for(int j=1;j<=L;j++)
            for(int k=1;k<=H;k++)
                sp[i][j][k]=sp[i-1][j][k]+sp[i][j-1][k]+sp[i][j][k-1]-sp[i-1][j-1][k]-sp[i-1][j][k-1]-sp[i][j-1][k-1]+sp[i-1][j-1][k-1]+a[i][j][k];
    for(int q=1;q<=Q2;q++)
    {
        cin>>x1>>y1>>z1>>x2>>y2>>z2;
        cout<<sp[x2][y2][z2]-sp[x1-1][y2][z2]-sp[x2][y1-1][z2]+sp[x1-1][y1-1][z2]-sp[x2][y2][z1-1]+sp[x1-1][y2][z1-1]+sp[x2][y1-1][z1-1]-sp[x1-1][y1-1][z1-1]<<'\n';
    }
    return 0;
}
