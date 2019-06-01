// copied from sylveon
// ap
void DFS(int v, int fa) //call DFS(v,v) at first
{
    D[v] = L[v] = timestamp++; //timestamp > 0
    int childCount = 0; //定理1 for root
    bool isAP = false;

    for (int w:adj[v])
    {
        if( w==fa ) continue;
        if ( !D[w] ) // D[w] = 0 if not visited
        {
            DFS(w,v);
            childCount++;
            if (D[v]<=L[w]) isAP = true; //定理2
            if (D[v]< L[w]) edgeBridge.emplace_back(v, w);//定理3
            L[v] = min(L[v], L[w]);
        }
        L[v] = min(L[v], D[w]);
    }
    if ( v == fa && childCount < 2 ) isAP = false; //定理1, v==fa只是確認root
    if ( isAP ) nodeAP.push_back(v);
    return ;
}
// SCC
void DFS(int v, int fa) { //call DFS(v,v) at first
    D[v] = L[v] = timestamp++; //timestamp > 0
    st.push(v);

    for (int w:adj[v]) {
        if( w==fa ) continue;
        if ( !D[w] ) { // D[w] = 0 if not visited
            DFS(w,v);
            L[v] = min(L[v], L[w]);
        }
        L[v] = min(L[v], D[w]);
    }
    if( D[v] == L[v] ) {
        int x;
        do{
            x = st.top();
            st.pop();
            scc[x] = SCCID;
        }while( x != v );
        SCCID++;
    }
}
