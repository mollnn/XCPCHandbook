#include<cstdio>
#include<vector>
#define N 505
int n,m,p,cx[N],cy[N],vis[N];
std::vector<int> e[N];
int dfs(int u,int Time) {
	for(int i=0;i<(int)e[u].size();++i) {
		int v=e[u][i];
		if(vis[v]^Time) {
			vis[v]=Time;
			if(!cy[v]||dfs(cy[v],Time)) {
				cx[u]=v; cy[v]=u;
				return 1;
			}
		}
	}
	return 0;
}
int main() {
	scanf("%d%d%d",&n,&m,&p);
	while(p--) {
		int u,v;
		scanf("%d%d",&u,&v);
		e[u].push_back(v);
	}
	int ans=0;
	for(int i=1;i<=n;++i) ans+=dfs(i,i);
	printf("%d\n",ans);
	for(int i=1;i<=n;++i) printf("%d ",cx[i]);
	return 0;
}
