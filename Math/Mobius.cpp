/* Mobius Function
 * u(x) = 1, x = 1
 * u(x) = 0, x has repeated factors
 * u(x) = (-1)^k, x = product of k distinct primes
 * ep(x) = [x==1] = u * 1 = sum(u(d)) for all d|x
 */
const int MAX_N = 1e5+5;
bool np[MAX_N];
int mo[MAX_N], p[MAX_N], pSZ;
void getMobius() {
	mo[1] = 1;
	for(int i = 2; i <= MAX_N; i++) {
		if(!np[i]) p[pSZ++] = i, mo[i] = -1;
		for(int j = 0; j < pSZ && p[j] <= MAX_N/i; j++) {
			np[i*p[j]] = 1;
			if(i%p[j] == 0) {
				mo[i*p[j]] = 0;
				break;
			} mo[i*p[j]] = -mo[i];
		}
	}
}
