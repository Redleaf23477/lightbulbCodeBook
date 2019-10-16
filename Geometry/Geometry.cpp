const double PI=atan2(0.0,-1.0);
const double EPS=1.0/1000000.0;
struct point {
	double x, y;
	point(){}
	point(double _x, double _y):x(_x),y(_y){}
	point operator+ (point &a) {
		return point(x+a.x,y+a.y); }
	point operator- (point &a) {
		return point(x-a.x,y-a.y); }
	point operator* (double &a) {
		return point(x*a,y*a); }
	point operator/ (double &a) {
		return point(x/a,y/a); }
	double operator* (point &a) { // dot
		return x*a.x+y*a.y; }
	double operator^ (point &a) { // cross
		return x*a.y-y*a.x; }
	point normal(){ // 法向量
		return point(-y,x); }
	double abs2() { // 長度平方
		return x*x+y*y; }
	double rad(point &a) { // 兩向量弧度, (*this)->a
		return atan2((*this)^a,(*this)*a); }
};
struct line {
	point p1, p2;
	double a, b, c; // ax+by+c=0
	line(){}
	line(point x1, point x2):p1(x1),p2(x2){}
	void to_normal() { // point->ax+by+c=0
		a=p2.y-p1.y;
		b=p1.x-p2.x;
		c=p1.y*p2.x-p2.y*p1.x;
	}
	int dir(point &p) { // 點在有向直線的左(>0)中(=0)右(<0)
		double t=(p2-p1)^(p-p1);
		if(fabs(t)<=EPS) return 0;
		else return t>0?1:-1;
	}
	point project(point &p) { // 直線上的投影點
		point n=(p2-p1).normal();
		return p+n*((p1-p)*n)/n.abs2();
	}
	bool project_on(point &p) { // 投影點在線段上
		point t=project(p);
		return ((p2-t)^(t-p1))>=0;
	}
	bool point_on(point &p) { // 點在線段上
		return !dir(p)&&project_on(p);
	}
	double dis2(point &p, bool is_seg) { // 點到直線/線段長度平方
		if(!is_seg||project_on(p)) return (p-project(p)).abs2();
		return min((p1-p).abs2(),(p2-p).abs2());
	}
	point mirror(point &p) { // 鏡射
		point n=(p2-p1).normal();
		return p+n*((p1-p)*n)/n.abs2()*2.0;
	}
	bool equal(line &l) { // 直線相等
		return !dir(l.p1)&&!dir(l.p2);
	}
	bool cross_seg(line &l) { // 直線是否交線段
		return ((p2-p1)^(l.p1-p1))*((p2-p1)^(l.p2-p1))<=EPS;
	}
	bool parallel(line &l) {
		return fabs((p2-p1)^(l.p2-l.p1))<=EPS;
	}
	int is_intersect(line &l, bool is_seg) { // 相交(1)不相交(0)無限多(-1)
		int c1=dir(l.p1), c2=dir(l.p2);
		int c3=l.dir(p1), c4=l.dir(p2);
		if(!is_seg) return !parallel(l)?1:(c1==0?-1:0);
		if(c1==0&&c2==0) {
			if(l.project_on(p1)) return 2;
			if(l.project_on(p2)) return 3;
			return 0;
		} else if(c1*c2<=0&&c3*c4<=0) return 1;
		return 0;
	}
	point line_intersection(line &l) { // 直線相交點
		point x=p2-p1, y=l.p2-l.p1, s=l.p1-p1;
		int res=is_intersect(l,false);
		if(!res) assert(0);
		return p1+x*((s^y)/(x^y));
	}
	point seg_intersection(line &l) { // 線段相交點
		point x=p2-p1, y=l.p2-l.p1, s=l.p1-p1;
		int res=is_intersect(l,true);
		if(!res) assert(0);
		if(res==2) return p1;
		if(res==3) return p2;
		return p1+x*((s^y)/(x^y));
	}
};
struct polygon {
	vector<point> p; // 逆時針順序
	polygon(){}
	double area() { // 面積
		double ans=0;
		for(size_t i=p.size()-1,j=0;j<p.size();i=j++)
			ans+=(p[i]^p[j]);
		return ans/2;
	}
	point center_of_mass() { // 重心
		double cx=0, cy=0, w=0;
		for(size_t i=p.size()-1,j=0;j<p.size();i=j++) {
			double a=(p[i]^p[j]);
			cx+=(p[i].x+p[j].x)*a;
			cy+=(p[i].y+p[j].y)*a;
			w+=a;
		}
		return point(cx/3/w,cy/3/w);
	}
	int ahas(point &t) { // 點在簡單多邊形中，是(1)否(0)邊上(-1)
		bool c=0;
		for(size_t i=0,j=p.size()-1;i<p.size();j=i++)
			if(line(p[i],p[j]).point_on(t)) return -1;
			else if((p[i].y>t.y)!=(p[j].y>t.y)&&
			t.x<(p[j].x-p[i].x)*(t.y-p[i].y)/(p[j].y-p[i].y)+p[i].x)
				c=!c;
		return c;
	}
	int point_in_conver(point &x) { // 凸多邊形，同上
		int l=1, r=p.size()-2;
		while(l<=r) {
			int mid=(l+r)/2;
			double a1=(p[mid]-p[0])^(x-p[0]);
			double a2=(p[mid+1]-p[0])^(x-p[0]);
			if(a1>=0&&a2<=0) {
				double res=(p[mid+1]-p[mid])^(x-p[mid]);
				return res>0?1:(fabs(res)<=EPS?-1:0);
			} else if(a1<0) r=mid-1;
			else l=mid+1;
		}
		return 0;
	}
	vector<double> getA() { // 凸包邊對x軸的夾角
		vector<double> res;
		for(size_t i=0;i<p.sizez();i++)
			res.push_back((p[(i+1)%p.size()]-p[i]).getA());
		return res;
	}
	bool line_intersect(vector<double> &A, line &l) { // A=getA()
		int f1=upper_bound(A.begin(),A.end(),(l.p1-l.p2).getA())-A.begin();
		int f1=upper_bound(A.begin(),A.end(),(l.p2-l.p1).getA())-A.begin();
		return l.cross_seg(line(p[f1],p[f2]));
	}
	polygon cut(const line &l)const{//凸包對直線切割，得到直線l左側的凸包
		polygon ans;
		for(int n=p.size(),i=n-1,j=0;j<n;i=j++){
			if(l.dir(p[i])>=0){
				ans.p.push_back(p[i]); 
				if(l.dir(p[j])<0)
					ans.p.push_back(l.line_intersection(line(p[i],p[j])));
			}else if(l.dir(p[j])>0)
				ans.p.push_back(l.line_intersection(line(p[i],p[j])));
		}
		return ans;
	}
};
