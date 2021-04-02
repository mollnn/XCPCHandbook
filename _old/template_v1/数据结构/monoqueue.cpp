#include <bits/stdc++.h>
using namespace std;

int n,k,a[1000005];

struct Monoqueue {
	deque <pair<int,int> > q;
	void push(int num,int tim) {
		while(q.size() && q.back().first < num)
			q.pop_back();
		q.push_back(make_pair(num,tim));
	}
	int get(int tim) {
		while(q.size() && q.front().second < tim) 
			q.pop_front();
		if(q.size())
			return q.front().first;
		else return 0;
	}
} q,q2;

int main() {
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<k;i++) q.push(a[i], i+k-1), q2.push(-a[i], i+k-1);
	for(int i=k;i<=n;i++) {
		q2.push(-a[i], i+k-1);
		printf("%d ",-q2.get(i));
	}
	printf("\n");
	for(int i=k;i<=n;i++) {
		q.push(a[i], i+k-1);
		printf("%d ",q.get(i));
	}
	
	
}
