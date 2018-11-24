void tarjan(int u,int p ){ // p -> u
    dfn[u] = low[u] = ++tim;

    for(auto v: G[u]){ //u->v
        if(!dfn[v]){
            tarjan(v, u);
            low[u] = min(low[u], low[v]);
            if(low[v] > dfn[u]){
                ans++;
                E.push_back(edge(u ,v));
            }
        }
        else if(v != p)
            low[u] = min(low[u], dfn[v]);
    }

}
struct edge{
    int from, to;
    edge(int u, int v):
         from(u), to(v){}
};
for(int i=0; i<n; i++)
	if(!dnf[i])
		tarjan(i, -1);
