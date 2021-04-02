#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

struct CantorExpansion {
	int calc(vector <int> perm) {
		int n = perm.size();
		int a[20];
		memset(a, 0, sizeof a);
		for (int i = 0; i < n; i++)
			for (int j = i + 1; j < n; j++)
				if (perm[i] > perm[j])
					a[i]++;
		int facBase = 1, ans = 0;
		for (int i = 0; i < n; i++) {
			ans += facBase * a[n - i - 1];
			facBase *= (i + 1);
		}
		return ans;
	}
	vector <int> incalc(vector <int> rem, int x) {
		int n = rem.size();
		vector <int> perm;
		int fac[20];
		fac[0] = 1;
		for (int i = 1; i <= n; i++) 
			fac[i] = fac[i - 1] * i;
		for (int i = n - 1; i >= 0; --i) {
			int q = x / fac[i], r = x % fac[i];
			x = r;
			sort(rem.begin(), rem.end());
			perm.push_back(rem[q]);
			rem.erase(rem.begin() + q);
		}
		return perm;
	}
} cantor;

void permPrint(vector <int> perm) {
	for (int i = 0; i < perm.size(); i++)
		cout << perm[i] << " ";
	cout << endl;
}

int main()
{
	vector <int> perm;
	vector <int> nums;
	for (int i = 1; i <= 5; i++) {
		int t;
		cin >> t;
		perm.push_back(t);
		nums.push_back(i);
	}
	cout << cantor.calc(perm) << endl;
	permPrint(cantor.incalc(nums, cantor.calc(perm)));
}