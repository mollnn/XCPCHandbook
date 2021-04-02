#include <bits/stdc++.h>
using namespace std;

int src[1000005],a[1000005],al[1000005],ar[1000005],s[1000005],n,m,t1,t2,t3,t4;

struct Result {
	int a,al,ar,s;
};

void build(int p,int l,int r) {
	if(l==r) a[p]=al[p]=ar[p]=s[p]=src[l];
	else {
		build(p<<1,l,(l+r)/2),
		build(p<<1|1,(l+r)/2+1,r);
		a[p]=max(max(a[p<<1],a[p<<1|1]),max(max(ar[p<<1],al[p<<1|1]),ar[p<<1]+al[p<<1|1]));
		al[p]=max(al[p<<1],s[p<<1]+max(0,al[p<<1|1]));
		ar[p]=max(ar[p<<1|1],max(0,ar[p<<1])+s[p<<1|1]);
		s[p]=s[p*2]+s[p*2+1];
	}
}

void modify(int p,int l,int r,int pos,int key) {
	if(l==r) a[p]=al[p]=ar[p]=s[p]=key;
	else {
		if(pos<=(l+r)/2) modify(p<<1,l,(l+r)/2,pos,key);
		else modify(p<<1|1,(l+r)/2+1,r,pos,key);
		a[p]=max(max(a[p<<1],a[p<<1|1]),max(max(ar[p<<1],al[p<<1|1]),ar[p<<1]+al[p<<1|1]));
		al[p]=max(al[p<<1],s[p<<1]+max(0,al[p<<1|1]));
		ar[p]=max(ar[p<<1|1],max(0,ar[p<<1])+s[p<<1|1]);
		s[p]=s[p*2]+s[p*2+1];
	}
}

Result query(int p,int l,int r,int ql,int qr) {
	Result res;
	res.a=-1e+8;
	res.al=-1e+8;
	res.ar=-1e+8;
	res.s=-1e+8;
	if(l>qr||r<ql) return res;
	if(l>=ql&&r<=qr) {
		res.a=a[p];
		res.al=al[p];
		res.ar=ar[p];
		res.s=s[p];
		return res;
	}
	else {
		Result cl,cr;
		cl=query(p<<1,l,(l+r)/2,ql,qr);
		cr=query(p<<1|1,(l+r)/2+1,r,ql,qr);
		res.a=max(max(cl.a,cr.a),max(max(cl.ar,cr.al),cl.ar+cr.al));
		res.al=max(cl.al,cl.s+max(0,cr.al));
		res.ar=max(cr.ar,max(0,cl.ar)+cr.s);
		res.s=cl.s+cr.s;
		return res;
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>src[i];
	build(1,1,n);
	cin>>m;
	for(int i=1;i<=m;i++) {
		cin>>t3>>t1>>t2;
		if(t3) {
			Result res=query(1,1,n,t1,t2);
			cout<<res.a<<endl;
		}
		else {
			modify(1,1,n,t1,t2);
		}
	}
}
