const double eps = 5e-8;
struct Point{
	double x,y;
	Point(){}
	Point(double x,double y):x(x),y(y){}
	Point operator+(Point b)const{
		return Point(x+b.x,y+b.y); 
	}
	Point operator-(Point b)const{
		return Point(x-b.x,y-b.y); 
	}
	Point operator*(double b)const{
		return Point(x*b,y*b); 
	}
	Point operator/(double b)const{
		return Point(x/b,y/b); 
	}
	bool operator==(Point b)const{
		return (fabs(x-b.x)<=eps&&fabs(y-b.y)<=eps);
	}
	double dot(Point b)const{
		return x*b.x+y*b.y; 
	}
	double cross(Point b)const{
		return x*b.y-y*b.x; 
	}
	Point normal()const{  
		return Point(-y,x); 
	} // �D�k�V�q
	double abs2()const{
		return dot(*this); 
	} // �V�q���ת�����
	double rad(const Point b)const{ 
		return fabs(atan2(fabs(cross(b)),dot(b))); 
	} // ��V�q������
};
