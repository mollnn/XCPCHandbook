// luogu-judger-enable-o2
#include<cstdio>
#include<cstring>
#include<iostream>
#include<cmath>
#include<algorithm>
using namespace std;
int n,m,t1,t2,t3,k,a[2000005],b[2000005],c[8000005],d[8000005],e[8000005],f,g[2000005],q[2000005],s,h[2000005]={1,0};
int build(int l,int r){
    int p=++f;
    if(r==l) c[p]=0;
    else d[p]=build(l,(l+r)/2), e[p]=build((l+r)/2+1,r);
    return p;}
void pushup(int p){c[p]=c[d[p]]+c[e[p]];}
int modify(int j,int l,int r,int k){
    int p=++f; c[p]=c[j]; d[p]=d[j]; e[p]=e[j];
    if(l==r) {c[p]++; return p;}
    if(k<=(l+r)/2) d[p]=modify(d[j],l,(l+r)/2,k);
    else e[p]=modify(e[j],(l+r)/2+1,r,k);
    pushup(p); return p;}
int query(int i,int j,int l,int r,int k){
    if(l==r) return l;
    if(k<=c[d[j]]-c[d[i]]) return query(d[i],d[j],l,(l+r)/2,k);
    else return query(e[i],e[j],(l+r)/2+1,r,k-(c[d[j]]-c[d[i]]));}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]), h[i]=a[i];
    sort(a+1,a+n+1); s=unique(a+1,a+n+1)-a-1;
    for(int i=1;i<=n;i++) q[i]=lower_bound(a+1,a+s+1,h[i])-a;
    build(1,s); g[0]=1;
    for(int i=1;i<=n;i++) g[i]=modify(g[i-1],1,s,q[i]);
    for(int i=1;i<=m;i++)
        scanf("%d%d%d",&t1,&t2,&k),
        printf("%d\n",a[query(g[t1-1],g[t2],1,s,k)]);
}
