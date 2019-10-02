/*
 *  SCC in an directed graph
 *  usage : init(), addEdge(), run()
 *  0-base graph
 */
class DirectedTarjan
{
private:
    int vn;
    int ts; // dfs timestamp
    int sccIdx;
    vector<vector<int>> graph;
    vector<int> low;
    vector<int> dep;
    stack<int> stk;
    vector<bool> inStk;
    vector<int> scc;  // scc[v] = id of scc
    void reportSCC(int v){
        int x;
        do{
            x = stk.top(); stk.pop();
            inStk[x] = false;
            scc[x] = sccIdx;
        } while(x != v);
        sccIdx++;
    }
    void dfs(int v) {
        low[v] = dep[v] = ++ts;
        stk.push(v); inStk[v] = true;
        for(auto c : graph[v]){
            if(dep[c] == 0){// not visited
                dfs(c);
                low[v] = min(low[v], low[c]);
            }
            if(inStk[c]) low[v] = min(low[v], dep[c]);
        }
        if(low[v] == dep[v]) reportSCC(v);
    }
public:
    void init(int v){
        vn = v, ts = 0, sccIdx = 0;
        graph.resize(v);
        low.resize(v, 0);
        dep.resize(v, 0);
        scc.resize(v, 0);
        inStk.resize(v, false);
    }
    void addEdge(int u, int v){
        graph[u].emplace_back(v);
    }
    void run(){
        for(int v = 0; v < vn; v++)
            if(dep[v] == 0) dfs(v);
    }
    int getSCCId(int v) { return scc[v]; }
};
