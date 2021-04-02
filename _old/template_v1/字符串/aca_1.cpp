// How many pattern strings have occurred in the main string
#include <bits/stdc++.h>
using namespace std;

const int N = 1000005;

int ch[N][26],fi[N],val[N],n,m,t1,t2,t3,t4,ind;

void ins(char *s) {
	int len=strlen(s),p=0;
	for(int i=0;i<len;i++) {
		if(ch[p][s[i]-'a']==0) ch[p][s[i]-'a']=++ind;
		p=ch[p][s[i]-'a'];
	}
	val[p]++;
}

void build() {
	queue <int> q;
	for(int i=0;i<26;i++) if(ch[0][i]) q.push(ch[0][i]);
	while(!q.empty()) {
		int p=q.front(); q.pop();
		for(int i=0;i<26;i++)
			if(ch[p][i]) fi[ch[p][i]]=ch[fi[p]][i],q.push(ch[p][i]);
			else ch[p][i]=ch[fi[p]][i];
	}
}

int query(char *s) {
	int ans=0,len=strlen(s),p=0;
	for(int i=0;i<len;i++) {
		p=ch[p][s[i]-'a'];
		for(int t=p;t&&~val[p];t=fi[t])
			ans+=val[p],val[p]=-1;
	}
	return ans;
}

char str[N];

int main() {
	cin>>n;
	for(int i=1;i<=n;i++) cin>>str,ins(str);
	build();
	cin>>str;
	cout<<query(str)<<endl;
}
