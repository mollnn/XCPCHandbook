// Linear Programming
// [Number of vars] [Number of res] [if Output Solution]
// [ci]
// [ai1 ai2 ... ain] [bi]
// Maximize sum cjxj  with the restriction sum aijxj <= bi
#include<bits/stdc++.h>
using namespace std;

template <typename T> void chmin(T&x,const T &y)
{
	if(x>y)x=y;
}
template <typename T> void chmax(T &x,const T &y)
{
	if(x<y)x=y;
}
typedef long long s64;
#define rep(i,l,r) for(int i=l;i<=r;++i)
#define per(i,r,l) for(int i=r;i>=l;--i)
#define gc (c=getchar())
int read()
{
	char c;
	while(gc<'-');
	if(c=='-')
	{
		int x=gc-'0';
		while(gc>='0')x=x*10+c-'0';
		return -x;
	}
	int x=c-'0';
	while(gc>='0')x=x*10+c-'0';
	return x;
}
#undef gc

const int W=1e8,B=20,T=60;
struct db
{
	int a[T],n;
	bool is_neg;
	int& operator [](int x)
	{
		return a[x];
	}
	int operator [](int x)const
	{
		return a[x];
	}
	void left_move(int l)
	{
		per(i,n-1,0)a[i+l]=a[i];
		rep(i,0,l-1)a[i]=0;
		n+=l;
	}
	db (int x=0)
	{
		memset(a,0,sizeof(a));n=B;
		is_neg=0;
		if(x<0){is_neg=1;x=-x;}
		while(x){a[n++]=x%W;x/=W;}
	}
	void print(char c='\n')const
	{
		if(is_neg)putchar('-');
		if(n>B)
		{
			printf("%d",a[n-1]);
			per(i,n-2,B)printf("%.8d",a[i]);
		}
		else printf("0");
	
		printf(".");
		per(i,B-1,B-2)printf("%.8d",a[i]);
		printf("%c",c);
	}
	long double evalu(int l)const
	{
		long double x=0;
		per(i,n-1,l)x=x*W+a[i];
		return x;
	}
};
bool operator <(const db &a,const db &b)
{
	if(a.is_neg)
	{
		if(!b.is_neg)return 1;
		per(i,T-1,0)
		if(a[i]!=b[i])return a[i]>b[i];
		return 0; 
	}
	else
	{
		if(b.is_neg)return 0;
		per(i,T-1,0)
		if(a[i]!=b[i])return a[i]<b[i];
		return 0; 
	}
}
bool operator >=(const db &a,const db &b)
{
	return !(a<b);
}
bool operator <=(const db &a,const db &b)
{
	return b>=a;
}
bool operator >(const db &a,const db &b)
{
	return b<a;
}
bool operator !(const db &a)
{
	int n=a.n;
	while(n&&!a[n-1])--n;
	return !n;
}
db operator -(db a)
{
	a.is_neg^=1;
	return a;
}
db operator +(db a,const db &b);
db operator -(db a,db b)
{
	b=-b;
	if(a.is_neg)
	{
		if(!b.is_neg)
		{
			a=-a;
			swap(a,b);
		}
		else return a+b;
	}
	else
	{
		if(b.is_neg)
		{
			b=-b;
		}
		else return a+b;
	}
	if(a<b)return -(b-a);
	
	rep(i,0,a.n-1)
	if((a[i]-=b[i])<0)
	{
		a[i]+=W;
		--a[i+1];
	}
	while(a.n&&!a[a.n-1])--a.n;
	return a;
}
db operator +(db a,const db &b)
{
	if(a.is_neg)
	{
		if(!b.is_neg)return b-(-a);
	}
	else
	{
		if(b.is_neg)return a-(-b);
	}
	chmax(a.n,b.n);
	rep(i,0,a.n-1)
	if((a[i]+=b[i])>=W)
	{
		a[i]-=W;
		++a[i+1];
	}
	if(a[a.n])++a.n;
	return a;
}
void operator +=(db &a,const db &b)
{
	a=a+b;
}
void operator -=(db &a,const db &b)
{
	a=a-b;
}
db eps1,eps2,eps3;
db operator *(const db &a,const db &b)
{
	db ans;
	ans.is_neg=a.is_neg^b.is_neg;
	ans.n=max(0,a.n+b.n-B);
	rep(i,0,ans.n)
	{
		int jk=i+B;s64 sum=0;
		rep(j,max(0,jk-(b.n-1)),min(jk,a.n-1))sum+=(s64)a[j]*b[jk-j]; 
		int x=i;
		while(sum)
		{
			ans[x]+=sum%W;
			sum/=W;
			++x;
		}
	}
	rep(i,0,ans.n)
	while(ans[i]>=W)
	{
		ans[i]-=W;
		++ans[i+1];
	}
	if(ans.n&&!ans[ans.n-1])--ans.n;
	return ans;
}
void operator *=(db &a,const db &b)
{
	a=a*b;
}
db operator *(db a,int k)
{
	per(i,a.n-1,0)
	{
		s64 sum=(s64)a[i]*k;
		a[i]=sum%W;
		a[i+1]+=sum/W;
	}
	rep(i,0,a.n-1)
	while(a[i]>=W)
	{
		a[i]-=W;
		++a[i+1];
	}
	if(a[a.n])++a.n;
	return a;
}
db operator *(int k,const db &a)
{
	return a*k;
}
db operator /(db a,db b)
{
//	a.print();
//	b.print();
	a.is_neg^=b.is_neg;
	b.is_neg=0;
	a.left_move(B);
	int l=max(0,b.n-20);
	long double b_e=b.evalu(l);
//	a.print();
//	b.print();
//	if(!b_e)return a;
	db x;x.n=0;
	per(i,a.n-1,0)
	{
//		cerr<<i<<endl;
		x.left_move(1);x[0]=a[i];
//		cerr<<i<<endl;
		if(x>=b)
		{
			int k=x.evalu(l)/b_e;
			if(k)--k;
//			cerr<<k<<endl;
			a[i]=k;
			x-=k*b;
			while(x>=b)
			{
//				cerr<<i<<endl;
				x-=b;
				++a[i];
			}
		}else a[i]=0;
	}
//	a.print();
//	b.print();
	while(a.n&&!a[a.n-1])--a.n;
//	cerr<<a.n<<" "<<a[a.n-1]<<endl;
//	a.print();
//	b.print();
	return a;
}
void operator /=(db &a,const db &b)
{
	a=a/b;
}

int cmp(const db &x,const db &eps)
{
	return x<-eps?-1:x>eps;
}
const int N=20+1,M=20+1,inf=1e9;
db a[M][N],b[M];
int idn[N],idm[M];
int n,m;
void pivot(int x,int y)
{
//	cerr<<x<<" "<<y<<endl;
	swap(idm[x],idn[y]);
	db k=a[x][y];
//	k.print();
	rep(j,1,n)a[x][j]/=k; 
//	exit(0);
	b[x]/=k;
	a[x][y]=1/k;
	rep(i,0,m)
	if(i!=x)
	{
		k=a[i][y];
		b[i]-=k*b[x];
		a[i][y]=0;
		rep(j,1,n)a[i][j]-=a[x][j]*k;
	}
}
void simplex()
{
//	cerr<<1<<endl;
	idn[0]=inf;
	while(1)
	{
		int y=0;
		rep(j,1,n)
		if(cmp(a[0][j],eps1)>0&&idn[j]<idn[y])y=j;
		//cerr<<1<<endl;
		if(!y)break;
		int x=0;
		rep(i,1,m)
		if(cmp(a[i][y],eps1)>0)
		{
		//	cerr<<i<<endl;
			if(!x)x=i;
			else
			{
		//		cerr<<i<<endl;
		//		a[i][y].print();
		//		a[x][y].print();
				int t=cmp(b[i]/a[i][y]-b[x]/a[x][y],eps2);
				if(t<0||(t==0&&idm[i]<idm[x]))x=i;
		//		cerr<<i<<endl;
			}
		}
//		cerr<<x<<" "<<y<<endl;
		if(!x)
		{
			puts("Unbounded");			
			exit(0);
		}
		pivot(x,y);
	}
}
void init()
{
	idm[0]=inf;idn[0]=inf;
	while(1)
	{
		int x=0;
		rep(i,1,m)
		if(cmp(b[i],eps3)<0&&idm[i]<idm[x])x=i;
		if(!x)break;
		int y=0;
		rep(j,1,n)
		if(cmp(a[x][j],eps3)<0&&idn[j]<idn[y])y=j;
		if(!y)
		{
			puts("Infeasible");
			exit(0);
		}
		pivot(x,y);
	}
}

int main()
{
#ifdef kcz
	freopen("1.in","r",stdin);//freopen("1.out","w",stdout);
#endif
	eps1.n=B-10;eps1[eps1.n-1]=1;
	eps2.n=B;eps2[eps2.n-1]=1;
	eps3.n=B-10;eps3[eps3.n-1]=1;
	//eps1.print();
	
	int t;
	n=read();m=read();t=read();
	rep(j,1,n)a[0][j]=read();
	rep(i,1,m)
	{
		rep(j,1,n)a[i][j]=read();
		b[i]=read();
	}
	rep(j,1,n)idn[j]=j;
	rep(i,1,m)idm[i]=n+i;
	init();
	simplex();
	(-b[0]).print('\n');
	if(t)
	{
		rep(j,1,n)
		{
			rep(i,1,m)
			if(idm[i]==j)
			{
				b[i].print(' ');
				goto Find ;
			}
			printf("0 ");
			Find : ;
		}
		puts("");
	}
}
