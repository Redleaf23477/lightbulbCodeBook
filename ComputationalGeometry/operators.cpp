typedef std::pair<double,double> Pt;
#define X first
#define Y second
const double eps = 1e-6;
Pt point( double x , double y ){
    return make_pair( x , y );
}
Pt operator+( const Pt& p1 , const Pt& p2 ){
  return Pt( p1.X + p2.X , p1.Y + p2.Y );
}
Pt operator-( const Pt& p1 , const Pt& p2 ){
  return Pt( p1.X - p2.X , p1.Y - p2.Y );
}
double operator*( const Pt& p1 , const Pt& p2 ){
  return p1.X * p2.X + p1.Y * p2.Y;
}
double operator^( const Pt& p1 , const Pt& p2 ){
  return p1.X * p2.Y - p1.Y * p2.X;
}
Pt operator*( const Pt& p1 , const double& k ){
  return Pt( p1.X * k , p1.Y * k );
}
Pt operator/( const Pt& p1 , const double& k ){
  return Pt( p1.X / k , p1.Y / k );
}
bool equal( const double& a , const double& b ){
  return b - eps < a && a < b + eps; 
}
bool less( const double& a , const double& b ){
  return a < b - eps;
}
bool lessOrEqual( const double& a , const double& b ){
  return a < b + eps;
}
double abs( const Pt& p1 ){
  return sqrt( p1 * p1 );
}
double area(){
	double sum = 0;
	for(int i = 0; i < n; i++) sum += 0.5*p[i]^[i+1];
	return sum;
}
Pt o;
D angle( const Pt& x ){
  return atan2( x.Y , x.X );
}
bool cmp_angle( Pt a , Pt b ){
  return angle( a - o ) < angle( b - o );
}
bool cmp_cross( Pt a , Pt b ){
  return ( a - o ) ^ ( b - o ) > 0;
}