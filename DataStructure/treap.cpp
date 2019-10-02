struct Treap
{
    int pri, sz;
    int rev;
    ll data, sum;   // tag: make-same
    Treap *lchild, *rchild;
    Treap(ll d):pri(rand()), sz(1), rev(0), data(d), sum(d), lchild(NULL), rchild(NULL)
    {
    }
    inline void up();
    inline void down();
}; 

inline int size(Treap *t) { return t? t->sz:0; }
inline ll get_data(Treap *t) { return t? t->data:0; }
inline ll get_sum(Treap *t) { return t? t->sum:0; }

inline void Treap::up(){
    if(lchild) lchild->down();
    if(rchild) rchild->down();
    sz = 1+size(lchild)+size(rchild);
    sum = get_sum(lchild) + data + get_sum(rchild);
}

inline void Treap::down(){
    if(rev){
        swap(mxpre, mxpost);
        swap(lchild, rchild);
        if(lchild) lchild->rev ^= 1;
        if(rchild) rchild->rev ^= 1;
        rev ^= 1;
    }
}

Treap *merge(Treap *a, Treap *b){
    if(!a || !b) return (a? a:b);
    if(a->pri < b->pri){
        a->down();
        a->rchild = merge(a->rchild, b);
        a->up();
        return a;
    }
    else{
        b->down();
        b->lchild = merge(a, b->lchild);
        b->up();
        return b;
    }
}

void split(Treap *o, Treap *&a, Treap *&b, int k){
    if(!o) a = b = NULL;
    else{
        o->down();
        if(k >= size(o->lchild)+1){
            a = o;
            split(o->rchild, a->rchild, b, k-size(o->lchild)-1);
        }
        else {
            b = o;
            split(o->lchild, a, b->lchild, k);
        }
        o->up();
    }
}
