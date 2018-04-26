void cal_subsz(int v, int p)
{
    ll s = 1;
    for(int i = 0; i < graph[v].size(); i++)
    {
        int c = graph[v][i].idx;
        if(c == p || iscentroid[c]) continue;
        cal_subsz(c, v);
        s += subsz[c];
    }
    subsz[v] = s;
}

Edge find_centroid(int v, int p, const ll sz)
{
    Edge cen(-1, INF);
    ll mxsz = -1;
    for(int i = 0; i < graph[v].size(); i++)
    {
        int c = graph[v][i].idx; 
        if(c == p || iscentroid[c]) continue;
        Edge res = find_centroid(c, v, sz);
        if(res.w < cen.w) cen = res;
        mxsz = max(mxsz, subsz[c]);
    }
    mxsz = max(mxsz, sz-subsz[v]);
    if(mxsz < cen.w) cen.idx = v, cen.w = mxsz;
    return cen;
}

void get_dist(int v, int p, ll w)
{
    dist.push_back(w);
    for(int i = 0; i < graph[v].size(); i++)
    {
        int c = graph[v][i].idx;
        if(c == p || iscentroid[c]) continue;
        get_dist(c, v, w+graph[v][i].w);
    }
}

ll cal_pair(int idx, ll w)
{
    dist.clear();
    get_dist(idx, -1, w);
    sort(dist.begin(), dist.end());
    ll sum = 0;
    for(int l = 0, r = dist.size()-1; l < r; )
    {
        if(dist[r]+dist[l] <= k) sum += r-l, l++;
        else r--;
    }
    return sum;
}

ll tree_dc(int v)
{
    ll sum = 0;
    // find centroid
    cal_subsz(v, -1);
    int centroid = find_centroid(v, -1, subsz[v]).idx;
    iscentroid[centroid] = true;
    // cal result
    sum += cal_pair(centroid, 0);
    // for ever subtree
    for(int i = 0; i < graph[centroid].size(); i++)
    {
        int c = graph[centroid][i].idx; ll w = graph[centroid][i].w;
        if(iscentroid[c]) continue;
        // cal res
        sum -= cal_pair(c, w);
        // dc
        sum += tree_dc(c);
    }
    return sum;
}
