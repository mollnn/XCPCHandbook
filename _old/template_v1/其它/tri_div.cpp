#include <bits/stdc++.h>
#define db double
using namespace std;
const db eps=1e-6;
int n;db a[15],L,R,mid1,mid2,k;
db f(db x){
    db S=0;
    for(int i=n;i>=0;i--) S=S*x+a[i];
    return S;
}
int main(){
    scanf("%d%lf%lf",&n,&L,&R);
    for(int i=n;i>=0;i--) scanf("%lf",&a[i]);
    while(R-L>=eps){
        k=(R-L)/3.0;
        mid1=L+k,mid2=R-k;
        if(f(mid1)>f(mid2)) R=mid2;else L=mid1;
    }
    printf("%.5lf\n",L);
    return 0;
}
