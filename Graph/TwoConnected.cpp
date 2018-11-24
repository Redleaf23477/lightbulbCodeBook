vector<int> G[MAXN];
vector<int> bcc[MAXN]; // bcc內的點
 
int dfn[MAXN], low[MAXN], tim, ans;
int st[MAXN], top;
int bccID[MAXN], bcc_cnt;// 每個點的bcc編號
bool is_cut[MAXN]; // 是否為割點, 割點的ID會被覆蓋

void tarjan(int u, int p){ // p->u
    int child= 0, w;
    dfn[u] = low[u] = ++tim;
    st[top++] = u;
    for(auto v:G[u]){ // u->v
        if(!dfn[v]){
            tarjan(v, u);  child++;
            low[u]= min(low[u], low[v]);
            if(low[v] >= dfn[u]){
                is_cut[u]= true;
				 do{
                    w = st[--top];
                    bccID[w]= bcc_cnt;
                    bcc[bcc_cnt].push_back(w);
                }while(dfn[w] > dfn[v]);
                bccID[u]= bcc_cnt;
                bcc[bcc_cnt++].push_back(u);
            }
        }
        else if(v != p)
            low[u]= min(low[u], dfn[v]);
    }

    if(p == -1 && child<2)
        is_cut[u]= false;
}
