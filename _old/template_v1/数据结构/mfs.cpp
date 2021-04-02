int find(int x) { return f[x] == x ? x : f[x] = find(f[x]); }
void merge(int i,int j) {if(find(i)!=find(j)) f[find(i)]=find(j); }
