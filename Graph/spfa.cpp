typedef pair<int, ll> P;
#define idx first
#define w second
int vn, en;
vector<P> graph[N];
ll dist[N];

bool spfa(){ // return true if neg cycle
    for(int i = 0; i < vn; i++) dist[i] = INF; dist[0] = 0;
    int cnt[N] = {0};
    bool inq[N] = {false};
    queue<int> q; q.push(0); inq[0] = true;
    while(!q.empty()){
        int s = q.front(); q.pop();
        inq[s] = false;
        for(auto e:graph[s]){
            if(dist[e.idx] > dist[s]+e.w){
                dist[e.idx] = dist[s]+e.w;
                if(++cnt[e.idx] >= vn) return true;
                if(!inq[e.idx]){
                    inq[e.idx] = true;
                    q.push(e.idx);
                }
            }
        }
    }
    return false;
}
