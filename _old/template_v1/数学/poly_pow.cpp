#include<algorithm>
#include<iostream>
#include<cstring>
#include<vector>
#include<cstdio>
#include<cmath>
#include<queue>
#include<stack>
#include<map>
#include<set>
using namespace std;
typedef long long ll;
const int p=1004535809,g=3;
int n,m,k,bit=1,bitnum=0,s[100001],tmp[100001],x,_g,rev[100001],blg[100001],inv,G[100001],a[100001],b[100001],c[100001],sum[100001],ans[100001];
int fastpow(int a,int b,int p){
    int ret=1;
    for(;b;b>>=1,a=(ll)a*a%p){
        if(b&1)ret=(ll)ret*a%p;
    }
    return ret;
}
bool check(int x,int n){
    for(int i=2;i*i<=n;i++){
        if((n-1)%i==0&&fastpow(x,(n-1)/i,n)==1)return false;
    }
    return true;
}
int GetG(int n){
    if(n==2)return 1;
    for(int i=2;;i++){
        if(check(i,n))return i;
    }
}
void ntt(int s[],int n,int op){
    for(int i=0;i<n;i++)if(i<rev[i])swap(s[i],s[rev[i]]);
    for(int i=1;i<n;i<<=1){
        int w=fastpow(g,(p-1)/(i<<1),p);
        for(int pp=i<<1,j=0;j<n;j+=pp){
            int wk=1;
            for(int k=j;k<i+j;k++,wk=(ll)wk*w%p){
                int x=s[k],y=(ll)s[k+i]*wk%p;
                s[k]=(x+y)%p;
                s[k+i]=(x-y+p)%p;
            }
        }
    }
    if(op==-1){
        reverse(s+1,s+n);
        int inv=fastpow(n,p-2,p);
        for(int i=0;i<n;i++){
            s[i]=(ll)s[i]*inv%p;
        }
    }
}
void mul(int aa[],int bb[],int cc[]){
    for(int i=0;i<bit;i++)b[i]=aa[i],c[i]=bb[i];
    ntt(b,bit,1);
    ntt(c,bit,1);
    for(int i=0;i<bit;i++)cc[i]=(ll)b[i]*c[i]%p;
    ntt(cc,bit,-1);
    for(int i=m-1;i<bit;i++){
        cc[i-m+1]=(cc[i-m+1]+cc[i])%p;
        cc[i]=0;
    }
}
void pow(int a[],int n){
    ans[0]=1;
    for(;n;n>>=1,mul(a,a,a)){
        if(n&1)mul(a,ans,ans);
    }
}
int main(){
    scanf("%d%d%d%d",&n,&m,&x,&k);
    for(int i=1;i<=k;i++)scanf("%d",&s[i]);
    for(;bit<m*2;bit<<=1)bitnum++;
    for(int i=0;i<bit;i++){
        rev[i]=(rev[i>>1]>>1|(i&1)<<(bitnum-1));
    }
    _g=GetG(m);
    //printf("%d\n",_g);
    G[0]=1;
    for(int i=1;i<m-1;i++){
        G[i]=(G[i-1]*_g)%m;
        blg[G[i]]=i;
    }
    for(int i=1;i<=k;i++){
        if(s[i])tmp[blg[s[i]]]++;
    }
    pow(tmp,n);
    printf("%d",ans[blg[x]]);
    return 0;
}
