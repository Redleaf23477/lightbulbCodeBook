struct ConvexHull {
    vector<Point> h; // hull
    static bool cmp(const Point &lhs, const Point &rhs) {
        if(lhs.x == rhs.x) return lhs.y < rhs.y;
        else return lhs.x < rhs.x;
    }
    // p : points, h : return hull
    void buildHull(vector<Point> &p) {
        int n = p.size(), m = 0;
        sort(p.begin(), p.end(), cmp);
        h.resize(n+1);
		for(int i = 0; i < n; ++i){
			while(m>=2&&(h[m-1]-h[m-2]).cross(p[i]-h[m-2])<=0)--m;
			h[m++]=p[i];
		}
		for(int i = n-2, t = m+1; i >= 0; --i) {
			while(m>=t&&(h[m-1]-h[m-2]).cross(p[i]-h[m-2])<=0)--m;
			h[m++]=p[i];
		}
		if(h.size()>1)--m; 
		h.resize(m);
    }
};
