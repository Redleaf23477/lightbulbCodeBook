struct edge{ int from, to, cost; };
#define INF 2147483647

edge es[100];

int d[100]; //min distance
int V, E, s, f;

bool bellman_ford()  // return true if there is negative loop
{
    for(int i = 0; i < V; i++) d[i] = INF;
    d[s] = 0;

    for(int i = 0; i < V; i++)
    {
        for(int j = 0; j < E; j++)
        {
            edge e = es[j];
            if(d[e.from] != INF && d[e.to] > d[e.from] + e.cost)
            {
                d[e.to] = d[e.from] + e.cost;
                if(i == V - 1) return true; //got neg loop
            }
            if(d[e.to] != INF && d[e.from] > d[e.to] + e.cost)
            {
                d[e.from] = d[e.to] + e.cost;
                if(i == V - 1) return true; //got neg loop
            }
        }
    }
    return false;
}
