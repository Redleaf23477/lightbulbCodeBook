const int maxn = 500 + 3, INF = 0x3f3f3f3f;
int n, W[maxn][maxn];
int mat[maxn];
int Lx[maxn], Ly[maxn], slack[maxn];
bool S[maxn], T[maxn];

inline void tension(int &a, const int b) {
    if(b < a) a = b;
}

inline bool match(int u) {
    S[u] = true;
    for(int v = 0; v < n; ++v) {
        if(T[v]) continue;
        int t = Lx[u] + Ly[v] - W[u][v];
        if(!t) {
            T[v] = true;
            if(mat[v] == -1 || match(mat[v])) {
                mat[v] = u;
                return true;
            }
        }else tension(slack[v], t);
    }
    return false;
}

inline void update() {
    int d = INF;
    for(int i = 0; i < n; ++i)
        if(!T[i]) tension(d, slack[i]);
    for(int i = 0; i < n; ++i) {
        if(S[i]) Lx[i] -= d;
        if(T[i]) Ly[i] += d;
    }
}

inline void KM() {
    for(int i = 0; i < n; ++i) {
        Lx[i] = Ly[i] = 0; mat[i] = -1;
        for(int j = 0; j < n; ++j) Lx[i] = max(Lx[i], W[i][j]);
    }
    for(int i = 0; i < n; ++i) {
        fill(slack, slack + n, INF);
        while(true) {
            for(int j = 0; j < n; ++j) S[j] = T[j] = false;
            if(match(i)) break;
            else update();
        }
    }
}

