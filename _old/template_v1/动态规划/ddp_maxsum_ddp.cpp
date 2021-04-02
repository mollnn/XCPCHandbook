#include <bits/stdc++.h>
using namespace std;
#define int long long
struct Matrix {
	int n,m,a[5][5];
	Matrix() {
		n=m=0;
		for(int i=0;i<4;i++) for(int j=0;j<4;j++) a[i][j]=0;
	}
	Matrix operator * (const Matrix &y) {
		Matrix r;
		if(m!=y.n) return r;
		r.n = n; r.m = y.m;
		for(int i=1;i<=n;i++) {
			for(int j=1;j<=y.m;j++) {
				for(int k=1;k<=m;k++) {
					if(k==1) r.a[i][j]=a[i][k]+y.a[k][j];
					else r.a[i][j]=max(r.a[i][j],a[i][k]+y.a[k][j]);
				}
			}
		}
		return r;
	}
}; 
Matrix make(int x) {
	Matrix r;
	r.m=r.n=3;
	r.a[1][1]=r.a[1][3]=r.a[2][1]=r.a[2][3]=x;
	r.a[2][2]=r.a[3][3]=0;
	r.a[1][2]=r.a[3][1]=r.a[3][2]=-1e+9;
	return r;
}

const int N = 1000005;

Matrix val[N],zero;
int n,q,src[N],t1,t2,t3;

void pushup(int p) {
	val[p] = val[p*2]*val[p*2+1];
}
void build(int p,int l,int r) {
	if(l==r) {
		val[p]=make(src[l]);
	}
	else {
		build(p*2,l,(l+r)/2);
		build(p*2+1,(l+r)/2+1,r);
		pushup(p); 
	}
}
void modify(int p,int l,int r,int pos,int key) {
	if(l==r) {
		val[p]=make(key);
	}
	else {
		if(pos<=(l+r)/2) modify(p*2,l,(l+r)/2,pos,key);
		else modify(p*2+1,(l+r)/2+1,r,pos,key);
		pushup(p); 
	}
}
Matrix query(int p,int l,int r,int ql,int qr) {
	Matrix R=make(-1e+9);
	if(l>qr||r<ql) return R;
	if(l>=ql&&r<=qr) return val[p];
	return query(p*2,l,(l+r)/2,ql,qr)*query(p*2+1,(l+r)/2+1,r,ql,qr);
}

signed main() {
	ios::sync_with_stdio(false);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>src[i];
	cin>>q;
	zero.n=3; zero.m=1;
	zero.a[1][1]=zero.a[2][1]=-1e+9;
	build(1,1,n);
	for(int i=1;i<=q;i++) {
		cin>>t1>>t2>>t3;
		if(t1==0) {
			modify(1,1,n,t2,t3);
		}
		else {
			Matrix r=query(1,1,n,t2,t3)*zero;
			cout<<r.a[2][1]<<endl;
		}
	}
}
