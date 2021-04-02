// Which pattern string occurred for the most times
#include <bits/stdc++.h>
using namespace std;
struct ACA{
	queue <int> q;
	int c[500005][26],val[500005],fi[500005],cnt,ans[1005];
	void init(){
		memset(c,0,sizeof c); memset(val,0,sizeof val);
		memset(fi,0,sizeof fi); memset(ans,0,sizeof ans); cnt=0;}
	void ins(char *str,int id){
		int len=strlen(str), p=0;
		for(int i=0;i<len;i++){
			int v=str[i]-'a';
			if(!c[p][v]) c[p][v]=++cnt;
			p=c[p][v];}
		val[p]=id;}
	void build(){
		for(int i=0;i<26;i++) if(c[0][i]) fi[c[0][i]]=0, q.push(c[0][i]);
		while(!q.empty()){
			int u=q.front(); q.pop();
			for(int i=0;i<26;i++)
				if(c[u][i]) fi[c[u][i]]=c[fi[u]][i], q.push(c[u][i]);
				else c[u][i]=c[fi[u]][i];}}
	int query(char *s){
		int len=strlen(s); int p=0;
		for(int i=0;i<len;i++){
			p=c[p][s[i]-'a'];
			for(int t=p;t&&~val[t];t=fi[t])
				ans[val[t]]++;}}
} AC;
int n; char p[1000005]; string mp[1005];
int main(){
	while(scanf("%d",&n)&&n){
		memset(p,0,sizeof p); AC.init();
		for(int i=1;i<=n;i++) scanf("%s",p), AC.ins(p,i), mp[i]=p;
		AC.build();
		scanf("%s",p); int ans=AC.query(p);
		int mx=0;
		for(int i=1;i<=n;i++) if(AC.ans[i]>mx) mx=AC.ans[i];
		printf("%d\n",mx);
		for(int i=1;i<=n;i++) if(AC.ans[i]==mx) printf("%s\n",mp[i].c_str());
	}
}
