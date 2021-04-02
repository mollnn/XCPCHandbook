#include <bits/stdc++.h>
using namespace std;

char s[1000005],p[1000005];
int n,m,fail[1000005];

int main() {
	ios::sync_with_stdio(false);
	cin>>s+1>>p+1;
	n=strlen(s+1); m=strlen(p+1); // Care for the order
	// Build fail array for pattern string
	for(int i=2;i<=m;i++) {
		fail[i]=fail[i-1];
		while(p[fail[i]+1]-p[i] && fail[i]) fail[i]=fail[fail[i]];
		if(p[fail[i]+1]==p[i]) ++fail[i];
	}

	fail[0]=-1;
	for(int i=1,j=1;i<=n;) {
		if(s[i]==p[j]) {
			if(j<m) ++i,++j;
			else {
				cout<<i-m+1<<endl;
				j=fail[j-1]+1;
			}
		}
		else {
			j=fail[j-1]+1;
			if(j<=0) j=1,i++;
		}
	}
	for(int i=1;i<=m;i++) cout<<(fail[i]<0?0:fail[i])<<" ";
	cout<<endl;
}
