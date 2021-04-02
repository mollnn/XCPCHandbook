#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#define pw(n) (1<<n)
using namespace std;
const int N=262144,P=998244353,g=3;
int n,m,bit,bitnum=0,a[N+5],b[N+5],rev[N+5];
void getrev(int l){
    for(int i=0;i<pw(l);i++){
        rev[i]=(rev[i>>1]>>1)|((i&1)<<(l-1));
    }
}
int fastpow(int a,int b){
    int ans=1;
    for(;b;b>>=1,a=1LL*a*a%P){
        if(b&1)ans=1LL*ans*a%P;
    }
    return ans;
}
void NTT(int *s,int op){
    for(int i=0;i<bit;i++)if(i<rev[i])swap(s[i],s[rev[i]]);
    for(int i=1;i<bit;i<<=1){
        int w=fastpow(g,(P-1)/(i<<1));
        for(int p=i<<1,j=0;j<bit;j+=p){
            int wk=1;
            for(int k=j;k<i+j;k++,wk=1LL*wk*w%P){
                int x=s[k],y=1LL*s[k+i]*wk%P;
                s[k]=(x+y)%P;
                s[k+i]=(x-y+P)%P;
            }
        }
    }
    if(op==-1){
        reverse(s+1,s+bit);
        int inv=fastpow(bit,P-2);
        for(int i=0;i<bit;i++)a[i]=1LL*a[i]*inv%P;
    }
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=0;i<=n;i++)scanf("%d",&a[i]);
    for(int i=0;i<=m;i++)scanf("%d",&b[i]);
    m+=n;
    for(bit=1;bit<=m;bit<<=1)bitnum++;
    getrev(bitnum);
    NTT(a,1);
    NTT(b,1);
    for(int i=0;i<bit;i++)a[i]=1LL*a[i]*b[i]%P;
    NTT(a,-1);
    for(int i=0;i<=m;i++)printf("%d ",a[i]);
    return 0;
}
