#include <bits/stdc++.h>
double a,b,c,d,l,r;
inline double f(double x) {
    return (c*x+d)/(a*x+b);  //Original Function
}
inline double simpson(double l,double r) { //Simpson
    double mid=(l+r)/2;
    return (f(l)+4*f(mid)+f(r))*(r-l)/6;
}
double asr(double l,double r,double eps,double ans) {
    double mid=(l+r)/2;
    double l_=simpson(l,mid),r_=simpson(mid,r);
    if(fabs(l_+r_-ans)<=15*eps) return l_+r_+(l_+r_-ans)/15;
    return asr(l,mid,eps/2,l_)+asr(mid,r,eps/2,r_);
}
inline double asr(double l,double r,double eps) {
    return asr(l,r,eps,simpson(l,r));
}
int main() {
    scanf("%lf%lf%lf%lf%lf%lf",&a,&b,&c,&d,&l,&r);
    printf("%.6lf",asr(l,r,1e-6));
    return 0;
}
