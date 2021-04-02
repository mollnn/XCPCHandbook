#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
#include<cstdio>
#define p 31011
#define N 1003
using namespace std;
int a[12][12],c[N][N],n,m,vis[N],fa[N],U[N];
vector<int> V[N];
struct data{
    int x,y,c;
    bool operator<(const data &a)const{
      return c<a.c;
    }
}e[N];
int gauss(int n)
{
    for (int i=1;i<=n;i++)
     for (int j=1;j<=n;j++) a[i][j]%=p;
    //for (int i=1;i<=n;i++,cout<<endl)
     // for (int j=1;j<=n;j++) cout<<a[i][j]<<" ";
    int ret=1;
    for (int i=1;i<=n;i++) {
        int num=i;
        for (int j=i+1;j<=n;j++)
         if (abs(a[j][i])) num=j;
        for (int j=1;j<=n;j++) swap(a[num][j],a[i][j]);
        if (num!=i) ret=-ret;
        for (int j=i+1;j<=n;j++)
         while (a[j][i]) {
            int t=a[j][i]/a[i][i];
            for (int k=1;k<=n;k++)
             a[j][k]=(a[j][k]-t*a[i][k])%p;
            if (!a[j][i]) break;
            ret=-ret;
            for (int k=1;k<=n;k++) swap(a[i][k],a[j][k]);
         }
        ret=(ret*a[i][i])%p;
    }
    //cout<<ret<<endl;
    return (ret%p+p)%p;
}
int find(int x,int f[N])
{
    if (x==f[x]) return x;
    else return find(f[x],f);
}
int main()
{
    freopen("bzoj_1016.in","r",stdin);
    freopen("bzoj_1016.out","w",stdout);
    scanf("%d%d",&n,&m);
    for (int i=1;i<=m;i++) scanf("%d%d%d",&e[i].x,&e[i].y,&e[i].c);
    sort(e+1,e+m+1);
    for (int i=1;i<=n;i++) vis[i]=0,fa[i]=i;
    int ans=1; int last=-1;
    for (int i=1;i<=m+1;i++) {
        if (e[i].c!=last||i==m+1) {
            for (int j=1;j<=n;j++)
             if (vis[j]) {
                int r1=find(j,U);
                V[r1].push_back(j);
                vis[j]=0;
             }
            for (int j=1;j<=n;j++)
             if (V[j].size()>1) {
                memset(a,0,sizeof(a));
                int len=V[j].size();
                for (int k=0;k<len;k++)
                 for (int l=k+1;l<len;l++) {
                    int x=V[j][k]; int y=V[j][l]; int t=c[x][y];
                    a[k+1][l+1]-=t; a[l+1][k+1]-=t;
                    a[k+1][k+1]+=t; a[l+1][l+1]+=t;
                 }
                ans=ans*gauss(len-1)%p;
                for (int k=0;k<len;k++) fa[V[j][k]]=j;
             }
            for (int j=1;j<=n;j++) {
                U[j]=fa[j]=find(j,fa);
                V[j].clear();
            }
            last=e[i].c;
            if(i==m+1) break;
        }
        int x=e[i].x; int y=e[i].y;
        int r1=find(x,fa); int r2=find(y,fa);
        if (r1==r2) continue;
        U[find(r1,U)]=find(r2,U); vis[r1]=1; vis[r2]=1;
        c[r1][r2]++; c[r2][r1]++;
    }
    int flag=1;
    for (int i=2;i<=n;i++)
     if (find(i,U)!=find(i-1,U)) flag=0;
    ans=(ans*flag%p+p)%p;
    printf("%d\n",ans);
}
