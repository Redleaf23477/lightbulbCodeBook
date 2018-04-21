// 解線性模方程組(最小非負整數解)
const int N;  //N個方程
ll A[N], B[N], M[N];  // A * X = B (%M)
ll solve() //解X, return INF if no solution 
{
   ll k = 0, h = 1;
   for(ll i = 0; i < N; i++)
   {
      ll a = A[i]*h, b = B[i]-A[i]*k, m = M[i], ar;
      ll d = exgcd(a, ar=1, m); 
      if(b%d != 0) return INF;
      ll n = abs(m/d);
      ll t = ar*b/d; t%=n; t+=n; t%=n;

      k += h*t, h *= n; k%=h; //維護解是正的
   }
   int ret = (k%h+h)%h;
   return ret;
}

