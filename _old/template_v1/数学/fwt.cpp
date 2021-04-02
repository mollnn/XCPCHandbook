// template
void FWT_or(int *a,int opt)
{
    for(int i=1;i<N;i<<=1)
        for(int p=i<<1,j=0;j<N;j+=p)
            for(int k=0;k<i;++k)
                if(opt==1)a[i+j+k]=(a[j+k]+a[i+j+k])%MOD;
                else a[i+j+k]=(a[i+j+k]+MOD-a[j+k])%MOD;
}
void FWT_and(int *a,int opt)
{
    for(int i=1;i<N;i<<=1)
        for(int p=i<<1,j=0;j<N;j+=p)
            for(int k=0;k<i;++k)
                if(opt==1)a[j+k]=(a[j+k]+a[i+j+k])%MOD;
                else a[j+k]=(a[j+k]+MOD-a[i+j+k])%MOD;
}
void FWT_xor(int *a,int opt)
{
    for(int i=1;i<N;i<<=1)
        for(int p=i<<1,j=0;j<N;j+=p)
            for(int k=0;k<i;++k)
            {
                int X=a[j+k],Y=a[i+j+k];
                a[j+k]=(X+Y)%MOD;a[i+j+k]=(X+MOD-Y)%MOD;
                if(opt==-1)a[j+k]=1ll*a[j+k]*inv2%MOD,a[i+j+k]=1ll*a[i+j+k]*inv2%MOD;
            }
}

// example CF662C
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define N (1<<n)
int n,m,s[25][100005],a[2000005],b[2000005];
char ch[25][100005];
void FWT_xor(int *a,int opt){
    for(int i=1;i<N;i<<=1)
        for(int p=i<<1,j=0;j<N;j+=p)
            for(int k=0;k<i;++k)
            {
                int X=a[j+k],Y=a[i+j+k];
                a[j+k]=(X+Y);a[i+j+k]=(X-Y);
                if(opt==-1)a[j+k]=1ll*a[j+k]/2,a[i+j+k]=1ll*a[i+j+k]/2;
            }
}

signed main() {
    scanf("%lld%lld",&n,&m);
    for(int i=1;i<=n;i++) {
        scanf("%s",ch[i]+1);
        for(int j=1;j<=m;j++) s[i][j]=ch[i][j]-'0';
    }
    for(int j=1;j<=m;j++) {
        int x=0;
        for(int i=1;i<=n;i++) {
            x=x*2+s[i][j];
        }
        a[x]++;
    }
    for(int i=0;i<1<<n;i++) {
        int t=__builtin_popcount(i);
        b[i]=min(n-t,t);
    }
    FWT_xor(a,1);
    FWT_xor(b,1);
    for(int i=0;i<1<<n;i++) a[i]*=b[i];
    FWT_xor(a,-1);
    int ans = a[0];
    for(int i=1;i<1<<n;i++) ans=min(ans,a[i]);
    cout<<ans<<endl;
}
