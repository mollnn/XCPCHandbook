const int MAXN = 20000005;
int prime[MAXN+1]; // Note: Let prime[0] donate the number of primes
// Note: the array "prime" has two different roles in the algorithm

void presolve() {
    memset(prime,0,sizeof prime);
    for(int i=2;i<=MAXN;i++) {
        if(!prime[i]) prime[++prime[0]]=i;
        for(int j=1;j<=prime[0]&&prime[j]<=MAXN/i;j++) {
            prime[prime[j]*i]=1;
            if(i%prime[j]==0) break;
        }
    }
}
