// How many different substrings are there in the main string
#include <bits/stdc++.h>
using namespace std;

int n,m=256,sa[1000005],y[1000005],u[1000005],v[1000005],o[1000005],r[1000005],h[1000005],T;
// sa: Suffix Array
// r: Rank Array
// h: Height Array (between sa[i] & sa[i-1])
char str[1000005];
long long ans;

int main(){
	ios::sync_with_stdio(false);

	cin>>T;

	while(T--) {
		memset(sa,0,sizeof sa);
		memset(y,0,sizeof y);
		memset(u,0,sizeof u);
		memset(v,0,sizeof v);
		memset(o,0,sizeof o);
		memset(r,0,sizeof r);
		memset(h,0,sizeof h);

		cin>>str+1;
		n=strlen(str+1);

		for(int i=1;i<=n;i++) u[str[i]]++;
		for(int i=1;i<=m;i++) u[i]+=u[i-1];
		for(int i=n;i>=1;i--) sa[u[str[i]]--]=i;
		r[sa[1]]=1;
		for(int i=2;i<=n;i++) r[sa[i]]=r[sa[i-1]]+(str[sa[i]]!=str[sa[i-1]]);

		for(int l=1;r[sa[n]]<n;l<<=1) {
			memset(u,0,sizeof u);
			memset(v,0,sizeof v);
			memcpy(o,r,sizeof r);
			for(int i=1;i<=n;i++) u[r[i]]++, v[r[i+l]]++;
			for(int i=1;i<=n;i++) u[i]+=u[i-1], v[i]+=v[i-1];
			for(int i=n;i>=1;i--) y[v[r[i+l]]--]=i;
			for(int i=n;i>=1;i--) sa[u[r[y[i]]]--]=y[i];
			r[sa[1]]=1;
			for(int i=2;i<=n;i++) r[sa[i]]=r[sa[i-1]]+((o[sa[i]]!=o[sa[i-1]])||(o[sa[i]+l]!=o[sa[i-1]+l]));
		}
		{
			int i,j,k=0;
			for(int i=1;i<=n;h[r[i++]]=k)
				for(k?k--:0,j=sa[r[i]-1];str[i+k]==str[j+k];k++);
		}

		ans=(long long)n*(long long)(n+1)/(long long)2;
		for(int i=1;i<=n;i++) ans-=(long long)h[i];

		cout<<ans<<endl;
	}
}
