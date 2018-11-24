vector<int> G[MAXN];
int dfn[MAXN], low[MAXN], tim, ans;
void tarjan(int u, int p){ // p -> u
    int child=0, cut_node=0;
    dfn[u] = low[u] = ++tim;
    for(auto v:G[u]){ // u -> v
        if(!dfn[v]){ // tree edge
            tarjan(v, u); child++;
            low[u]= min(low[u], low[v]);
            if(low[v] >= dfn[u]) cut_node=1;
        }
        else if(v!=p)  //back edge
            low[u]= min(low[u], dfn[v]);
    }

    if(p!=-1 && cut_node) ans++;
    if(p==-1 && child>=2) ans++;
}
//how to call
for(int i=0; i<n; i++)
	if(!dnf[i])
		tarjan(i, -1);
