
struct edge{int to, cost;};
typedef pair<int, int> P; //first = min distance, second = v id
#define f first
#define s second
#define INF 2147483647

int V, E, S, F;
vector<edge> G[100];
int d[100];

void dijkstra()
{
    priority_queue<P, vector<P>, greater<P>> q;
    fill(d, d + V, INF);
    d[S] = 0;
    q.push(P(0, S));

    while(!q.empty())
    {
        P p = q.top(); q.pop();
        int v = p.s;
        if(d[v] < p.f) continue;
        for(int i = 0; i < G[v].size(); i++)
        {
            edge e = G[v][i];
            if(d[e.to] > d[v] + e.cost)
            {
                d[e.to] = d[v] + e.cost;
                q.push(P(d[e.to], e.to));
            }
        }
    }
}


