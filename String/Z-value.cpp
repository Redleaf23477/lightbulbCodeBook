void Z_build(const char *S, int *Z){
	Z[0]=0;
	int b=0;
	for(int i=1;S[i];i++){
		if(Z[b]+b<i) Z[i]=0;
		else Z[i]=min(Z[b]+b-i,Z[i-b]);
		while(S[i+Z[i]]&&S[Z[i]]==S[i+Z[i]]) Z[i]++;
		if(Z[i]+i>Z[b]+b) b=i;
	}
}
