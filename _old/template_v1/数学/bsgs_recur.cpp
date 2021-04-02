// x[i+1]=(ax[i]+b) % p  Given p,a,b,x1,t
// Find smallest n s.t. x[n]=t
#include <map>
#include <cmath>
#include <cstdio>
using namespace std;
typedef long long ll;
map<ll , ll> mp;
map<ll , ll>::iterator it;
ll u[50010] , v[50010];
int main()
{
    int T;
    scanf("%d" , &T);
    while(T -- )
    {
        ll p , a , b , x , t , m , i , ans = 1ll << 62;
        scanf("%lld%lld%lld%lld%lld" , &p , &a , &b , &x , &t);
        if(!a)
        {
            if(t == x) puts("1");
            else if(t == b) puts("2");
            else puts("-1");
        }
        else
        {
            mp.clear() , m = ceil(sqrt(p));
            u[0] = 1 , v[0] = 0;
            for(i = 1 ; i <= m ; i ++ ) u[i] = u[i - 1] * a % p , v[i] = (a * v[i - 1] + b) % p;
            for(i = 1 ; i <= m ; i ++ )
            {
                x = (x * u[m] + v[m]) % p;
                if((it = mp.find(x)) == mp.end())
                    mp[x] = i;
            }
            for(i = 1 ; i <= m ; i ++ )
                if((it = mp.find((t * u[i] + v[i]) % p)) != mp.end())
                    ans = min(ans , it->second * m - i + 1);
            if(ans == 1ll << 62) puts("-1");
            else printf("%lld\n" , ans);
        }
    }
    return 0;
}
