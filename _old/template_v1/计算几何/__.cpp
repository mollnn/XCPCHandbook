#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;
int a[105],used[105],n,len,m,minn=0,sum=0,bj;
bool cmp(const int &x,const int &y)
{
	return x>y;
}
void dfs(int k,int last,int rest)
{
	if (k==m)
	{
		cout<<len<<endl;
		exit(0);
	}
	if (rest==0)
	{
		for (int i=1;i<=n;i++)
		{
			if (!used[i])
			{
				used[i]=1;
				dfs(k+1,i,len-a[i]);
				used[i]=0;
				break;
			}
		}
	}
	for (int i=last+1;i<=n;i++)
	if (!used[i] && rest>=a[i])
	{
		used[i]=1;
		dfs(k,i,rest-a[i]);
		used[i]=0;
		if(rest==a[i]||rest==len)
		return;
        while(a[i]==a[i+1])i++;
        if(i==n)return;
	}
}
int main()
{
	cin>>n;
	for (int i=1;i<=n;i++)
	{
		cin>>a[i];
		minn=max(minn,a[i]);
		sum=sum+a[i];
	}
	sort(a+1,a+n+1,cmp);
	for (int i=minn;i<=sum;i++)
	{
		if (sum%i==0)
		{
			memset(used,0,sizeof(used));
			len=i;
			used[1]=1;
			bj=0;
			m=sum/i;
			dfs(1,1,len-a[i]);
		}
	}
}