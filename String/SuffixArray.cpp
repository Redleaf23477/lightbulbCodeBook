void SA_radix_sort(int *s, int *e, int *Rank, int rankcnt)
{
	int box[MAX_N], tmp[MAX_N], len=e-s;
	memset(box,0,sizeof(int)*rankcnt);
	for(int i=0;i<len;i++) box[Rank[i]]++;
	for(int i=1;i<rankcnt;i++) box[i]=box[i]+box[i-1];
	for(int i=len-1;i>=0;i--) tmp[--box[Rank[s[i]]]]=s[i];
	for(int i=0;i<len;i++) s[i]=tmp[i];
}
#define equal(a,b,c) c[a]!=c[b]||a+k>=len||c[a+k]!=c[b+k]
void SA_build(int *SA, int *Rank, char *S)
{
	int ranktmp[MAX_N], len=strlen(S), rankcnt='z'+1;
	for(int i=0;i<len;i++) Rank[i]=S[i];
	for(int k=1;rankcnt!=len;k*=2)
	{
		for(int i=0;i<len;i++) SA[i]=(i+len-k)%len;
		SA_radix_sort(SA+k, SA+len, Rank+k, rankcnt);
		SA_radix_sort(SA, SA+len, Rank, rankcnt);
		ranktmp[SA[0]]=0, rankcnt=0;
		for(int i=1;i<len;i++)
			ranktmp[SA[i]]=rankcnt+=equal(SA[i-1], SA[i], Rank);
		rankcnt++;
		for(int i=0;i<len;i++) Rank[i]=ranktmp[i];
	}
}
#undef equal
