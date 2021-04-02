// Count on a Tree II (spoj10707)
vector <int> g[100005];
map <int,int> mp;
int a[200005],b[200005],cnt[200005],src[100005],dep[100005],seq[100005],vis[100005],fa[100005][18],st[100005],en[100005],ans,ind,n,m,blocksize;
int _a[200005];
struct Query {
    int x,y,l,ans,id;
    bool operator < (const Query &tar) {
        return ((x/blocksize == tar.x/blocksize)?(y<tar.y):(x<tar.x));
    }
} q[200005];

void add(int p) {
    b[seq[p]]++;
    if(b[seq[p]]&1) {cnt[a[p]]++;if(cnt[a[p]]==1) ++ans;}
    else {cnt[a[p]]--;if(cnt[a[p]]==0) --ans;}
}
void dec(int p) {
    b[seq[p]]--;
    if(b[seq[p]]&1) {cnt[a[p]]++;if(cnt[a[p]]==1) ++ans;}
    else {cnt[a[p]]--;if(cnt[a[p]]==0) --ans;}
}
void dfs(int p) {
    vis[p]=1;
    seq[++ind]=p; st[p]=ind;
    for(int i=0;i<g[p].size();i++) {
        if(vis[g[p][i]]) continue;
        fa[g[p][i]][0]=p;
        dep[g[p][i]]=dep[p]+1;
        dfs(g[p][i]);
    }
    seq[++ind]=p; en[p]=ind;
}
void lca_presolve() {
    for(int i=1;i<18;i++)
        for(int j=1;j<=n;j++)
            fa[j][i]=fa[fa[j][i-1]][i-1];
}
int lca(int p,int q) {
    if(dep[p]<dep[q]) swap(p,q);
    for(int i=17;i>=0;--i)
        if(dep[fa[p][i]]>=dep[q]) p=fa[p][i];
    for(int i=17;i>=0;--i)
        if(fa[p][i]-fa[q][i]) p=fa[p][i],q=fa[q][i];
    if(p-q) p=fa[p][0],q=fa[q][0];
    return p;
}
int main() {
    ios::sync_with_stdio(false);
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>src[i], mp[src[i]]++;
    int __idx=0;
    for(map<int,int>::iterator it=mp.begin(); it!=mp.end(); it++)
        it->second = ++__idx;
    for(int i=1;i<=n;i++) src[i]=mp[src[i]];
    for(int i=1;i<n;i++) {
        int u,v;
        cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dep[1]=1;
    dfs(1);
    lca_presolve();
    for(int i=1;i<=2*n;i++) a[i]=src[seq[i]];
    for(int i=1;i<=m;i++) {
        cin>>q[i].x>>q[i].y;
        q[i].id=i;
        q[i].l=lca(q[i].x,q[i].y);
        if(st[q[i].x]>st[q[i].y]) swap(q[i].x,q[i].y);
        if(q[i].x==q[i].l) {
            q[i].l=0;
            q[i].x=st[q[i].x];
            q[i].y=st[q[i].y];
        }
        else {
            q[i].l=st[q[i].l];
            q[i].x=en[q[i].x];
            q[i].y=st[q[i].y];
            if(q[i].x>q[i].y) swap(q[i].x,q[i].y);
        }
    }
    blocksize = sqrt(m);
    sort(q+1,q+m+1);
    int L=1,R=0;
    for(int i=1;i<=m;i++) {
        while(R<q[i].y) ++R,add(R);
        while(L>q[i].x) --L,add(L);
        while(R>q[i].y) dec(R),--R;
        while(L<q[i].x) dec(L),++L;
        if(q[i].l==0) {
            q[i].ans = ans;
        }
        else {
            add(q[i].l);
            q[i].ans = ans;
            dec(q[i].l);
        }
        _a[q[i].id]=q[i].ans;
    }
    for(int i=1;i<=m;i++) cout<<_a[i]<<endl;
}
