// Query sigma(c(i)^2), where c(i) is the number of occurrence of i
int n,m,k,b[100005];
long long cnt[100005],res[100005];
struct query{int l,r,block,id;}a[100005];
bool operator <(query a,query b){
	if(a.block==b.block)return a.r<b.r;
	return a.block<b.block;
}
int main(){
	scanf("%d%d%d",&n,&m,&k);
	int size=sqrt(n);
	for(int i=1;i<=n;i++) scanf("%d",&b[i]);
	for(int i=1;i<=m;i++){
		scanf("%d%d",&a[i].l,&a[i].r);
		a[i].id=i;
		a[i].block=(a[i].l-1)/size+1;
    }
	sort(a+1,a+m+1);
	int l=1,r=0; long long ans=0;
	for(int i=1;i<=m;i++){
		while(l>a[i].l) l--,cnt[b[l]]++,ans+=2*cnt[b[l]]-1;
		while(r<a[i].r) r++,cnt[b[r]]++,ans+=2*cnt[b[r]]-1;
		while(l<a[i].l) cnt[b[l]]--,ans-=2*cnt[b[l]]+1,l++;
		while(r>a[i].r) cnt[b[r]]--,ans-=2*cnt[b[r]]+1,r--;
		res[a[i].id]=ans;
    }
	for(int i=1;i<=m;i++) printf("%lld\n",res[i]);
}
