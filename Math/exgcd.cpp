//維護a*x+b*y=gcd(a, b)
int extgcd(int a, int b, int &x, int &y)
{
	int gcd = a;
	if(b != 0) 
	{
		gcd = extgcd(b, a%b, y, x);
		y -= (a/b)*x;
	}
	else x = 1, y = 0;
	return gcd;
}

