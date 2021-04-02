#include <queue>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define N 100010
using namespace std;
typedef long long ll;
typedef pair<ll , int> pr;
priority_queue<pr> q;
int head[N] , to[N << 2] , next[N << 2] , cnt , vis[33][N];
ll len[N << 2] , f[33][N];
inline void add(int x , int y , ll z)
{
    to[++cnt] = y , len[cnt] = z , next[cnt] = head[x] , head[x] = cnt;
}
int main()
{
    int n , p , m , i , j , k , x , y;
    ll z , ans = 1ll << 62;
    scanf("%d%d%d" , &n , &p , &m);
    memset(f , 0x3f , sizeof(f));
    for(i = 0 ; i < p ; i ++ ) scanf("%d" , &x) , f[1 << i][x] = 0;
    for(i = 0 ; i < m ; i ++ ) scanf("%d%d%lld" , &x , &y , &z) , add(x , y , z) , add(y , x , z);
    for(i = 1 ; i < (1 << p) ; i ++ )
    {
        for(j = i ; j ; j = i & (j - 1))
            for(k = 1 ; k <= n ; k ++ )
                f[i][k] = min(f[i][k] , f[j][k] + f[i ^ j][k]);
        for(j = 1 ; j <= n ; j ++ ) q.push(pr(-f[i][j] , j));
        while(!q.empty())
        {
            x = q.top().second , q.pop();
            if(vis[i][x]) continue;
            vis[i][x] = 1;
            for(j = head[x] ; j ; j = next[j])
                if(f[i][to[j]] > f[i][x] + len[j])
                    f[i][to[j]] = f[i][x] + len[j] , q.push(pr(-f[i][to[j]] , to[j]));
        }
    }
    for(i = 1 ; i <= n ; i ++ ) ans = min(ans , f[(1 << p) - 1][i]);
    printf("%lld\n" , ans);
    return 0;
}
