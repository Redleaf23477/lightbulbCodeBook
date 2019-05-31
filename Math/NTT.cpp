typedef long long ll;

const ll P = (479<<21)+1;
const ll G = 3;
inline ll fpw(ll x, ll y, ll m)
{
	ll rtn = 1;
	for(x=(x>=m?x%m:x);y;y>>=1)
	{
		if(y&1) rtn = rtn*x%m;
		x = x*x%m;
	}
	return rtn;
}
inline vector<ll> ntt(vector<ll> rtn, int Rev = 1)
{
	int ntt_n = rtn.size();
	for(int i=0,j=0;i<ntt_n;i++)
	{
		if(i>j) swap(rtn[i],rtn[j]);
		for(int k=(ntt_n>>1);(j^=k)<k;k>>=1);
	}
	for(int i=2,m=1;i<=ntt_n;i<<=1,m++)
	{
		ll w = 1, wn = fpw(G,(P-1)>>m,P), u, t;
		int mh = i>>1;
		for(int j=0;j<mh;j++)
		{
			for(int k=j;k<ntt_n;k+=i)
			{
				u = rtn[k], t = w*rtn[k+mh]%P;
				rtn[k] = (u+t)%P;
				rtn[k+mh] = (u-t+P)%P;
			}
			w = w*wn%P;
		}
	}
	if(!~Rev)
	{
		for(int i=1;i<ntt_n/2;i++) swap(rtn[i],rtn[ntt_n-i]);
		ll Revn = fpw(ntt_n,P-2,P);
		for(int i=0;i<ntt_n;i++) rtn[i] = rtn[i]*Revn%P;
	}
	return rtn;
}
// 把原多項式包成long long的vector(poly), 並把項次拓展到2^i.
// 用ntt(poly)即可得到轉換後的結果.
// Rev為1時為NTT, 為-1時為InvNTT.
