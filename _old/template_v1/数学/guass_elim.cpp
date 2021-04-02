#include <bits/stdc++.h>
#define eps 1e-6
using namespace std;

const int N = 1005;

double a[N][N];
int n,p=1;

void gauss_jordan() {
	for(int i=1;i<=n;i++) {
		int r=i;
		for(int j=i+1;j<=n;j++) if(fabs(a[j][i])>fabs(a[r][i])) r=j;
		if(r-i) {for(int j=1;j<=n+1;j++) swap(a[i][j],a[r][j]);}
		if(fabs(a[i][i])<eps) {p=0; return;}
		for(int j=1;j<=n;j++) if(j-i) {
			double tmp=a[j][i]/a[i][i];
			for(int k=i+1;k<=n+1;k++) a[j][k]-=a[i][k]*tmp;
		}
	}
	for(int i=1;i<=n;i++) a[i][n+1]/=a[i][i];
}

int main() {
	cin>>n;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n+1;j++)
			cin>>a[i][j];
	gauss_jordan();
	if(p)
		for(int i=1;i<=n;i++) printf("%.2f\n",a[i][n+1]);
	else cout<<"No Solution"<<endl;
}

// Modu det
// Warning: tot = n - 1
// the template is designed for Matrix Tree
int Gauss()
{
    int ans = 1;
    for(int i = 1; i < tot; i ++) // !!!!
    {
        for(int j = i + 1; j < tot; j ++)
            while(f[j][i])
            {
                int t = f[i][i] / f[j][i];
                for(int k = i; k < tot; k ++)
                    f[i][k] = (f[i][k] - t * f[j][k] + mod) % mod;
                swap(f[i], f[j]);
                ans = - ans;
            }
        ans = (ans * f[i][i]) % mod;
    }
    return (ans + mod) % mod;
}
