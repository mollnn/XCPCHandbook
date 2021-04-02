#include<algorithm>
#include<iostream>
using namespace std;
namespace blossom{
const int N=505,M=300005;
int*fr,*bk,que[N],h[N],nxt[M],to[M],ec,match[N],lst[N],vis[N],vcc,n,m,fa[N],col[N],ret;
void add(int u,int v){to[++ec]=v;nxt[ec]=h[u];h[u]=ec;to[++ec]=u;nxt[ec]=h[v];h[v]=ec;}
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
int getlca(int u,int v){
	for(u=find(u),v=find(v),++vcc;;swap(u,v))if(u){
		if(vis[u]==vcc)return u;
		vis[u]=vcc;u=find(lst[match[u]]);
	}
}
void blossom(int u,int v,int lca){
	while(find(u)!=lca){
		if(fa[u]==u)fa[u]=lca;lst[u]=v,v=match[u],u=lst[match[u]];
		if(col[v]==2)col[*bk++=v]=1;if(fa[v]==v)fa[v]=lca;
	}
}
int aug(int x){
	int i;for(i=1;i<=n;i++)fa[i]=i,col[i]=lst[i]=0;
	bk=fr=que,col[*bk++=x]=1;
	while(fr!=bk){
		int u=*fr++,v,z,g;
		for(i=h[u];i;i=nxt[i])if(!col[v=to[i]]){
			lst[v]=u;
			if(!match[v]){for(;u;v=z,u=lst[v])z=match[u],match[u]=v,match[v]=u;return 1;}
			col[v]=2;col[*bk++=match[v]]=1;
		}else if(find(u)!=find(v)&&col[v]==1)g=getlca(u,v),blossom(u,v,g),blossom(v,u,g);
	}
	return 0;
}
void main(){
	int u,v,i;for(cin>>n>>m,i=1;i<=m;i++)cin>>u>>v,add(u,v);
	for(i=1;i<=n;i++)if(!match[i])ret+=aug(i);cout<<ret<<endl;
	for(i=1;i<=n;i++)cout<<match[i]<<" \n"[i==n]; 
}
};
int main(){blossom::main();return 0;}
