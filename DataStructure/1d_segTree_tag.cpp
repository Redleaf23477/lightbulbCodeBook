//線段樹懶人標記：一維陣列區間加值區間乘值區間查詢總和
struct Node //data = data*mul+add;
{
    ll data, mul, add;
};

ll getval(int l, int r, int idx){
    return (st[idx].data*st[idx].mul%MD+(r-l+1)*st[idx].add%MD)%MD;
}

void up(int l, int r, int idx){
    int mid = l+(r-l)/2;
    st[idx].data = (getval(l, mid, idx*2)+getval(mid+1, r, idx*2+1))%MD;
}

void down(int l, int r, int idx){
    st[idx].data = getval(l, r, idx);
    int lson = idx*2, rson = idx*2+1;
    if(l != r){
        st[lson].mul = st[lson].mul*st[idx].mul%MD;
        st[lson].add = (st[lson].add*st[idx].mul+st[idx].add)%MD;
        st[rson].mul = st[rson].mul*st[idx].mul%MD;
        st[rson].add = (st[rson].add*st[idx].mul+st[idx].add)%MD;
    }
    st[idx].mul = 1, st[idx].add = 0;
}

void buildst(int l, int r, int idx){
    st[idx].mul = 1, st[idx].add = 0;
    if(l == r){
        st[idx].data = arr[l];
        return;
    }
    int mid = l+(r-l)/2;
    buildst(l, mid, idx*2);
    buildst(mid+1, r, idx*2+1);
    up(l, r, idx);
}

void add(int l, int r, int idx, int L, int R, int v){ //操作L,R
    if(r < L || R < l) return;
    if(L <= l && r <= R){
        st[idx].add = (st[idx].add+v)%MD; 
        return;
    }
    down(l, r, idx);
    int mid = l+(r-l)/2;
    add(l, mid, idx*2, L, R, v);
    add(mid+1, r, idx*2+1, L, R, v);
    up(l, r, idx);
}

void mul(int l, int r, int idx, int L, int R, int v){
    if(r < L || R < l) return;
    if(L <= l && r <= R){
        st[idx].add = st[idx].add*v%MD;
        st[idx].mul = st[idx].mul*v%MD;
        return;
    }
    down(l, r, idx);
    int mid = l+(r-l)/2;
    mul(l, mid, idx*2, L, R, v);
    mul(mid+1, r, idx*2+1, L, R, v);
    up(l, r, idx);
}

ll query(int l, int r, int idx, int L, int R){
    if(r < L || R < l) return 0;
    if(L <= l && r <= R){
        return getval(l, r, idx);
    }
    down(l, r, idx);
    int mid = l+(r-l)/2;
    return (query(l, mid, idx*2, L, R)+query(mid+1, r, idx*2+1, L, R))%MD;
}
