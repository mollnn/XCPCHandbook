// Linear Recurrence Solver
// Test in N=1e9 K=3e4 780ms
// a[n]=sigma(i=1->k){f[i]*a[n-i]}
// Input
// [n] [k]
// [f1] [f2] ... [fk]
// [a0] [a1] ... [ak-1]
// Output
// [an] % Modulo
#include<cstdio>
#include<algorithm>
using namespace std;const int N=65536+10;typedef long long ll;const ll mod=998244353;
int n;int k;int rv[20][N];ll rt[20][20];int Len;ll tr1[N];ll tr2[N];long long st[N];long long xs[N];
ll sg[N];ll a[N];ll res[N];ll irg[N];ll q[N];ll rf[N];int DL=-1;ll ans=0;ll ret[N];
inline ll po(ll a,ll p){ll r=1;for(;p;p>>=1,a=a*a%mod)if(p&1)r=r*a%mod;return r;}
inline void ntt(ll* a,int o,int len,int d)
{
    for(int i=0;i<len;i++)if(i<rv[d][i])swap(a[i],a[rv[d][i]]);
    for(int k=1,j=1;k<len;k<<=1,j++)
        for(int s=0;s<len;s+=(k<<1))
            for(int i=s,w=1;i<s+k;i++,w=w*rt[o][j]%mod)
            {ll a0=a[i];ll a1=a[i+k]*w%mod;a[i]=(a0+a1)%mod,a[i+k]=(a0+mod-a1)%mod;}
    if(o==1){ll inv=po(len,mod-2);for(int i=0;i<len;i++)(a[i]*=inv)%=mod;}
}
inline void poly_inv(ll* a,ll* b,int len)
{
    b[0]=po(a[0],mod-2);
    for(int k=1,j=0;k<=len;k<<=1,j++)
    {
        for(int i=0;i<k;i++)tr1[i]=a[i];for(int i=0;i<k;i++)tr2[i]=b[i];
        ntt(tr1,0,k<<1,j);ntt(tr2,0,k<<1,j);
        for(int i=0;i<(k<<1);i++)b[i]=tr2[i]*(2+mod-tr1[i]*tr2[i]%mod)%mod;
        ntt(b,1,k<<1,j);for(int i=k;i<(k<<1);i++)b[i]=0;
    }
}
inline void poly_mod(ll* a)
{
    int mi=(k<<1);while(a[--mi]==0);if(mi<k)return;
    for(int i=0;i<(Len<<1);i++)rf[i]=0;for(int i=0;i<=mi;i++)rf[i]=a[i];
    reverse(rf,rf+mi+1);for(int i=mi-k+1;i<=mi;i++)rf[i]=0;ntt(rf,0,Len<<1,DL+1);
    for(int i=0;i<(Len<<1);i++)q[i]=(rf[i]*irg[i])%mod;ntt(q,1,(Len<<1),DL+1);
    for(int i=mi-k+1;i<=(Len<<1);i++)q[i]=0;reverse(q,q+mi-k+1);ntt(q,0,(Len<<1),DL+1);
    for(int i=0;i<(Len<<1);i++)(q[i]*=sg[i])%=mod;ntt(q,1,(Len<<1),DL+1);
    for(int i=0;i<k;i++)(a[i]+=mod-q[i])%=mod;for(int i=k;i<=mi;i++)a[i]=0;
}
int main()
{
    for(int i=0;i<=15;i++)
        for(int j=0;j<(1<<(i+1));j++)rv[i][j]=(rv[i][j>>1]>>1)|((j&1)<<i);
    for(int t=2,j=1;j<=18;t<<=1,j++)rt[0][j]=po(3,(mod-1)/t);
    for(int t=2,j=1;j<=18;t<<=1,j++)rt[1][j]=po(332748118,(mod-1)/t);
    scanf("%d%d",&n,&k);
    for(Len=1;Len<=k;Len<<=1,DL++);
    for(int i=1;i<=k;i++){scanf("%lld",&xs[i]);xs[i]=xs[i]<0?xs[i]+mod:xs[i];}
    for(int i=0;i<k;i++){scanf("%lld",&st[i]);st[i]=st[i]<0?st[i]+mod:st[i];}
    for(int i=1;i<=k;i++)sg[k-i]=mod-xs[i];sg[k]=1;for(int i=0;i<=k;i++)ret[i]=sg[i];
    for(int i=0;i<=k;i++)rf[i]=sg[i];reverse(rf,rf+k+1);poly_inv(rf,irg,Len);
    for(int i=0;i<=k;i++)rf[i]=0;ntt(sg,0,Len<<1,DL+1);ntt(irg,0,Len<<1,DL+1);a[1]=1;res[0]=1;
    while(n)
    {
        if(n&1)
        {
            ntt(res,0,Len<<1,DL+1);ntt(a,0,Len<<1,DL+1);
            for(int i=0;i<(Len<<1);i++)(res[i]*=a[i])%=mod;
            ntt(res,1,Len<<1,DL+1);ntt(a,1,Len<<1,DL+1);poly_mod(res);
        }ntt(a,0,Len<<1,DL+1);for(int i=0;i<(Len<<1);i++)(a[i]*=a[i])%=mod;
        ntt(a,1,Len<<1,DL+1);poly_mod(a);n>>=1;
    }for(int i=0;i<k;i++)(ans+=res[i]*st[i])%=mod;printf("%lld",ans);return 0;
}
