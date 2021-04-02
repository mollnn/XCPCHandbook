#include <bits/stdc++.h>
using namespace std;

namespace Trie {
    struct Node {
        Node *ch[2];
        Node* clear() {
            ch[0]=ch[1]=0;
            return this; // Don't forget this
        }
    };
    Node *root;
    Node pool[4000005];
    int ind;
    Node* newnode() {
        return pool[ind++].clear();
    }
    void insert(int x) {
        Node *pos = root;
        for(int i=30;i>=0;--i) {
            int b=(x/(1<<i))&1;
            if(pos->ch[b]==NULL) pos->ch[b]=newnode();
            pos=pos->ch[b];
        }
    }
    int query(int x) {
        Node *pos = root;
        int ans = 0;
        for(int i=30;i>=0 && pos!=NULL;--i) {
            int b=(x/(1<<i))&1;
            if(pos->ch[b^1]!=NULL)
                pos=pos->ch[b^1], ans+=(1<<i);
            else pos=pos->ch[b];
        }
        return ans;
    }
    int a[1000005];
    void solve() {
        int n,ans=0;
        cin>>n;
        root=newnode(); // Don't forget this
        for(int i=1;i<=n;i++) cin>>a[i], insert(a[i]);
        for(int i=1;i<=n;i++) ans=max(ans,query(a[i]));
        cout<<ans<<endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    Trie::solve();
}
