void failure_build(const char *p, int *fail)
{
	for(int i=1, j=fail[0]=-1; p[i]; i++)
	{
		while(j>=0&&p[j+1]!=p[i]) j=fail[j];
		if(p[j+1]==p[i]) j++;
		fail[i]=j;
	}
}
int KMP(const char *T, const char *P, int *fail)
{
	failure_build(P, fail);
	for(int i=0, j=-1; T[i]; i++)
	{
		while(j>=0&&P[j+1]!=T[i]) j=fail[j];
		if(P[j+1]==T[i]) j++;
		if(!P[j+1]) return i-j;
	}
	return -1;
}

//使用方法: KMP(主字串, 待匹配字串, failure array)
//回傳: 第一個完全匹配的位置
