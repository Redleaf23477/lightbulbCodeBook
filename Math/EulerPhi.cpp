//find in O(sqrt(N))

int euler_phi(int N)
{
    int res=N;
    for(int i=2;i*i<=N;i++)
    {
        if(N%i==0)
        {
            res=res/i*(i-1);
            for(;N%i==0;N/=i);
        }
    }
    if(N!=1)res=res/N*(N-1);//self=prime
    return res;
}

//tabulate in O(MAXN)

int euler[MAXN];

void euler_phi2()
{
    for(int i=0;i<MAXN;i++)euler[i]=i;
    for(int i=2;i<MAXN;i++)
    {
        if(euler[i]==i)
        {
            for(int j=i;j<MAXN;j+=i)
            {
                euler[j]=euler[j]/i*(i-1);
            }
        }
    }
}

