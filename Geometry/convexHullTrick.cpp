// usage ( for example )
// dp[i] = min(dp[j] - 2*a[i]*a[j] + a[j]^2) + m + a[i]^2
// insert into hull : 
//    a         x   +        b
// (-2*a[j]) (a[i]) + (dp[j]+a[j]^2)
// get dp[i] : 
// dp[i] = hull(a[i]) + m + a[i]^2

template<typename Ty = long long int>
class Linear{
private:
    Ty a, b;
public:
    Linear(Ty a, Ty b):a(a), b(b) {}
    Ty operator()(Ty x) { return a*x+b; }
    // get x of intersection of two lines (fraction)
    tuple<Ty, Ty> inter(Linear &that){
        ll up = that.b-this->b;
        ll down = this->a-that.a;
        if(down < 0) up *= -1, down *= -1;
        return make_tuple(up, down);
    }
};

template<typename Ty = long long int>
class ConvexHull{
private:
    using L = Linear<Ty>;
    vector<L> hull;
public:
    void push_back(L h){
        while(hull.size() >= 2){
            auto &f = hull.end()[-2];
            auto &g = hull.end()[-1];  // back
            // x of inter(h,f) <= x of inter(f,g)
            Ty a, b, c, d;
            tie(a, b) = h.inter(f);
            tie(c, d) = f.inter(g);
            if(a*d <= b*c) hull.pop_back();
            else break;
        }
        hull.push_back(h);
    }
    Ty operator() (Ty x){
        static int idx = 0;
        if(idx >= hull.size()) 
            idx = max(0, (int)hull.size()-2);
        while(idx+1 < hull.size())
        {
            if(hull[idx+1](x) <= hull[idx](x)) idx++;
            else break;
        }
        return hull[idx](x);
    }
};
