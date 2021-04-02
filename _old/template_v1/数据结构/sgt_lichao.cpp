#include<cstdio>
const int mod2=1e9;
const int mod1=39989;
const int maxn=4e4+10;
const double eps=1e-9;
inline int max_(int x,int y){return x>y?x:y;}
inline void swap_(int&x,int&y){x^=y,y^=x,x^=y;}
inline int dcmp(double x){return (x>eps)-(x<-eps);}
int n,m=0,lastans=0;
int opt,x,x0,y0,x1,y1;
int a[maxn],id[maxn];
int L,R,idx;
double K,B;
struct node{
    int id;
    double k,b;
    bool v;
}t[maxn<<2];
void solve(int k,int l,int r){
    if(t[k].v==0){
        t[k].k=K,t[k].b=B;
        t[k].v=1,t[k].id=idx;
        return;
    }
    double y0,y1,y2,y3;
    y0=t[k].k*l+t[k].b,y1=K*l+B;
    y2=t[k].k*r+t[k].b,y3=K*r+B;
    if(dcmp(y1-y0)>0&&dcmp(y3-y2)>0){
        if(dcmp(K-t[k].k)==0&&dcmp(B-t[k].b)==0) return;
        t[k].k=K,t[k].b=B,t[k].id=idx;
        return;
    }
    if(dcmp(y1-y0)<=0&&dcmp(y3-y2)<=0) return;
    int mid=l+r>>1,ls=k<<1,rs=ls|1;
    solve(ls,l,mid),solve(rs,mid+1,r);
}
void ins(int k,int l,int r){
    if(L<=l&&r<=R){
        solve(k,l,r);
        return;
    }
    int mid=l+r>>1,ls=k<<1,rs=ls|1;
    if(L<=mid) ins(ls,l,mid);
    if(R>mid) ins(rs,mid+1,r);
}
void ins(int x0,int x1,int y0,int y1,int num){
    L=x0,R=x1,idx=num;
    K=(0.0+y1-y0)/(0.0+x1-x0),B=y0-x0*K;
    ins(1,1,maxn);
}
int aid;
double ans;
void query(int k,int l,int r,int x){
    double y=t[k].k*x+t[k].b;
    if(dcmp(y-ans)==1||(dcmp(y-ans)==0&&t[k].id<aid)) ans=y,aid=t[k].id;
    if(l==r) return;
    int mid=l+r>>1,ls=k<<1,rs=ls|1;
    if(x<=mid) query(ls,l,mid,x);
    else query(rs,mid+1,r,x);
}
int main(){
    scanf("%d",&n);
    while(n--){
        scanf("%d",&opt);
        if(opt==0){
            scanf("%d",&x);
            x=(x+lastans-1)%mod1+1;
            ans=aid=0;
            query(1,1,maxn,x);
            if(ans<a[x]||(ans==a[x]&&id[x]<aid)) aid=id[x];
            printf("%d\n",lastans=aid);
        }
        if(opt==1){
            scanf("%d%d%d%d",&x0,&y0,&x1,&y1),m++;
            x0=(x0+lastans-1)%mod1+1,y0=(y0+lastans-1)%mod2+1;
            x1=(x1+lastans-1)%mod1+1,y1=(y1+lastans-1)%mod2+1;
            if(x0>x1) swap_(x0,x1),swap_(y0,y1);
            if(x0==x1){if(max_(y0,y1)>a[x0]) a[x0]=max_(y0,y1),id[x0]=m;}
            else ins(x0,x1,y0,y1,m);
        }
    }
    return 0;
}
