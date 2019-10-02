const int MAX_N;
vector<int> link[MAX_N]; //edge

void dfs_build(int now, int fa, int *weight, int *depth, int *pa, int *son){
	weight[now]=1;
	son[now]=-1;
	pa[now]=fa;
	for(auto i:link[now])
	{
		if(i==fa) continue;
		depth[i]=depth[now]+1;
		dfs_build(i,now,weight,depth,pa,son);
		if(son[now]==-1||weight[son[now]]<weight[i]) son[now]=i;
		weight[now]+=weight[i];
	}
}
void build_top(int now, int top,int *pa, int *son, int *link_top){
	link_top[now]=top;
	if(son[now]==-1) return;
	build_top(son[now],top,pa,son,link_top);
	for(auto i:link[now])
	{
		if(i==son[now]||i==pa[now]) continue;
		build_top(i,i,pa,son,link_top);
	}
}
inline void HLD(int *weight, int *depth, int *pa, int *son, int *link_top){
	memset(son,-1,sizeof(int)*MAX_N);
	depth[1]=1; //set node(1) as root
	dfs_build(1,0,weight,depth,pa,son);
	build_top(1,1,pa,son,link_top);
}
inline int find_lca(int x, int y, int *depth, int *pa, int *link_top){
	int tx=link_top[x], ty=link_top[y];
	while(tx!=ty)
	{
		if(depth[tx]<depth[ty])
		{
			swap(tx,ty);
			swap(x,y);
		}
		tx=link_top[x=pa[x]];
	}
	return depth[x]<depth[y]?x:y;
}
//usage: 
//build HeavyLightDecomposition: HLD
//find LCA(x,y): find_lca
