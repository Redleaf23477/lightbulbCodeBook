const int N = 10000000;
bool isprime[N] = {true};
void prime_detect()
{
    for(int i = 2; i < sq; i++) 
        if(isprime[i]) 
            for(int j = i*i; j < N; j+=i) isprime[j] = false;
}
