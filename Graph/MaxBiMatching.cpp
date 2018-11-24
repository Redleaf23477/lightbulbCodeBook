//注意: 變數V
#define MAXV 505
int V;//# of vertex
vector<int> G[MAXV];
int match[MAXV];
int used[MAXV];

void add_edge(int u, int v)
{
    G[u].pb(v);
    G[v].pb(u);
}

bool dfs(int u)
{
    used[u]=true;
    for(int i = 0; i < G[u].size(); i++)
    {
        int v = G[u][i], w = match[v];
        if(w<0 || !used[w]&&dfs(w) )
        {
            match[u]=v;
            match[v]=u;
            return true;
        }
    }
    return false;
}

int bip_match()
{
    int res=0;
    memset(match,-1,sizeof(match));
    for(int v=0; v<V; v++)
    {
        if(match[v]<0)
        {
            memset(used,0,sizeof(used));
            if(dfs(v))res++;
        }
    }
    return res;
}
