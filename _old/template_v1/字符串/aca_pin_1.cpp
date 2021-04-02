#include <bits/stdc++.h>
using namespace std;

namespace ACA {
    struct Node {
        Node* ch[26], *fail;
        int val;
        // Default value: fail=root ch=NULL
        Node* clear(Node* defFail) {
            fail=defFail;
            for(int i=0;i<26;i++) ch[i]=0;
            val=0;
            return this;
        }
    };
    Node *root = NULL, pool[1000005];
    int index;
    Node* newnode() {
        return pool[index++].clear(root);
    }
    void insert(string str) {
        Node *p=root;
        for(int i=0;i<str.length();i++) {
            int v=str[i]-'a';
            if(!p->ch[v]) p->ch[v]=newnode();
            p=p->ch[v];
        }
        p->val++;
    }
    void build() {
        queue <Node*> q;
        for(int i=0;i<26;i++) if(root->ch[i]) q.push(root->ch[i]);
        while(!q.empty()) {
            Node* p=q.front(); q.pop();

            for(int i=0;i<26;i++) {
                if(p->ch[i]!=NULL)
                    p->ch[i]->fail = (p->fail->ch[i])?((p->fail->ch[i])):root,
                    q.push(p->ch[i]);
                else p->ch[i] = p->fail->ch[i];
            }
        }
    }
    int query(string str) {
        Node *p=root; int ans = 0;
        for(int i=0;i<str.length();i++) {
            p=p->ch[str[i]-'a'];
            if(p==NULL) p=root; // Attention!
            for(Node* t=p; t!=root && ~(t->val); t=t->fail)
                ans+=t->val, t->val=-1;
        }
        return ans;
    }
    void solve() {
        int n;
        cin>>n;
        index=0;
        root=newnode();
        for(int i=1;i<=n;i++) {
            string tmp;
            cin>>tmp;
            insert(tmp);
        }
        build();
        string art;
        cin>>art;
        cout<<query(art)<<endl;
    }
}

int main() {
    int T;
    //ios::sync_with_stdio(false);
    cin>>T;
    while(T--) ACA::solve();
}
