const int N = 10;   // 變數數量
bool adj[20][20];   // adjacency matrix
int visit[20];      // DFS visit record
int sat[20];        // 解
 
int not(int a) {return a<N ? a+N : a-N;}
 
// 另外一種方式
/*
int not(int a) {return a&1 ? a : a+1;}
int not(int a) {return a^1;}
*/
 
bool dfs_try(int i)
{
    if (visit[i] == 1 || sat[i] == 1) return true;
    if (visit[i] == 2 || sat[i] == 2) return false;
    visit[i] = 1;
    visit[not(i)] = 2;
    for (int j=0; j<N+N; ++j)
        if (adj[i][j] && !dfs_try(j))
            return false;
    return true;
}
 
void dfs_mark(int i)
{
    if (sat[i] == 1) return;
    sat[i] = 1;
    sat[not(i)] = 2;
    for (int j=0; j<N+N; ++j)
        if (adj[i][j])
            dfs_mark(j);
}
 
void two_satisfiability()
{
    // 一次輸入一個括號
    memset(adj, false, sizeof(adj));
    int a, b;
    while (cin >> a >> b)
    {
        map[not(a)][b] = true;
        map[not(b)][a] = true;
    }
 
    // 找出一組解
    for (int i=0; i<N; ++i)
    {
        memset(visit, 0, sizeof(visit));
        if (dfs_try(i)) {dfs_mark(i); continue;}
 
        memset(visit, 0, sizeof(visit));
        if (dfs_try(not(i))) {dfs_mark(not(i)); continue;}
 
        // 無解則立即結束。
        return;
    }
 
    // 印出一組解。
    for (int i=1; i<N; ++i)
        if (sat[i] == 1)
            cout << i;
        else /*if (sat[i] == 2)*/
            cout << "not" << i;
}
