#include<bits/stdc++.h>
#define N 262145
#define pi acos(-1)
using namespace std;
typedef complex<double> E;
int n,m,L;
int R[N];
E a[N],b[N];
void fft(E *a,int f){
	for(int i=0;i<n;i++)if(i<R[i])swap(a[i],a[R[i]]);
	for(int i=1;i<n;i<<=1){
		E wn(cos(pi/i),f*sin(pi/i));
		for(int p=i<<1,j=0;j<n;j+=p){
			E w(1,0);
			for(int k=0;k<i;k++,w*=wn){
				E x=a[j+k],y=w*a[j+k+i];
				a[j+k]=x+y;a[j+k+i]=x-y;
			}
		}
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=0,x;i<=n;i++)scanf("%d",&x),a[i]=x;
	for(int i=0,x;i<=m;i++)scanf("%d",&x),b[i]=x;
	m=n+m;for(n=1;n<=m;n<<=1)L++;
	for(int i=0;i<n;i++)R[i]=(R[i>>1]>>1)|((i&1)<<(L-1));
	fft(a,1);fft(b,1);
	for(int i=0;i<=n;i++)a[i]=a[i]*b[i];
	fft(a,-1);
	for(int i=0;i<=m;i++)printf("%d ",(int)(a[i].real()/n+0.5));
	return 0;
}
