// ExLucas
// input n,m,p to get C(m,n) mod p
// p is not limited to prime
// Test: 666 233 123456 -> 61728

#include<bits/stdc++.h>
#define rg register
#define int long long
using namespace std;

inline void exgcd(int a,int b ,int &x,int &y){
    if(!b){x=1,y=0;return;}
    exgcd(b,a%b,x,y);
    int t=x;
    x=y,y=t-(a/b)*y;
}
inline int inv(int a,int b){
    int x,y;
    return exgcd(a,b,x,y),(x%b+b)%b;
}
inline int ksm(int a,int b,int p){
    int ans=1;
    while(b){
        if(b&1)
            ans=a*ans%p;
        a=a*a%p;
        b>>=1;
    }
    return ans%p;
}
inline int crt(int x,int p,int mod){
    return inv(p/mod,mod)*(p/mod)*x;
}
inline int fac(int x,int a,int b){
    if(!x)
        return 1;
    int ans=1;
    for(int i=1;i<=b;i++)
    if(i%a)
            ans*=i,ans%=b;
    ans=ksm(ans,x/b,b);
    for(int i=1;i<=x%b;i++)
        if(i%a)
            ans*=i,ans%=b;
    return ans*fac(x/a,a,b)%b;
}
inline int C(int n,int m,int a,int b){
    int N=fac(n,a,b),M=fac(m,a,b),Z=fac(n-m,a,b),sum=0;
    for(int i=n;i;i=i/a)
        sum+=i/a;
    for(int i=m;i;i=i/a)
        sum-=i/a;
    for(int i=n-m;i;i=i/a)
        sum-=i/a;
    return N*ksm(a,sum,b)%b*inv(M,b)%b*inv(Z,b)%b;
}
inline void exlucas(int n,int m,int p){
    int t=p,ans=0;
    for(int i=2;i*i<=p;i++){
        int k=1;
        while(t%i==0)
            k*=i,t/=i;
        ans+=crt(C(n,m,i,k),p,k),ans%=p;
    }
    if(t>1)
        ans+=crt(C(n,m,t,t),p,t),ans%=p;
    printf("%d",ans%p); // Output is here
}
main(){
    cin>>n>>m>>p;
    exlucas(n,m,p);
    return 0;
}
