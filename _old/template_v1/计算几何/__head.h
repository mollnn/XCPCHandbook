#include <bits/stdc++.h>
using namespace std;
#define mp make_pair
#define fi first
#define se second
#define pb push_back
typedef double db;
const db eps = 1e-6;
const db pi = acos(-1);
int sign(db k) {
	if (k > eps) return 1; else if (k < -eps) return -1; return 0;
}
int cmp(db p1, db p2) { return sign(p1 - p2); }
int inmid(db p1, db p2, db p3) { return sign(p1 - p3) * sign(p2 - p3) <= 0; }// p3 in [p1,p2] 
