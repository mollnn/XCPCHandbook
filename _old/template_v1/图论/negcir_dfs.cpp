#include <bits/stdc++.h>
using namespace std;

int n,m,ins[1000005],vis[1000005],dis[1000005],fg=0,t1,t2,t3,T;

vector <pair<int,int> > g[1000005];

void dfs(int p){
	ins[p]=1; vis[p]=1;
	for(int i=0;i<g[p].size()&&!fg;i++)
		if(dis[g[p][i].first]>dis[p]+g[p][i].second){
			dis[g[p][i].first]=dis[p]+g[p][i].second;
			if(ins[g[p][i].first]==0)
				dfs(g[p][i].first);
			else {fg=1; return;}}
	ins[p]=0;
}

int main(){
	scanf("%d",&T);
	while(T--){
		n=m=fg=0; memset(ins,0,sizeof ins); memset(vis,0,sizeof vis); memset(dis,0,sizeof dis);
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++) g[i].clear();
		for(int i=1;i<=m;i++){
			scanf("%d%d%d",&t1,&t2,&t3),
			g[t1].push_back(make_pair(t2,t3));
			if(t3>=0) g[t2].push_back(make_pair(t1,t3));
		}
		for(int i=1;i<=n;i++)
			if(vis[i]==0) dis[i]=0, dfs(i);
		if(fg==1) printf("YE5\n");
		else printf("N0\n");
	}
}
