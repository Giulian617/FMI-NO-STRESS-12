// Mity O(N + inv_mod)
#include<cstdio>
const int NMAX=1000005;
typedef long long ll;
const ll MOD=1000000009;

ll fastExp(ll a, ll b)
{
    if(b==0)
        return 1;
    if(b==1)
        return a;
    ll x=fastExp(a, b/2);
    x=x*x%MOD;
    if(b&1)
        x=x*a%MOD;
    return x;
}

int N, K, M, C=1;
int col[NMAX];
ll fact[NMAX], ifact[NMAX];

void precalc()
{
    int i;

    fact[0]=1;
    for(i=1;i<NMAX;++i)
        fact[i]=fact[i-1]*i%MOD;
    ifact[NMAX-1]=fastExp(fact[NMAX-1], MOD-2);
    for(i=NMAX-2;i>-1;--i)
        ifact[i]=ifact[i+1]*(i+1)%MOD;
}

ll comb(int N, int K)
{
    if(N<0 || N<K || K<0)
        return 0;
    return fact[N]*ifact[N-K]%MOD*ifact[K]%MOD;
}

int main()
{
    int i, a, b;
    ll ans=0;

    precalc();
    scanf("%d%d", &N, &K);
    M=N-1;
    for(i=0;i<N;++i)
        scanf("%d", col+i);
    for(i=1;i<N;++i)
    {
        scanf("%d%d", &a, &b);
        if(col[--a]!=col[--b])
        {
            --M;
            ++C;
        }
    }

    K-=C;
    for(i=0;i<=M && i<=K;++i)
        ans=(ans+comb(M, i))%MOD;
    printf("%I64d\n", ans);

    return 0;
}