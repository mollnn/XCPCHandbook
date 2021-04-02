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
const int p=998244353,g=3;
int n,m,a[500001],b[500001],rev[500001],tmp[500001];
int fastpow(int x,int y){
    int ret=1;
    for(;y;y>>=1,x=(ll)x*x%p){
        if(y&1)ret=(ll)ret*x%p;
    }
    return ret;
}
void ntt(int s[],int n,int op){
    for(int i=0;i<n;i++)if(i<rev[i])swap(s[i],s[rev[i]]);
    for(int i=1;i<n;i<<=1){
        int w=fastpow(g,(p-1)/(i<<1));
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
        int inv=fastpow(n,p-2);
        for(int i=0;i<n;i++){
            s[i]=(ll)s[i]*inv%p;
        }
    }
}
void GetInv(int a[],int b[],int l){
    if(l==1){
        b[0]=fastpow(a[0],p-2);
        return;
    }
    GetInv(a,b,(l+1)/2);
    int bit=1,bitnum=0;
    for(;bit<l*2;bit<<=1)bitnum++;
    for(int i=1;i<bit;i++){
        rev[i]=(rev[i>>1]>>1|(i&1)<<(bitnum-1));
    }
    for(int i=0;i<l;i++)tmp[i]=a[i];
    for(int i=l;i<bit;i++)tmp[i]=0;
    ntt(tmp,bit,1);
    ntt(b,bit,1);
    for(int i=0;i<bit;i++)b[i]=(ll)b[i]*((2-(ll)tmp[i]*b[i]%p+p)%p)%p;
    ntt(b,bit,-1);
    for(int i=l;i<bit;i++)b[i]=0;
}
int main(){
    scanf("%d",&n);
    for(int i=0;i<n;i++)scanf("%d",&a[i]);
    GetInv(a,b,n);
    for(int i=0;i<n;i++)printf("%d ",b[i]);
    return 0;
}
