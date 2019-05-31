ll solve(ll *a, ll *b, ll *m, int N)
{
	ll k = 0, h = 1, gcd, n, t, ar;
	for (ll i = 0; i < N; i++)
	{
		gcd = extgcd(a[i] * h, m[i], ar, t);
		t = (b[i] - a[i] * k) / gcd, n = abs(m[i] / gcd);
		if (t * gcd != b[i] - a[i] * k) return -1;
		t = ((ar * t) % n + n) % n;
		k += h * t, h *= n, k %= h;
	}
	return (k % h + h) % h;
}
// 解n組a*x=b%m, 回傳x.
// 回傳的是最小非負整數解. 無解回傳-1.
