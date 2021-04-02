#include <bits/stdc++.h>
using namespace std;

const int N = 1000000;

int n,m,val[N];

struct LinkCutTree{
	int top, q[N], ch[N][2], fa[N], xr[N], rev[N];
	inline void pushup(int x){
		xr[x]=xr[ch[x][0]]^xr[ch[x][1]]^val[x];
	}
	inline void pushdown(int x){
		if(!rev[x]) return;
		rev[ch[x][0]]^=1;
		rev[ch[x][1]]^=1;
		rev[x]^=1;
		swap(ch[x][0],ch[x][1]);
	}
	inline bool isroot(int x){
		return ch[fa[x]][0]!=x && ch[fa[x]][1]!=x;
	}
	inline void rotate(int p){
		int q=fa[p], y=fa[q], x=ch[fa[p]][1]==p;
		ch[q][x]=ch[p][x^1]; fa[ch[q][x]]=q;
		ch[p][x^1]=q; fa[q]=p; fa[p]=y;
		if(y) if(ch[y][0]==q) ch[y][0]=p;
		else  if(ch[y][1]==q) ch[y][1]=p;
		pushup(q); pushup(p);
	}
	inline void splay(int x){
		q[top=1]=x;
		for(int i=x;!isroot(i);i=fa[i]) q[++top]=fa[i];
		for(int i=top;i;i--) pushdown(q[i]);
		for(;!isroot(x);rotate(x))
			if(!isroot(fa[x]))
				rotate((ch[fa[x]][0]==x)==(ch[fa[fa[x]]][0]==fa[x])?fa[x]:x);
	}
	void access(int x){
		for(int t=0;x;t=x,x=fa[x])
			splay(x),ch[x][1]=t,pushup(x);
	}
	void makeroot(int x){
		access(x);
		splay(x);
		rev[x]^=1;
	}
	int find(int x){
		access(x);
		splay(x);
		while(ch[x][0]) x=ch[x][0];
		return x;
	}
	void split(int x,int y){
		makeroot(x);
		access(y);
		splay(y);
	}
	void cut(int x,int y){
		split(x,y);
		if(ch[y][0]==x)
			ch[y][0]=0, fa[x]=0;
	}
	void link(int x,int y){
		makeroot(x);
		fa[x]=y;
	}
} T;

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		char str[10]; int t1,t2;
		scanf("%s%d%d",&str,&t1,&t2);
		if(str[0]=='C')
			if(T.find(t1)-T.find(t2)) T.link(t1,t2);
		if(str[0]=='D')
			T.cut(t1,t2);
		if(str[0]=='Q')
			printf("%s\n",T.find(t1)-T.find(t2)?"No":"Yes");
	}
}
