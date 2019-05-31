const double PI = acos(-1.0);
struct Complex
{
	double x,y;
	Complex(){}
	Complex(double a):x(a),y(0){}
	Complex(double a, double b):x(a),y(b){}
	Complex operator+ (const Complex &a){ return Complex(x+a.x,y+a.y); }
	Complex operator- (const Complex &a){ return Complex(x-a.x,y-a.y); }
	Complex operator* (const Complex &a){ return Complex(x*a.x-y*a.y,x*a.y+y*a.x); }
};
inline vector<Complex> fft(vector<Complex> rtn, int Rev = 1)
{
	int fft_n = rtn.size();
	for(int i=0,j=0;i<fft_n;i++)
	{
		if(i>j) swap(rtn[i],rtn[j]);
		for(int k=(fft_n>>1);(j^=k)<k;k>>=1);
	}
	for(int i=2,m;i<=fft_n;i<<=1)
	{
		m = i>>1;
		for(int j=0;j<fft_n;j+=i)
		{
			for(int k=0;k<m;k++)
			{
				Complex y = rtn[j+k+m]*Complex(cos(2*PI/i*k), Rev*sin(2*PI/i*k));
				rtn[j+k+m] = rtn[j+k]-y;
				rtn[j+k] = rtn[j+k]+y;
			}
		}
	}
	for(int i=0;!~Rev&&i<fft_n;i++)
		rtn[i].x = rtn[i].x/fft_n;
	return rtn;
}
// Complex的x為實部, y為虛部.
// 把原多項式包成Complex的vector(poly), 並把項次拓展到2^i, 用fft(poly)即可得到轉換後的結果.
// Rev為1時為FFT, 為-1時為InvFFT.
