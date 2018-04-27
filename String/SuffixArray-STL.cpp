struct CMP
{
	int len,k,*Rank,a,b;
	inline bool operator()(int i, int j)
	{
		if(Rank[i]!=Rank[j])return Rank[i]<Rank[j];
		a=(i+=k)<len?Rank[i]:-1;
		b=(j+=k)<len?Rank[j]:-1;
		return a<b;
	}
};
void SA_build(int *SA, int *Rank, char *S){
	int tmp[MAX_N], len=strlen(S);
	for(int i=0;i<len;i++) SA[i]=i, Rank[i]=S[i];
	CMP cmp={len,1};
	while(cmp.k*=2)
	{
		cmp.Rank=Rank;
		sort(SA,SA+len,cmp);
		tmp[SA[0]]=0;
		for(int i=1;i<len;i++)
			tmp[SA[i]]=tmp[SA[i-1]]+cmp(SA[i-1],SA[i]);
		if(tmp[SA[len-1]]==len-1) break;
		for(int i=0;i<len;i++) Rank[i]=tmp[i];
	}
}
