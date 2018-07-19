bool cmp_y(P a, P b)
{
    return a.y < b.y;
}

bool cmp_x(P a, P b)
{
    return a.x < b.x;
}

double dc(P *arr, int n)
{
    if(n == 1) return INF;
    int mid = n/2;
    double cx = arr[mid].x;
    double dist = min( dc(arr, mid), dc(arr+mid, n-mid) );
    inplace_merge(arr, arr+mid, arr+n, cmp_y);
    static vector<P> brr; brr.clear();
    for(int i = 0; i < n; i++)
    {
        if(fabs(arr[i].x)-cx >= dist) continue;
        for(int j = brr.size()-1; j >= 0; j--)
        {
            double dx = brr[j].x-arr[i].x;
            double dy = brr[j].y-arr[i].y;
            if(fabs(dy) >= dist) break;
            dist = min(dist, sqrt(dx*dx+dy*dy));
        }
        brr.push_back(arr[i]);
    }
    return dist;
}

double nearestDist(P *arr, int n)
{
    sort(arr, arr+n, cmp_x);
    return dc(arr, n);
}
