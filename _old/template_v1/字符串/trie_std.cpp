#include <bits/stdc++.h>
using namespace std;

namespace Trie {
    struct Node {
        Node *ch[10];
        int val;
        Node* clear() {
            for(int i=0;i<10;i++) ch[i]=NULL;
            val=0;
            return this;
        }
    };

    Node *root;
    Node pool[1000005];
    int ind=0;
    Node* newnode() {
        return pool[ind++].clear();
    }

    void clear() {
        ind=0;
        root=newnode();
    }
    void insert(string s) {
        Node *pos=root;
        for(int i=0;i<s.length();i++) {
            if(pos->ch[s[i]]==NULL) pos->ch[s[i]]=newnode();
            pos->val++;
            pos=pos->ch[s[i]];
        }
    }
    int query(string s) {
        Node *pos=root;
        for(int i=0;i<s.length();i++) {
            if(pos->ch[s[i]]==NULL) return 0;
            pos=pos->ch[s[i]];
        }
        return pos->val;
    }

    string str[10005];

    void solve() {
        int n;
        cin>>n;
        clear();
        for(int i=1;i<=n;i++) {
            cin>>str[i];
            for(int j=0;j<str[i].length();j++) str[i][j] -= '0';
            insert(str[i]);
        }
        int flag=0;
        for(int i=1;i<=n;i++) {
            if(query(str[i])) {
                flag=1;
                break;
            }
        }
        if(flag) cout<<"NO"<<endl;
        else cout<<"YES"<<endl;
    }
}

int main() {
    int t;
    ios::sync_with_stdio(false);
    cin>>t;
    while(t--) Trie::solve();
    return 0;
}
