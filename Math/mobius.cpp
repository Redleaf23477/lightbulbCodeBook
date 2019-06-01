/* Mobius Function
 * m(x) = 0, x has repeated factors
 * m(x) = 1, x = 1
 * m(x) = (-1)^k, x is the product of k distinct primes
*/
const int M = 100005;
ll sp[M], mobius[M];
void sieve()
{
    for(ll i = 0; i < M; i++) sp[i] = i;
    for(ll i = 2; i*i < M; i++) if(sp[i] == i) 
    {
        for(ll j = i*i; j < M; j += i) 
            if(sp[j] == j) sp[j] = i;
    }
}
void makeMobius()
{
    for(ll i = 0; i < M; i++) mobius[i] = 1;
    mobius[0] = 0;
    for(ll i = 2; i < M; i++) if(sp[i] == i)
    {
        for(ll j = i; j < M; j += i) mobius[j] = -mobius[j];
        for(ll j = i*i; j < M; j += i*i) mobius[j] = 0;
    }
}
