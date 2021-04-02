#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#define pw(n) (1<<n)
using namespace std;
const double pi=acos(-1);
struct complex{
    double a,b;
    complex(double _a=0,double _b=0){
        a=_a;
        b=_b;
    }
    friend complex operator +(complex x,complex y){return complex(x.a+y.a,x.b+y.b);}
    friend complex operator -(complex x,complex y){return complex(x.a-y.a,x.b-y.b);}
    friend complex operator *(complex x,complex y){return complex(x.a*y.a-x.b*y.b,x.a*y.b+x.b*y.a);}
    friend complex operator *(complex x,double y){return complex(x.a*y,x.b*y);}
    friend complex operator /(complex x,double y){return complex(x.a/y,x.b/y);}
}a[100001],b[100001];
int n,m,bit,bitnum=0,rev[pw(20)];
void getrev(int l){//Reverse
    for(int i=0;i<pw(l);i++){
        rev[i]=(rev[i>>1]>>1)|((i&1)<<(l-1));
    }
}
void FFT(complex *s,int op){
    for(int i=0;i<bit;i++)if(i<rev[i])swap(s[i],s[rev[i]]);
    for(int i=1;i<bit;i<<=1){
        complex w(cos(pi/i),op*sin(pi/i));
        for(int p=i<<1,j=0;j<bit;j+=p){//Butterfly
            complex wk(1,0);
            for(int k=j;k<i+j;k++,wk=wk*w){
                complex x=s[k],y=wk*s[k+i];
                s[k]=x+y;
                s[k+i]=x-y;
            }
        }
    }
    if(op==-1){
        for(int i=0;i<=bit;i++){
            s[i]=s[i]/(double)bit;
        }
    }
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=0;i<=n;i++)scanf("%lf",&a[i].a);
    for(int i=0;i<=m;i++)scanf("%lf",&b[i].a);
    m+=n;
    for(bit=1;bit<=m;bit<<=1)bitnum++;
    getrev(bitnum);
    FFT(a,1);
    FFT(b,1);
    for(int i=0;i<=bit;i++)a[i]=a[i]*b[i];
    FFT(a,-1);
    for(int i=0;i<=m;i++)printf("%d ",(int)(a[i].a+0.5));
    return 0;
}
