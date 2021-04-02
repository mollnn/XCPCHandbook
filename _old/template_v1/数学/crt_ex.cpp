// Input: n,ai[],bi[]
// Method: solve()
// Output: (returned)
namespace excrt {
const int maxn=100010;
int n;
int ai[maxn],bi[maxn]; //x=a%b
int mul(int a,int b,int mod){
    int res=0;
    while(b>0){
        if(b&1) res=(res+a)%mod;
        a=(a+a)%mod;
        b>>=1;
    }
    return res;
}
int exgcd(int a,int b,int &x,int &y){
    if(b==0){x=1;y=0;return a;}
    int gcd=exgcd(b,a%b,x,y);
    int tp=x;
    x=y; y=tp-a/b*y;
    return gcd;
}
int solve(){
    int x,y,k;
    int M=bi[1],ans=ai[1];
    for(int i=2;i<=n;i++){
        int a=M,b=bi[i],c=(ai[i]-ans%b+b)%b;
        int gcd=exgcd(a,b,x,y),bg=b/gcd;
        if(c%gcd!=0) return -1;
        x=mul(x,c/gcd,bg);
        ans+=x*M;
        M*=bg;
        ans=(ans%M+M)%M;
    }
    return (ans%M+M)%M;
}
}

signed main(){
    int n;
    cin>>n;
    excrt::n=n;
    for(int i=1;i<=n;++i) cin>>excrt::bi[i]>>excrt::ai[i]; //x=a%b
    cout<<excrt::solve();
}
