//二維陣列單點查詢區間加值
class St1d
{
private:
    ll st[4*N];

public:
    void build();
    void modify(int l, int r, int idx, int L, int R, ll v);
    ll query(int l, int r, int idx, int x);
    void down(int idx);
};

void St1d::build()
{
    memset(st, 0, sizeof(st));
}

void St1d::modify(int l, int r, int idx, int L, int R, ll v)
{
    if(r < L || R < l) return;
    if(L <= l && r <= R)
    {
        st[idx] += v;
        return;
    }
    assert(l != r);
    down(idx);
    int mid = (l+r)/2;
    modify(l, mid, idx*2, L, R, v);
    modify(mid+1, r, idx*2+1, L, R, v);
}

ll St1d::query(int l, int r, int idx, int x)
{
    if(x < l || r < x) return 0;
    if(l == x && r == x) return st[idx];
    down(idx);
    int mid = (l+r)/2;
    ll left = query(l, mid, idx*2, x);
    ll right = query(mid+1, r, idx*2+1, x);
    return left+right;
}

void St1d::down(int idx)
{
    st[idx*2] += st[idx], st[idx*2+1] += st[idx];
    st[idx] = 0;
}

////////////////////////

class St2d
{
private:
    St1d st[4*N];

public:
    void build(int il, int ir, int idx);
    void modify(int il, int ir, int jl, int jr, int idx, int iL, int iR, int jL, int jR, ll v);
    ll query(int il, int ir, int jl, int jr, int idx, int i, int j);
};

void St2d::build(int il, int ir, int idx)
{
    st[idx].build();
    if(il == ir) return;
    int mid = (il+ir)/2;
    build(il, mid, idx*2);
    build(mid+1, ir, idx*2+1);
}

void St2d::modify(int il, int ir, int jl, int jr, int idx, int iL, int iR, int jL, int jR, ll v)
{
    if(ir < iL || iR < il) return;
    if(iL <= il && ir <= iR)
    {
        st[idx].modify(jl, jr, 1, jL, jR, v); return;
    }
    int mid = (il+ir)/2;
    modify(il, mid, jl, jr, idx*2, iL, iR, jL, jR, v);
    modify(mid+1, ir, jl, jr, idx*2+1, iL, iR, jL, jR, v);
}

ll St2d::query(int il, int ir, int jl, int jr, int idx, int i, int j)
{
    ll tot = 0;
    if(i < il || ir < i) return 0;
    if(il <= i && i <= ir) tot += st[idx].query(jl, jr, 1, j);
    if(il == i && ir == i) return tot;
    int mid = (il+ir)/2;
    tot += query(il, mid, jl, jr, idx*2, i, j);
    tot += query(mid+1, ir, jl, jr, idx*2+1, i, j);
    return tot;
}
