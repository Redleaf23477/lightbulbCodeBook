int cost[100][100];
bool used[100];
int mincost[100];
int v, e;
#define INF 2147483647

int prim()
{
    for(int i = 0; i < v; i++)
    {
        mincost[i] = INF;
        used[i] = false;
    }
    mincost[0] = 0;
    int res = 0;

    while(true)
    {
        int x = -1;
        for(int u = 0; u < v; u++)
            if(!used[u] && (x == -1 || mincost[u] < mincost[x])) x = u;

        if(x == -1) break;
        used[x] = true;
        res += mincost[x];

        for(int u = 0; u < v; u++)
            mincost[u] = min(mincost[u], cost[x][u]);
    }
    return res;
}

void init()
{
    for(int i = 0; i < v; i++)
        for(int j = 0; j < v; j++)
            if(i == j) cost[i][j] = 0;
            else cost[i][j] = INF;
}

