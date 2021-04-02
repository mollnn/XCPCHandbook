#include <bits/stdc++.h>
using namespace std;

#define int long long

const int N = 1000000;

int n,m,q,t1,t2,t3,t4;

struct Edge {
    int u,v,w,f;
} e[N];

struct Operating {
    int o,p,q;
} op[N];

struct LinkCutTree {
    int top, q[N], ch[N][2], fa[N], rev[N], mx[N], mp[N], val[N];
    inline void pushup(int x) {
        mx[0]=mp[0]=0;
        mx[x] = max(max(mx[ch[x][0]],mx[ch[x][1]]),val[x]);
        if(mx[x] == mx[ch[x][0]])
            mp[x]=mp[ch[x][0]];
        if(mx[x] == mx[ch[x][1]])
            mp[x]=mp[ch[x][1]];
        if(mx[x] == val[x])
            mp[x]=x;
    }
    inline void pushdown(int x) {
        if(!rev[x])
            return;
        rev[ch[x][0]]^=1;
        rev[ch[x][1]]^=1;
        rev[x]^=1;
        swap(ch[x][0],ch[x][1]);
    }
    inline bool isroot(int x) {
        return ch[fa[x]][0]!=x && ch[fa[x]][1]!=x;
    }
    inline void rotate(int p) {
        int q=fa[p], y=fa[q], x=ch[fa[p]][1]==p;
        ch[q][x]=ch[p][x^1];
        fa[ch[q][x]]=q;
        ch[p][x^1]=q;
        fa[q]=p;
        fa[p]=y;
        if(y)
            if(ch[y][0]==q)
                ch[y][0]=p;
            else  if(ch[y][1]==q)
                ch[y][1]=p;
        pushup(q);
        pushup(p);
    }
    inline void splay(int x) {
        q[top=1]=x;
        for(int i=x; !isroot(i); i=fa[i])
            q[++top]=fa[i];
        for(int i=top; i; i--)
            pushdown(q[i]);
        for(; !isroot(x); rotate(x))
            if(!isroot(fa[x]))
                rotate((ch[fa[x]][0]==x)==(ch[fa[fa[x]]][0]==fa[x])?fa[x]:x);
    }
    void access(int x) {
        for(int t=0; x; t=x,x=fa[x])
            splay(x),ch[x][1]=t,pushup(x);
    }
    void makeroot(int x) {
        access(x);
        splay(x);
        rev[x]^=1;
    }
    int find(int x) {
        access(x);
        splay(x);
        while(ch[x][0])
            x=ch[x][0];
        return x;
    }
    void split(int x,int y) {
        makeroot(x);
        access(y);
        splay(y);
    }
    void cut(int x,int y) {
        split(x,y);
        if(ch[y][0]==x)
            ch[y][0]=0, fa[x]=0;
    }
    void link(int x,int y) {
        makeroot(x);
        fa[x]=y;
    }
    void setval(int p,int v) {
        val[p]=mx[p]=v;
        mp[p]=p;
    }
    int queryv(int p,int q) {
        split(p,q);
        return mx[q];
    }
    int queryp(int p,int q) {
        split(p,q);
        return mp[q];
    }
} lct;

bool check(int p,int q) {
    return lct.find(p)==lct.find(q);
}

int queryv(int p,int q) {
    return lct.queryv(p,q);
}

int queryp(int p,int q) {
    return lct.queryp(p,q)-n;
}

void link(int i) {
    lct.link(n+i,e[i].u);
    lct.link(n+i,e[i].v);
}

void cut(int i) {
    lct.cut(n+i,e[i].u);
    lct.cut(n+i,e[i].v);
}

void add(int i) {
    if(check(e[i].u,e[i].v)) {
        int v=queryv(e[i].u,e[i].v), p=queryp(e[i].u,e[i].v);
        if(v > e[i].w) {
            cut(p);
            link(i);
        }
    } else
        link(i);
}

map <int,int> mp[N];
vector <int> vc;

signed main() {
    scanf("%lld%lld%lld",&n,&m,&q);
    for(int i=1; i<=m; i++) {
        scanf("%lld%lld%lld",&t1,&t2,&t3);
        mp[t1][t2]=i;
        mp[t2][t1]=i;
        e[i]=(Edge) {
            t1,t2,t3,0
        };
    }
    for(int i=1; i<=n; i++)
        lct.setval(i, 0);
    for(int i=1; i<=m; i++)
        lct.setval(i+n, e[i].w);
    for(int i=1; i<=q; i++) {
        scanf("%lld%lld%lld",&t1,&t2,&t3);
        if(t1==2) {
            t4 = mp[t2][t3];
            e[t4].f=1;
        }
        op[i]=(Operating) {
            t1,t2,t3
        };
    }
    reverse(op+1,op+q+1);
    for(int i=1; i<=m; i++) {
        if(e[i].f==0) {
            add(i);
        }
    }
    for(int i=1; i<=q; i++) {
        if(op[i].o == 1) {
            vc.push_back(queryv(op[i].p,op[i].q));
        } else {
            add(mp[op[i].p][op[i].q]);
        }
    }
    while(vc.size()) {
        printf("%lld\n",vc.back());
        vc.pop_back();
    }
}
