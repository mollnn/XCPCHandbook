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
const long double pi=acos(-1);
struct complex{
    long double a,b;
    complex(long double _a=0,long double _b=0){
        a=_a;
        b=_b;
    }
    friend complex operator +(complex x,complex y){return complex(x.a+y.a,x.b+y.b);}
    friend complex operator -(complex x,complex y){return complex(x.a-y.a,x.b-y.b);}
    friend complex operator *(complex x,complex y){return complex(x.a*y.a-x.b*y.b,x.a*y.b+x.b*y.a);}
    friend complex operator *(complex x,long double y){return complex(x.a*y,x.b*y);}
    friend complex operator /(complex x,long double y){return complex(x.a/y,x.b/y);}
}a[1000001],b[1000001],c[1000001],d[1000001];
int n,m,p,bit=1,bitnum=0,A[1000001],B[1000001],rev[1000001];
void fft(complex *s,int op){
    for(int i=0;i<bit;i++)if(i<rev[i])swap(s[i],s[rev[i]]);
    for(int i=1;i<bit;i<<=1){
        complex w(cos(pi/i),op*sin(pi/i));
        for(int pp=i<<1,j=0;j<bit;j+=pp){
            complex wk(1,0);
            for(int k=j;k<i+j;k++,wk=wk*w){
                complex x=s[k],y=wk*s[k+i];
                s[k]=x+y;
                s[k+i]=x-y;
            }
        }
    }
    if(op==-1){
        for(int i=0;i<bit;i++){
            s[i]=s[i]/(double)bit;
        }
    }
}
int main(){
    scanf("%d%d%d",&n,&m,&p);
    for(int i=0;i<=n;i++)scanf("%d",&A[i]);
    for(int i=0;i<=m;i++)scanf("%d",&B[i]);
    n+=m+1;
    for(;bit<=n;bit<<=1)++bitnum;
    for(int i=0;i<bit;i++){
        rev[i]=(rev[i>>1]>>1|((i&1)<<(bitnum-1)));
    }
    for(int i=0;i<bit;i++){
        a[i].a=A[i]>>15;
        b[i].a=A[i]&32767;
        c[i].a=B[i]>>15;
        d[i].a=B[i]&32767;
    }
    fft(a,1);
    fft(b,1);
    fft(c,1);
    fft(d,1);
    for(int i=0;i<bit;i++){
        complex s1=a[i],s2=b[i],s3=c[i],s4=d[i];
        a[i]=s1*s3;
        b[i]=s1*s4+s2*s3;
        c[i]=s2*s4;
    }
    fft(a,-1);
    fft(b,-1);
    fft(c,-1);
    for(int i=0;i<n;i++){
        printf("%lld ",(ll)((ll)(a[i].a+0.5)%p*(1LL<<30)%p+(ll)(b[i].a+0.5)%p*(1LL<<15)%p+(ll)(c[i].a+0.5)%p)%p);
    }
    return 0;
}
