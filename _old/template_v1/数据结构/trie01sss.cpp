#include<bits/stdc++.h>
using namespace std;

int ch[1000005][2],val[1000005],cnt[1000005],root[1000005],ts[105],ind,n,m;

void insert(int p,int p0,int dep) {
    ch[p][0]=ch[p0][0];
    ch[p][1]=ch[p0][1];
    if(dep==30) return;
    if(ch[p0][ts[dep+1]]==0) {
        ch[p][ts[dep+1]]=++ind;
        val[ind]=ts[dep+1];
        cnt[ind]=1;
        insert(ind,ch[p0][ts[dep+1]],dep+1);
    }
    else {
        ch[p][ts[dep+1]]=++ind;
        val[ind]=ts[dep+1];
        cnt[ch[p][ts[dep+1]]]=cnt[ch[p0][ts[dep+1]]]+1;
        insert(ch[p][ts[dep+1]],ch[p0][ts[dep+1]],dep+1);
    }
}

void trie_insert(int rtx,int num) {
    for(int i=1;i<=30;i++)
        ts[i]=(num>>(30-i))&1;
    insert(root[rtx],root[rtx-1],0);
}

int xormax(int rtx,int rty,int num) {
    int p=root[rtx], q=root[rty], ans=0;
    for(int i=29;i>=0;i--) {
        if((num>>i)&1) {
            if(cnt[ch[q][0]]-cnt[ch[p][0]]) ans=ans*2+1, p=ch[p][0], q=ch[q][0];
            else ans=ans*2, p=ch[p][1], q=ch[q][1];
        }
        else {
            if(cnt[ch[q][1]]-cnt[ch[p][1]]) ans=ans*2+1, p=ch[p][1], q=ch[q][1];
            else ans=ans*2, p=ch[p][0], q=ch[q][0];
        }
    }
    return ans;
}

int main() {
    cin>>n;
    for(int i=1;i<=n;i++) {
        int t;
        cin>>t;
        root[i]=++ind;
        trie_insert(i,t);
    }
    cin>>m;
    for(int i=1;i<=m;i++) {
        int t1,t2,t3;
        cin>>t1>>t2>>t3;
        t1--;
        cout<<xormax(t1,t2,t3)<<endl;
    }
}
