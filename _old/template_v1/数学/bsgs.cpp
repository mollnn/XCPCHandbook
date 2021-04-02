// b^x = n % p  (b,p)=1
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
int main()
{
    ll p , b , n;
    while(scanf("%lld%lld%lld" , &p , &b , &n) != EOF)
    {
        ll m = (ll)ceil(sqrt(p)) , i , t , temp , flag = 0;
        f.clear();
        for(t = 1 , i = 0 ; i < m ; t = t * b % p , i ++ )
            if(f.find(t) == f.end())
                f[t] = i;
        for(t = 1 , temp = pow(b , p - m - 1 , p) , i = 0 ; i < m ; t = t * temp % p , i ++ )
        {
            it = f.find(n * t % p);
            if(it != f.end())
            {
                printf("%lld\n" , i * m + it->second) , flag = 1;
                break;
            }
        }
        if(!flag) printf("no solution\n");
    }
    return 0;
}
