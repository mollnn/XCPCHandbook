#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 50005;

int pr[N],is[N],mu[N],cnt;

signed main() {
	mu[0]=mu[1]=1; is[1]=1;
	for(int i=2;i<=N;i++) {
		if(is[i]==0) {
			pr[++cnt]=i;
			mu[i]=-1;
		}
		for(int j=1; j<=cnt&&pr[j]*i<N; ++j) {
			is[pr[j]*i]=1;
			if(i%pr[j]==0) {
				mu[pr[j]*i]=0;
				break;
			}
			else {
				mu[pr[j]*i]=-mu[i];
			}
		}
	}
	for(int i=1;i<=N;i++) mu[i]+=mu[i-1];
	int T;
	cin>>T;
	while(T--) {
		int n,m,d;
		cin>>n>>m>>d;
		n/=d; m/=d;
		long long ans=0;
		for(int l=1,r;l<=min(n,m);l=r+1) {
			r=min(n/(n/l),m/(m/l));
			ans+=(n/l)*(m/l)*(mu[r]-mu[l-1]);
		}
		cout<<ans<<endl;
	}
}
