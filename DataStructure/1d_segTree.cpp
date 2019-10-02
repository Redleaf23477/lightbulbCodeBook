void buildst(int l, int r, int idx)  //l, r是st的區間
{
    if(l == r){
        st[idx] = arr[l];
        return;
    }
    int mid = (l+r)/2;
    buildst(l, mid, idx*2);
    buildst(mid+1, r, idx*2+1);
    st[idx] = max(st[idx*2], st[idx*2+1]);
}

ll query(int l, int r, int idx, int L, int R)  //L,R是操作的區間
{
    if(r < L || R < l) return -INF;
    if(L <= l && r <= R) return st[idx];
    int mid = (l+r)/2;
    return max(query(l, mid, idx*2, L, R), query(mid+1, r, idx*2+1, L, R));
}

void modify(int l, int r, int idx, int x, int v)
{
    if(r < x || x < l) return;
    if(l == r){
        st[idx] += v; return;
    }
    int mid = (l+r)/2;
    modify(l, mid, idx*2, x, v);
    modify(mid+1, r, idx*2+1, x, v);
    st[idx] = max(st[idx*2], st[idx*2+1]);
}
