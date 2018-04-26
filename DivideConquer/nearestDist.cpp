bool cmp_y(P &a, P &b)  // y increasing
{
    return a.y < b.y;
}

bool cmp_x(P &a, P &b) // x increasing
{
    return a.x < b.x;
}

void init()
{
    sort(arr, arr+n, cmp_y);
}

double nearestDist(int l, int r)
{
    if(l == r) return (double)INT_MAX;
    int mid = (l+r)/2;
    double d = min(dc(l, mid), dc(mid+1, r));
    sort(arr+l, arr+r+1, cmp_x);
    double center = arr[mid].x;
    vector<P> cen;
    for(int i = l; i <= r; i++)
    {
        if(fabs(arr[i].x-center) >= d) continue;
        for(auto p:cen)
        {
            double dx = fabs(arr[i].x-p.x), dy = fabs(arr[i].y-p.y);
            if(dy < d)
            {
                d = min(d, sqrt(dx*dx+dy*dy));
            }
        }
        cen.push_back(arr[i]);
    }
    return d;
}
