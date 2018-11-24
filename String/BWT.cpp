// use with suffix array
int pivot;
// BWT array size must be double of the data size
inline void BWT(char *tmp, char *in, char *out, int *SA, int *Rank)
{
	int len=strlen(in);
	for(int i=0;i<len;i++) tmp[i]=tmp[i+len]=in[i];
	tmp[len*2]='\0';
	SA_build(SA,Rank,tmp);
	for(int i=0, j=0;i<2*len;i++)
	{
		if(SA[i]==len) pivot=j;
		if(SA[i]<len)
			out[j++]=in[(SA[i]+len-1)%len];
	}
	out[len]='\0';
}

inline void IBWT(char *in, char *out, int *tmp)
{
	int len=strlen(in);
	vector<int> idx[256];
	for(int i=0;i<len;i++)
		idx[in[i]].emplace_back(i);
	for(int i=0,k=0;i<256;i++)
		for(int j=0;j<(int)(idx[i].size());j++)
			tmp[k++]=idx[i][j];
	int p=pivot;
	for(int i=0;i<len;i++)
		out[i]=in[p=tmp[p]];
	out[len]='\0';
}
