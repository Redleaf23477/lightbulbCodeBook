//build query in O(nlogn), query LCP(i,j) in O(1)
int dp_height[MAX_N][20];
void height_build(int *SA, int *Rank, char *S, int *Height)
{
	int len=strlen(S), k=0;
	for(int i=0;i<len;i++)
	{
		if(Rank[i]==0) continue;
		while(S[i+k] == S[SA[Rank[i]-1]+k]) k++;
		Height[Rank[i]]=k;
		if(k) k--;
	} Height[0]=0;
	for(int i=0;i<len;i++) dp_height[i][0]=Height[i];
	for(int i=0;i<len;i++) for(int j=1;i+(1<<j)<len;j++)
		dp_height[i][j]=min(dp_height[i][j-1], dp_height[i+(1<<(j-1))][j-1]);
}
int height_query(int x, int y)
{
	int k=0;
	while((1<<(k+1))<=y-x) k++;
	return min(dp_height[x+1][k], dp_height[y-(1<<k)+1][k]);
}
