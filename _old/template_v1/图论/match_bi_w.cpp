// Input: g[v][u] (v in II, u in I)
// Method: solve(n1,n2)
// Output: ans, mat[u] (u in I)
namespace km {
const double inf=1e+9;
const int MX=405;
int n,m;
int py[MX],vy[MX],pre[MX];
double slk[MX],g[MX][MX],kx[MX],ky[MX],ans;
int mat[MX];
void clear() {
    n=m=0;
    reset(py); reset(vy); reset(pre);
    reset(slk); reset(g); reset(kx); reset(ky);
}
void KM(){
	int i,j,k,x,p=0;
	double d,t;
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
			kx[i]=max(kx[i],g[i][j]);
	for(i=1;i<=n;i++){
		memset(vy,0,sizeof(int)*(n+1));
		for(j=0;j<=n;j++) slk[j]=inf;
		memset(pre,0,sizeof(int)*(n+1));
		for(py[k=0]=i;py[k];k=p){
			d=inf;vy[k]=1;x=py[k];
			for(j=1;j<=n;j++)if(!vy[j]){
				if((t=kx[x]+ky[j]-g[x][j])<slk[j])slk[j]=t,pre[j]=k;
				if(slk[j]<d)d=slk[j],p=j;
			}
			for(j=0;j<=n;j++)
                if(vy[j])kx[py[j]]-=d,ky[j]+=d;
                else slk[j]-=d;
		}
		for(;k;k=pre[k])py[k]=py[pre[k]];
	}
}

void solve(int n1,int n2){
	n=max(n1,n2);
	KM();
	ans=0;
	for(int i=1;i<=n;i++)ans+=kx[i]+ky[i];
	for(int i=1;i<=n1;i++)mat[i]=(g[py[i]][i]?py[i]:0);
}
}
