// Input: n,k,m
//  n: Number of the Initial Cycle
//  k: We want to know the KTH player to leave
//  m: Jump m each round
#include <bits/stdc++.h>
using namespace std;
#define ll long long
int main() {
    ios::sync_with_stdio(false);
    ll T;
    cin>>T;
    for(int _T=1;_T<=T;_T++) {
        ll n,k,m,q;
        cin>>n>>k>>m;
        ll t=(m-1)%(n-k+1);
        if(m==1) t=k-1;
        else for(ll i=k-1;i>=1;i-=q) {
            q = min(i,max(1ll,(n-i-t)/m));
            t=(t+q*m)%(n-i+1);
        }
        cout<<"Case #"<<_T<<": "<<t+1<<endl;
    }
}

    /*ll t=(m-1)%(n-k+1);
    for(ll i=k-1;i>=1;--i) {
        t=(t+m)%(n-i+1);
    }
    cout<<t+1<<endl;

    t+qm = n-i
    qm = n-i-t
    q = (n-i-t)/m
    */

