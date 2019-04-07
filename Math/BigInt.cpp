#define MAX_N 100
#define MAX 100000
#define MAX_LOG 5
class BigInt
{
	public:
		long long m[MAX_N];
		int l;
		long long operator [](int i) const { return m[i]; }
		long long &operator [](int i) { return m[i]; }
		BigInt(){ l=1, m[0]=0; }
		BigInt(int x){ (*this)=x; }
		BigInt(const char *s){ (*this)=s; }
		BigInt operator =(int x)
		{
			for(l=1, m[l-1]=x%MAX, x/=MAX; x; m[l++]=x%MAX, x/=MAX);
			return *this;
		}
		BigInt operator =(const char *s)
		{
			int i, j, len;
			for(len=0; s[len]>='0' && s[len]<='9'; len++);
			for(l=(len+MAX_LOG-1)/MAX_LOG, i=0; i<l; i++)
				for(m[i]=0, j=0; j<MAX_LOG; j++)
					if(len-i*MAX_LOG-MAX_LOG+j>=0)
						m[i]=m[i]*10+s[len-i*MAX_LOG-MAX_LOG+j]-'0';
			return *this;
		}
		bool scan()
		{
			char s[MAX_N*MAX_LOG+10];
			if(scanf("%s", s)==EOF) return 0;
			else { *this=s; return 1; }
		}
		void print()
		{
			int i;
			char s[8];
			for(sprintf(s, "%%0%dlld", MAX_LOG), printf("%lld", m[l-1]), i=l-2; i>=0; printf(s, m[i]), i--);
		}
};
bool operator <(const BigInt &x, const BigInt &y)
{
	int i;
	if(x.l!=y.l) return x.l<y.l;
	for(i=x.l-1; i>=0 && x[i]==y[i]; i--);
	return i>=0 && x[i]<y[i];
}
bool operator ==(const BigInt &x, const BigInt &y)
{
	int i;
	if(x.l!=y.l) return 0;
	for(i=x.l-1; i>=0 && x[i]==y[i]; i--);
	return i<0;
}
BigInt operator +(BigInt x, const BigInt &y)
{
	int i;
	long long h;
	for(h=0, i=0; i<x.l || i<y.l || h; i++)
	{
		h+=(i<x.l)*x[i]+(i<y.l)*y[i];
		x[i]=h%MAX;
		h/=MAX;
	}
	x.l=i;
	return x;
}
BigInt operator -(BigInt x, const BigInt &y)
{
	int i;
	long long h;
	for(h=0, i=0; i<x.l; i++)
	{
		h+=x[i]-(i<y.l)*y[i]+MAX;
		x[i]=h%MAX;
		h/=MAX;
		h--;
	}
	for(; x.l>1 && !x[x.l-1]; x.l--);
	return x;
}
BigInt operator *(BigInt x, int y)
{
	int i;
	long long h;
	for(h=0, i=0; i<x.l || h; i++)
	{
		h+=(i<x.l)*x[i]*y;
		x[i]=h%MAX;
		h/=MAX;
	}
	for(x.l=i; x.l>1 && !x[x.l-1]; x.l--);
	return x;
}
BigInt operator /(BigInt x, int y)
{
	int i;
	long long h;
	for(h=0, i=x.l-1; i>=0; i--)
	{
		h=h*MAX+x[i];
		x[i]=h/y;
		h%=y;
	}
	for(; x.l>1 && !x[x.l-1]; x.l--);
	return x;
}
int operator %(BigInt x, int y)
{
	int i;
	long long h;
	for(h=0, i=x.l-1; i>=0; i--)
	{
		h=h*MAX+x[i];
		h%=y;
	}
	return h;
}
long long fl(double x) { return x<0?x-0.5:x+0.5; }
BigInt operator *(BigInt x, BigInt y)
{
	int i, N;
	long long t;
	vector<Complex> a, b;
	for(i=0; i<x.l; i++) a.emplace_back(x[i]);
	for(i=0; i<y.l; i++) b.emplace_back(y[i]);
	for(N=1; N<x.l+y.l; N<<=1);
	while(N!=(int)(a.size())) a.emplace_back(0);
	while(N!=(int)(b.size())) b.emplace_back(0);
	a=fft(a), b=fft(b);
	for(i=0; i<N; i++) a[i]=a[i]*b[i];
	a=fft(a,-1);
	for(i=0, t=0, x.l=0; i<N; i++)
	{
		t+=fl(a[i].x);
		x[x.l++]=t%MAX;
		t/=MAX;
	} x[x.l++]=t;
	for(; x.l>1 && !x[x.l-1]; x.l--);
	return x;
}
BigInt operator /(BigInt x, BigInt y)
{
	int i;
	BigInt h;
	if(y.l==1) return x/y[0];
	for(h=0, i=x.l-1; i>=0; i--)
	{
		h=h*MAX+x[i];
		if(h.l>y.l) x[i]=(h[h.l-1]*MAX*MAX+h[h.l-2]*MAX+h[h.l-3]);
		if(h.l==y.l) x[i]=(h[h.l-1]*MAX+h[h.l-2]);
		x[i]/=(y[y.l-1]*MAX+y[y.l-2]);
		for(; x[i] && h<y*x[i]; x[i]--);
		h=h-y*x[i];
	}
	for(; x.l>1 && !x[x.l-1]; x.l--);
	return x;
}
BigInt operator %(BigInt x, BigInt y)
{
	int i;
	BigInt h;
	if(y.l==1) return h=x%y[0];
	for(h=0, i=x.l-1; i>=0; i--)
	{
		h=h*MAX+x[i];
		if(h.l>y.l) x[i]=(h[h.l-1]*MAX*MAX+h[h.l-2]*MAX+h[h.l-3]);
		if(h.l==y.l) x[i]=(h[h.l-1]*MAX+h[h.l-2]);
		x[i]/=(y[y.l-1]*MAX+y[y.l-2]);
		for(; x[i] && h<y*x[i]; x[i]--);
		h=h-y*x[i];
	}
	return h;
}
