struct Treap {
    int pri, sz;
    int rev;
    ll data, tag;   // tag: make-same
    Treap *l, *r;
    Treap(ll d):pri(rand()), sz(1), rev(0), data(d), tag(INF), l(NULL), r(NULL) {}
    inline void up();
    inline void down();
}; 

int size(Treap *t) { return t? t->sz:0; }
ll get_data(Treap *t) { return t? t->data:0; }

void Treap::up() {
    if(l) l->down();
    if(r) r->down();
    sz = 1+size(l)+size(r);
}
void Treap::down() {
    if(tag != INF) {
        data = tag;
        if(l) l->tag = tag;
        if(r) r->tag = tag;
        tag = INF;
    }
    if(rev) {
        swap(l, r);
        if(l) l->rev ^= 1;
        if(r) r->rev ^= 1;
        rev ^= 1;
    }
}
void freeTreap(Treap *t) {
    if(!t) return;
    if(t->l) freeTreap(t->l);
    if(t->r) freeTreap(t->r);
    delete t;
}
Treap *merge(Treap *a, Treap *b) {
    if(!a || !b) return (a? a:b);
    if(a->pri < b->pri) {
        a->down();
        a->r = merge(a->r, b);
        a->up();
        return a;
    } else {
        b->down();
        b->l = merge(a, b->l);
        b->up();
        return b;
    }
}
void split(Treap *o, Treap *&a, Treap *&b, int k) {
    if(!o) a = b = NULL;
    else {
        o->down();
        if(k >= size(o->l)+1) {
            a = o;
            split(o->r, a->r, b, k-size(o->l)-1);
        } else {
            b = o;
            split(o->l, a, b->l, k);
        }
        o->up();
    }
}

Treap* buildTreap(vector<int> &arr) {
    srand(7122+time(NULL));
    Treap *tp = NULL;
    for(auto x : arr)
        tp = merge(tp, new Treap(x));
    return tp;
}
void ins(Treap *&tp, int pos, int x) {
    Treap *a, *b;
    split(tp, a, b, pos);
    tp = merge(a, merge(new Treap(x), b));
}
void del(Treap *&tp, int pos, int k) {
    Treap *a, *b, *c;
    split(tp, a, b, pos-1);
    split(b, b, c, k);
    freeTreap(b);
    tp = merge(a, c);
}
void makeSame(Treap *tp, int pos, int k, int val) {
    Treap *a, *b, *c;
    split(tp, a, b, pos-1);
    split(b, b, c, k);
    b->tag = val;
    tp = merge(a, merge(b, c));
}
void rev(Treap *&tp, int pos, int k) {
    Treap *a, *b, *c;
    split(tp, a, b, pos-1);
    split(b, b, c, k);
    b->rev ^= 1;
    tp = merge(a, merge(b, c));
}