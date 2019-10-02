#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;
typedef pair<int, ll> P;
#define idx first
#define w second

const int N = 10004;
const ll INF = (1ll << 60);

int vn;
ll k;
vector<P> graph[N];
vector<int> dist;
ll subtreeSz[N];
bool isCentroid[N];

void init(){
    for(int i = 1; i <= vn; i++) 
        graph[i].clear(), isCentroid[i] = false;
}

void buildTree(){
    for(int i = 1; i < vn; i++){
        int u, v, l; scanf("%d %d %d", &u, &v, &l);
        graph[u].push_back(P(v, l));
        graph[v].push_back(P(u, l));
    }
}

ll calSubsz(int v, int p){
    subtreeSz[v] = 1;
    for(auto c:graph[v]){
        if(isCentroid[c.idx] || c.idx == p) continue;
        subtreeSz[v] += calSubsz(c.idx, v);
    }
    return subtreeSz[v];
}


P getCentroid(int v, int p, ll subsz){
    P cen(-1, INF);
    ll mxsonSz = -1;
    for(auto c:graph[v]){
        if(c.idx == p || isCentroid[c.idx]) continue;
        P res = getCentroid(c.idx, v, subsz);
        if(res.w < cen.w) cen = res;
        mxsonSz = max(mxsonSz, subtreeSz[c.idx]); 
    }
    mxsonSz = max(mxsonSz, subsz-subtreeSz[v]);
    if(mxsonSz < cen.w) cen = P(v, mxsonSz);
    return cen;
}

void getDist(int v, int p, ll w){
    if(w > k) return;
    dist.push_back(w);
    for(auto c:graph[v]){
        if(c.idx == p || isCentroid[c.idx]) continue;
        getDist(c.idx, v, w+c.w);
    }
}

ll calValidPair(int idx, ll w){
    dist.clear();
    getDist(idx, -1, w);
    sort(dist.begin(), dist.end());
    ll sum = 0;
    for(int l = 0, r = dist.size()-1; l < r; ){
        if(dist[r]+dist[l] <= k) sum += r-l, l++;
        else r--;
    }
    return sum;
}

ll treedc(int v){
    ll sum = 0;
    // find centroid
    calSubsz(v, v);
    int cen = getCentroid(v, v, subtreeSz[v]).idx;
    isCentroid[cen] = true;
    
    sum += calValidPair(cen, 0);
    for(auto c:graph[cen])
    {
        if(isCentroid[c.idx]) continue;
        sum -= calValidPair(c.idx, c.w);
        sum += treedc(c.idx);
    }
    return sum;
}

int main(){
    while(scanf("%d %lld", &vn, &k) && vn && k)
    {
        init();
        buildTree();
        printf("%lld\n", treedc(1));
    }
    return 0;
}
