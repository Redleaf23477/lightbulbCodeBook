vector<Point> interCir(Point o1, double r1, Point o2, double r2)
{
	double d=sqrt((o1-o2).abs2());
	double c=(r1*r1 + d*d - r2*r2)/2.0/r1/d;
	double s=sqrt(1.0-c*c);
	Point v=(o2-o1)*r1/d;
	// case 0 intersections
	if(d>r1+r2||d<fabs(r1-r2)) return{};
	// case 1 intersection
	if(d-eps<=r1+r2&&r1+r2<=d+eps) return{o1+v};
	if(d-eps<=fabs(r1-r2)&&fabs(r1-r2)<=d+eps) return{o1-v};
	// case 2 intersections
	Point v_up=(Point){v.x*c-v.y*s,v.x*s+v.y*c};
	Point v_down=(Point){v.x*c+v.y*s,-v.x*s+v.y*c};
	return {o1+v_up,o1+v_down};
} // 求兩圓交點
