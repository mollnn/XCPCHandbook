// a^x = b mod p
#include <bits/stdc++.h>
using namespace std;

long long a,b,p,x;
map<long long,long long> mp;
inline long long gcd(long long x,long long y)
{
    return y?gcd(y,x%y):x;
}
inline long long ksm(long long x,long long y,long long mod)
{
    long long res=1;
    while(y)
    {
        if(y&1)
        res=(res*x)%mod;
        x=(x*x)%mod;
        y>>=1;
    }
    return res;
}
inline void exBSGS(long long a,long long b,long long p)
{
    if(b==1)
    {
        printf("0\n");
        return;
    }
    long long d=gcd(a,p),t=1,k=0;
    while(d!=1)
    {
        if(b%d)
        {
            printf("No Solution\n");
            return;
        }
        ++k;
        b/=d;
        p/=d;
        t=(t*(a/d))%p;//[1,k]µÄ´¦Àí
        d=gcd(a,p);
        if(b==t)
        {
            printf("%lld\n",k);
            return;
        }
    }
    mp.clear();
    long long m=ceil(sqrt(p)),ans;
    for(int j=0;j<=m;++j)
    {
        if(j==0)
        {
            ans=b%p;
            mp[ans]=j;
            continue;
        }
        ans=(ans*a)%p;
        mp[ans]=j;
    }
    long long x=ksm(a,m,p),pd=0;
    ans=t;
    for(int i=1;i<=m;++i)
    {
        ans=(ans*x)%p;
        if(mp[ans])
        {
            x=i*m-mp[ans];
            printf("%lld\n",x+k);
            pd=1;
            break;
        }
    }
    if(!pd)
    printf("No Solution\n");
    return;
}
int main()
{
    while(~scanf("%lld%lld%lld",&a,&p,&b))
    {
        if(a==0&&b==0&&p==0)
        break;
        a=a%p;
        b=b%p;
        exBSGS(a,b,p);
    }
    return 0;
}
