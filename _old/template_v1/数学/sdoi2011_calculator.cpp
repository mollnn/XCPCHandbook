#include <cstdio>
#include <cmath>
#include <map>
using namespace std;
typedef long long ll;
map<ll , ll> f;
map<ll , ll>::iterator it;
ll pow(ll x , ll y , ll mod)
{
    ll ans = 1;
    while(y)
    {
        if(y & 1) ans = ans * x % mod;
        x = x * x % mod , y >>= 1;
    }
    return ans;
}
ll gcd(ll a , ll b)
{
    return b ? gcd(b , a % b) : a;
}
void exgcd(ll a , ll b , ll &x , ll &y)
{
    if(!b)
    {
        x = 1 , y = 0;
        return;
    }
    exgcd(b , a % b , x , y);
    ll t = x;
    x = y , y = t - a / b * y;
}
int main()
{
    int T , k;
    scanf("%d%d" , &T , &k);
    while(T -- )
    {
        ll y , z , p;
        scanf("%lld%lld%lld" , &y , &z , &p);
        switch(k)
        {
            case 1: printf("%lld\n" , pow(y , z , p)); break;
            case 2:
            {
                y %= p , z %= p;
                ll t = gcd(y , p) , x1 , x2;
                if(z % t != 0)
                {
                    printf("Orz, I cannot find x!\n");
                    break;
                }
                y /= t , p /= t , z /= t , exgcd(y , p , x1 , x2) , x1 *= z;
                while(x1 < 0) x1 += p;
                while(x1 - p >= 0) x1 -= p;
                printf("%lld\n" , x1);
                break;
            }
            default:
            {
                y %= p , z %= p;
                if(!y)
                {
                    if(!z) printf("1\n");
                    else printf("Orz, I cannot find x!\n");
                    break;
                }
                ll m = (ll)ceil(sqrt(p)) , i , flag = 0 , t = 1 , temp;
                f.clear();
                for(i = 0 ; i < m ; i ++ )
                {
                    if(f.find(t) == f.end()) f[t] = i;
                    t = t * y % p;
                }
                temp = pow(y , p - m - 1 , p) , t = 1;
                for(i = 0 ; i <= m ; i ++ )
                {
                    it = f.find(z * t % p) , t = t * temp % p;
                    if(it != f.end())
                    {
                        printf("%lld\n" , i * m + it->second) , flag = 1;
                        break;
                    }
                }
                if(!flag) printf("Orz, I cannot find x!\n");
            }
        }
    }
    return 0;
}
