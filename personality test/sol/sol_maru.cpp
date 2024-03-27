#include<cstdio>
#include<algorithm>
using namespace std;
pair<int,int> personality(int nr)
{
    int d=2, personality = -1, exp_max = 0;
    while(d*d <= nr)
    {
        int e=0;
        while(nr%d == 0)
        {
            e++;
            nr/=d;
        }
        if(e>=exp_max)
        {
            exp_max = e;
            personality = d;
        }
        if(d==2) d++;
            else d+=2;
    }
    if(nr!=1 && exp_max <= 1)
    {
        exp_max = 1;
        personality = nr;
    }
    return {personality,exp_max};
}
int main()
{
    int n,best_personality=-1, personality_exponent=0, personality_type=-1;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        int nr;
        scanf("%d",&nr);
        auto return_ = personality(nr);
        int type = return_.first, exp = return_.second;
        if(exp>personality_exponent || (exp==personality_exponent && type>personality_type) || 
          (exp==personality_exponent && type==personality_type && nr > best_personality))
        {
            best_personality = nr;
            personality_type = type;
            personality_exponent = exp;
        }
    }
    printf("%d\n",best_personality);
    return 0;
}
