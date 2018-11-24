double EPS = 1e-10;

double add(double a, double b)
{
    if(abs(a+b)<EPS*(abs(a)+abs(b)))return 0;
    else return a+b;
}

struct P//struct for 2d vector/point
{
    double x,y;
    P(){}
    P(double x, double y):x(x),y(y){}
    P operator+(P p){return P(add(x,p.x), add(y,p.y));}
    P operator-(P p){return P(add(x,-p.x), add(y,-p.y));}
    P operator*(double d){return P(x*d,y*d);}
    double dot(P p){return add( x*p.x, y*p.y );}
    double det(P p){return add( x*p.y, -y*p.x );}
};

//is point q on p1p2
bool on_seg(P p1, P p2, P q){return (p1-q).det(p2-q)==0&&(p1-q).dot(p2-q)<=0;}

P intersection(P p1, P p2, P q1, P q2)//p and q Must not be parallel
{return p1 + (p2-p1)*((q2-q1).det(q1-p1)/(q2-q1).det(p2-p1));}

bool par(P p1, P p2, P p3, P p4){return (p2-p1).det(p4-p3)==0;}

bool operator<(const P& lhs, const P& rhs)
{return (lhs.x==rhs.x)?lhs.y<rhs.y:lhs.x<rhs.x;}

bool operator==(const P& lhs, const P& rhs)
{return lhs.x==rhs.x&&lhs.y==rhs.y;}

double len(P vec)
{return sqrt(add(vec.x*vec.x, vec.y*vec.y));}

double dis(P p1, P p2)
{return len(p2-p1);}

struct seg
{
    seg(){}
    seg(P _p1, P _p2)
    {
        p[0]=_p1;
        p[1]=_p2;
        if(p[1]<p[0])swap(p[0],p[1]);
    }
    P p[2];
};

bool par(seg& lhs, seg& rhs)
{return par(lhs.p[0],lhs.p[1],rhs.p[0],rhs.p[1]);}

P intersection(seg& lhs, seg& rhs)//p and q Must not be parallel
{return intersection(lhs.p[0],lhs.p[1],rhs.p[0],rhs.p[1]);}

bool on_seg(seg& sg, P q)
{return on_seg(sg.p[0],sg.p[1],q);}

bool overlap(seg s1, seg s2)
{
    return par(s1,s2)&&
    ( on_seg(s1,s2.p[0])||on_seg(s1,s2.p[1])||
    on_seg(s2,s1.p[0])||on_seg(s2,s1.p[1]) );
}

bool is_intersect(seg s1, seg s2)
{
    if(par(s1,s2))return false;
    P p0 = intersection(s1,s2);
    return on_seg(s1,p0)&&on_seg(s2,p0);
}

//make sure the vec is not vertical
double interpolate(seg& vec, double X)
{
    double y0=vec.p[0].y,y1=vec.p[1].y,
    x0=vec.p[0].x,x1=vec.p[1].x;
    return y0+(y1-y0)*(X-x0)/(x1-x0);
}

//pts in clockwise order, p[N]=p[0]
bool in_poly(P* pol,int N,P pt)
{
    double X = pt.x,Y=pt.y;
    int pas=0;
    for(int i=0;i<N;i++)
    {
        if(pol[i].x==pol[i+1].x)continue;
        seg s0(pol[i],pol[i+1]);
        //up or down?
        double Y1 = interpolate(s0,X);
        if(Y1<Y-EPS)continue;
        double xl=min(pol[i].x,pol[i+1].x),xr=max(pol[i].x,pol[i+1].x);
        if(xl<X-EPS&&xr>=X-EPS)pas++;
    }
    return pas&1;
}

double dpseg(P p, P p1, P p2)//p to p1p2, p1!=p2
{
    P v=p2-p1, v1=p-p1, v2=p-p2;
    if( v.dot(v1) < EPS )return dis(p,p1);
    if( v.dot(v2) > EPS )return dis(p,p2);
    return fabs((p-p1).det(v))/len(v);
}

double dpseg(P p, seg s1)
{
    return dpseg(p,s1.p[0],s1.p[1]);
}

double dsegseg(P p1, P p2, P p3, P p4)
{
    if( is_intersect( seg(p1,p2), seg(p3,p4) ) )return 0;
    return min( min( dpseg(p1,p3,p4),dpseg(p2,p3,p4) ), min( dpseg(p3,p1,p2),dpseg(p4,p1,p2) ) );
}

double dsegseg(seg s1, seg s2)
{
    return dsegseg( s1.p[0],s1.p[1],s2.p[0],s2.p[1] );
}
