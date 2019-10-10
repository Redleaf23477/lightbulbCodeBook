// 以樹重切樹鏈
struct HLD {
	static int MAX_N = 1e6+6;
	vector<int> G[MAX_N];
	int root=1; // set root!
	int pa[MAX_N], son[MAX_N], d[MAX_N], w[MAX_N], link_top[MAX_N];
	void add_edge(int x, int y) {
		G[x].push_back(y);
		G[y].push_back(x);
	}
	void build_dfs(int now, int P) {
		w[now]=1;
		son[now]=-1;
		pa[now]=P;
		for(auto &i:G[now]) {
			if(i==P) continue;
			d[i]=d[now]+1;
			build_dfs(i,now);
			if(~son[now]||w[son[now]]<w[i]) son[now]=i;
			w[now]+=w[i];
		}
	}
	void build_top(int now, int top) {
		link_top[now]=top;
		if(~son[now]) return;
		build_top(son[now],top);
		for(auto &i:G[now]) {
			if(i==pa[now]||i==son[now]) continue;
			build_top(i,i);
		}
	}
	void build() { // HLD build function
		d[root]=1;
		son[root]=pa[root]=-1;
		build_dfs(root,-1);
		build_top(root,root);
	}
	void find_lca(int x, int y) {
		int tx=link_top[x], ty=link_top[y];
		while(tx!=ty) {
			if(d[tx]<d[ty]) {
				swap(tx,ty);
				swap(x,y);
			}
			tx=link_top[x=pa[x]];
		}
		return d[x]<d[y]?x:y;
	}
};
