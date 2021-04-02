// 普通线段树，区间修改区间求和
long long a[1000005],t[1000005],src[1000005];
int n,m;
int t1,t2,t3,t4;
char ch[10];

void pushup(int p){
	a[p]=a[p*2]+a[p*2+1];
}

void pushdown(int p,int l,int r){
	a[p*2]+=(long long)t[p]*(long long)((l+r)/2-l+1);
	a[p*2+1]+=(long long)t[p]*(long long)(r-(l+r)/2);
	t[p*2]+=t[p]; t[p*2+1]+=t[p];
	t[p]=0;
}

void build(int p,int l,int r){
	if(l==r) a[p]=src[l];
	else build(p*2,l,(l+r)/2), build(p*2+1,(l+r)/2+1,r), pushup(p);
}

void modify(int p,int l,int r,int ql,int qr,long long k){
	if(l>qr||r<ql) return;
	if(l>=ql&&r<=qr) {a[p]+=(long long)k*(long long)(r-l+1), t[p]+=(long long)k; return;}
	pushdown(p,l,r);
	modify(p*2,l,(l+r)/2,ql,qr,k);
	modify(p*2+1,(l+r)/2+1,r,ql,qr,k);
	pushup(p);
}

long long query(int p,int l,int r,int ql,int qr){
	if(l>qr||r<ql) return 0;
	if(l>=ql&&r<=qr) return a[p];
	pushdown(p,l,r);
	return query(p*2,l,(l+r)/2,ql,qr)+query(p*2+1,(l+r)/2+1,r,ql,qr);
}
