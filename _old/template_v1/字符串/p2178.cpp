// How many different substrings are there in the main string
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n,m=256,sa[1000005],y[1000005],u[1000005],v[1000005],o[1000005];
int r[1000005],h[1000005],T,val[1000005],f[300005];
char str[1000005];
long long ans1,ans2=-1e18;
vector <int> pos[300005];
multiset <int> st[300005];

int mix(multiset <int> &a, multiset <int> &b)
{
    if(a.size()>b.size()) {a.insert(b.begin(),b.end());return 0;}
    else {b.insert(a.begin(),a.end());return 1;}
}

int getans2(multiset <int> &s)
{
    if(s.size()<2) return 0;
    else
    {
        multiset<int>::iterator it1,it2,it3,it4;
        it1=s.begin();
        it2=it1; ++it2;
        it3=s.end();
        --it3;
        it4=it3; --it4;
        return max((*it1)*(*it2), (*it3)*(*it4));
    }
}

int find(int x) {return f[x]==x?x:f[x]=find(f[x]);}
void merge(int i,int j) {
    if(find(i)!=find(j)) {
        ans1+=st[find(i)].size()*st[find(j)].size();
        int fg=mix(st[find(i)],st[find(j)]);
        if(fg) f[find(i)]=find(j);
        else f[find(j)]=find(i);
        ans2=max(ans2,getans2(st[find(i)]));
    }
}

signed main(){
    scanf("%lld",&n);
    scanf("%s",str+1);
    for(int i=1;i<=n;i++) scanf("%lld",&val[i]);

    for(int i=1;i<=n;i++) u[str[i]]++;
    for(int i=1;i<=m;i++) u[i]+=u[i-1];
    for(int i=n;i>=1;i--) sa[u[str[i]]--]=i;
    r[sa[1]]=1;
    for(int i=2;i<=n;i++) r[sa[i]]=r[sa[i-1]]+(str[sa[i]]!=str[sa[i-1]]);

    for(int l=1;r[sa[n]]<n;l<<=1) {
        memset(u,0,sizeof u);
        memset(v,0,sizeof v);
        memcpy(o,r,sizeof r);
        for(int i=1;i<=n;i++) u[r[i]]++, v[r[i+l]]++;
        for(int i=1;i<=n;i++) u[i]+=u[i-1], v[i]+=v[i-1];
        for(int i=n;i>=1;i--) y[v[r[i+l]]--]=i;
        for(int i=n;i>=1;i--) sa[u[r[y[i]]]--]=y[i];
        r[sa[1]]=1;
        for(int i=2;i<=n;i++) r[sa[i]]=r[sa[i-1]]+((o[sa[i]]!=o[sa[i-1]])||(o[sa[i]+l]!=o[sa[i-1]+l]));
    }
    {
        int i,j,k=0;
        for(int i=1;i<=n;h[r[i++]]=k)
            for(k?k--:0,j=sa[r[i]-1];str[i+k]==str[j+k];k++);
    }

    for(int i=2;i<=n;i++)
    {
        pos[h[i]].push_back(i);
    }
    for(int i=1;i<=n;i++) st[i].insert(val[sa[i]]);
    for(int i=1;i<=n;i++) f[i]=i;
    vector <int> a1,a2;
    for(int i=n-1;i>=0;--i)
    {
        for(int j=0;j<pos[i].size();j++)
        {
            merge(pos[i][j],pos[i][j]-1);
        }
        a1.push_back(ans1);
        a2.push_back(ans2);
    }
    for(int i=n-1;i>=0;--i) printf("%lld %lld\n",a1[i],(a2[i]<-9e17?0:a2[i]));
}
