int ori( const Pt& o , const Pt& a , const Pt& b ){
  double cross = ( a - o ) ^ ( b - o );
  if( fabs( cross ) < eps ) return 0;
  return cross > 0 ? 1 : -1;
}
bool intersect(const Pt& p1, const Pt& p2, const Pt& p3, const Pt& p4){ //線段p1p2, p3p4
	return ori(p1, p2, p3)^ori(p1, p2, p4) < 0;
}
int parallel(const Pt& p1, const Pt& p2, const Pt& p3, const Pt& p4){
	return (p2-p1)^(p4-p3) == 0;
}
bool Collinear(const Pt& p1, const Pt& p2, const Pt& p3, const Pt& p4){ //共線
	ori(p1, p2, p3) == 0;
}