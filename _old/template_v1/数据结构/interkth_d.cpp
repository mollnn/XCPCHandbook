// luogu-judger-enable-o2
// luogu-judger-enable-o2
#include <bits/stdc++.h>
using namespace std;

int a[10000005],b[10000005],ch[10000005][2],chb[10000005][2],src[100005],ind,idx,InnerSize,t1,t2,t3,t4,n,m,root;
char str[10];
const int Inf = 1000000007;

void inner_modify(int &p,int l,int r,int pos,int key){
	if(!p) p=++ind;
	//printf("inner_modify %d %d %d %d %d\n",p,l,r,pos,key);
	a[p]+=key;
	if(l-r){
		if(pos<=(l+r)/2){
			inner_modify(ch[p][0],l,(l+r)/2,pos,key);
		}
		else{
			inner_modify(ch[p][1],(l+r)/2+1,r,pos,key);
		}
	}
}

int inner_query(int p,int l,int r,int ql,int qr){
	//printf("inner_query %d %d %d %d %d\n",p,l,r,ql,qr);
	if(!p) return 0;
	if(l>qr||r<ql) return 0;
	if(l>=ql&&r<=qr) return a[p];
	return inner_query(ch[p][0],l,(l+r)/2,ql,qr)+inner_query(ch[p][1],(l+r)/2+1,r,ql,qr);
}

void outer_modify(int &p,int l,int r,int pos,int inner_pos,int inner_key){
	if(!p) p=++idx;
	//printf("outer_modify %d %d %d %d %d %d\n",p,l,r,pos,inner_pos,inner_key);
	inner_modify(b[p],1,n,inner_pos,inner_key);
	if(l-r){
		if(pos<=(l+r)/2){
			outer_modify(chb[p][0],l,(l+r)/2,pos,inner_pos,inner_key);
		}
		else{
			outer_modify(chb[p][1],(l+r)/2+1,r,pos,inner_pos,inner_key);
		}
	}
}

int outer_query(int p,int l,int r,int lb,int rb,int k){
	//printf("outer_query %d %d %d %d %d %d \n",p,l,r,lb,rb,k);
	int res=inner_query(b[chb[p][0]],1,n,lb,rb);
	if(l==r) return r;
	if(res>=k) return outer_query(chb[p][0],l,(l+r)/2,lb,rb,k);
	else return outer_query(chb[p][1],(l+r)/2+1,r,lb,rb,k-res);
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d",&src[i]);
		outer_modify(root,1,Inf,src[i],i,1);
	}
	for(int i=1;i<=m;i++){
		scanf("%s%d%d",&str,&t1,&t2);
		if(str[0]=='Q'){
			scanf("%d",&t3);
			printf("%d\n",outer_query(root,1,Inf,t1,t2,t3));
		}
		else{
			outer_modify(root,1,Inf,src[t1],t1,-1);
			outer_modify(root,1,Inf,t2,t1,1);
			src[t1]=t2;
		}
	}
}
