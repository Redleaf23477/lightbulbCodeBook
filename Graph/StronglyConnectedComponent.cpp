int V, E;
vector<int> G[MAXV];
vector<int> rG[MAXV];
vector<int> vs;//postorder
bool used[MAXV];
int comp[MAXV];//scc id, topologically ordered

void add_edge(int from, int to)
{
    G[from].pb(to);
    rG[to].pb(from);
}

void dfs(int u)//get postorder
{
    used[u] = true;
    for(int i=0;i<G[u].size();i++)
        if(!used[G[u][i]])dfs(G[u][i]);
    vs.pb(u);
}

void rdfs(int u, int k)
{
    used[u]=true;
    comp[u]=k;
    for(int i=0;i<rG[u].size();i++)
        if(!used[rG[u][i]])rdfs(rG[u][i],k);
}

int scc()//return scc cnt
{
    memset(used,0,sizeof(used));
    vs.clear();
    FOR(v,1,V)if(!used[v])dfs(v);
    memset(used,0,sizeof(used));
    int k = 0;//sccID
    FORD(i,V-1,0)
        if(!used[ vs[i] ])
        {
            rdfs(vs[i],k);
            k++;
        }
    return k;
}
