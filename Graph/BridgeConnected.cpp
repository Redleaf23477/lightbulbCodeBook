struct edge{
    int from, to;
    edge(int u, int v):from(u), to(v){}
};
vector<edge> bridge;
vector<int> G[MAXN];
int dfn[MAXN], low[MAXN], tim;
int bccID[MAXN], bccCNT;
int st[MAXN], top;

void tarjan(int u, int p){ // p->u
    dfn[u]= low[u]= ++tim;
    st[top++]= u;
    for(auto v:G[u]){ // u->v
        if(!dfn[v]){
            tarjan(v, u);
            low[u]= min(low[u], low[v]);
            if(low[v] > dfn[u])
               bridge.push_back(edge(u, v));
        }
        else if(v != p)
            low[u]= min(low[u], dfn[v]);
    }

    if(dfn[u] == low[u]){
        int w;
        do{
            w= st[--top];
            bccID[w]= bccCNT;
        }while(w != u);
        bccCNT++;
    }
}

