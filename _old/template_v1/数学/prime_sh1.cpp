// Eratosthenes's Algorithm
const int MAXN = 20000005;
bool np[MAXN]; // True means not a prime

void presolve() {
    memset(np,0,sizeof np);
    np[0]=np[1]=1;
    for(int i=2;i<MAXN;i++)
        if(!np[i] && i<=MAXN/i)
            for(int j=i*i;j<MAXN;j+=i) np[j]=1;
}
