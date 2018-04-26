struct edge { int u, v, cost; };

bool comp(const edge& e1, const edge& e2)
{
    return e1.cost < e2.cost;
}

int kruskal()
{
    sort(es, es + e, comp);
    dset s(v);
    int res = 0;
    for(int i = 0; i < e; i++)
    {
        edge E = es[i];
        if(s.Find(E.u) != s.Find(E.v))
        {
            s.Union(E.u, E.v);
            res += E.cost;
        }
    }
    return res;
}
