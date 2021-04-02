#include <bits/stdc++.h>
using namespace std;

const int N = 50005;

int val[N*4],tag[N*4];
void pushup(int p) {
    val[p]=val[p*2]+val[p*2+1];
}
void pushdown(int p,int l,int r) {
    if(tag[p]==0) return;
    val[p*2]+=tag[p]*((l+r)/2-l+1);
    val[p*2+1]+=tag[p]*(r-(l+r)/2);
    tag[p*2]+=tag[p];
    tag[p*2+1]+=tag[p];
    tag[p]=0;
}
void build(int p,int l,int r,int *src) {
    if(l==r) val[p]=src[l];
    else {
        build(p*2,l,(l+r)/2,src);
        build(p*2+1,(l+r)/2+1,r,src);
        pushup(p);
    }
}
void modify(int p,int l,int r,int ql,int qr,int key) {
    if(l>qr||r<ql) return;
    if(l>=ql&&r<=qr) {
        val[p]+=(r-l+1)*key;
        tag[p]+=key;
    }
    else {
        pushdown(p,l,r);
        modify(p*2,l,(l+r)/2,ql,qr,key);
        modify(p*2+1,(l+r)/2+1,r,ql,qr,key);
        pushup(p);
    }
}
int query(int p,int l,int r,int pos) {
    if(l==r)  return val[p];
    else {
        pushdown(p,l,r);
        if(pos<=(l+r)/2) return query(p*2,l,(l+r)/2,pos);
        else return query(p*2+1,(l+r)/2+1,r,pos);
    }
}
vector <int> g[N];
int top[N],wson[N],siz[N],dep[N],vis[N],tid[N],did[N],fa[N],cnt=0;
// TreenodeID is mapped to DFS order by DID
// DFS order is mapped to TreenodeID by TID
void link(int p,int q) {g[p].push_back(q), g[q].push_back(p);}
void dfs1(int p) {
    vis[p]=siz[p]=1;
    for(int i=0;i<g[p].size();i++)
    if(vis[g[p][i]]==0) {
        dep[g[p][i]]=dep[p]+1;
        fa[g[p][i]]=p;
        dfs1(g[p][i]);
        siz[p]+=siz[g[p][i]];
        if(wson[p]==0 || siz[g[p][i]]>siz[wson[p]]) wson[p]=g[p][i];
    }
}
void dfs2(int p) {
    did[p]=++cnt;
    tid[cnt]=p;
    vis[p]=1;
    if(wson[p]) top[wson[p]]=top[p], dfs2(wson[p]);
    for(int i=0;i<g[p].size();i++) if(vis[g[p][i]]==0)
        top[g[p][i]]=g[p][i],dfs2(g[p][i]);
}
void presolve() {
    dep[1]=1; dfs1(1);
    memset(vis,0,sizeof vis);
    top[1]=1; dfs2(1);
}


int n,m,p,a[N],b[N],t1,t2,t3; char ch[5];

int link_query(int p) {
    return query(1,1,n,did[p]);
}
void link_modify(int p,int q,int v) {
    while(top[p]-top[q]) {
        if(dep[top[p]]>dep[top[q]]) swap(p,q);
        modify(1,1,n,did[top[q]],did[q],v);
        q=fa[top[q]];
    }
    if(dep[p]>dep[q]) swap(p,q);
    modify(1,1,n,did[p],did[q],v);
}


int main() {
    ios::sync_with_stdio(false);
    while(~scanf("%d%d%d",&n,&m,&p)) {

        memset(vis,0,sizeof vis);
        cnt=0;
        memset(val,0,sizeof val);
        memset(tag,0,sizeof tag);
        memset(top,0,sizeof top);
        memset(wson,0,sizeof wson);
        memset(siz,0,sizeof siz);
        memset(dep,0,sizeof dep);

        for(int i=1;i<=n;i++) scanf("%d",&b[i]);
        for(int i=1;i<=m;i++) {
            scanf("%d%d",&t1,&t2);
            link(t1,t2);
        }
        presolve();
        for(int i=1;i<=n;i++) a[did[i]]=b[i];
        build(1,1,n,a);

        for(int i=1;i<=p;i++) {
            scanf("%s",ch);
            if(ch[0]=='I') {
                scanf("%d%d%d",&t1,&t2,&t3);
                link_modify(t1,t2,t3);
            }
            else if(ch[0]=='D') {
                scanf("%d%d%d",&t1,&t2,&t3);
                link_modify(t1,t2,-t3);
            }
            else {
                scanf("%d",&t1);
                printf("%d\n",link_query(t1));
            }
        }

        for(int i=1;i<=n;i++) g[i].clear();

    }
}
