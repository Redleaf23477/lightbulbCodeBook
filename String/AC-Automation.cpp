#define SZ 25000
int nx[SZ][26], spt;
int fl[SZ], efl[SZ], ed[SZ];
int newnode(){
	for(int i=0;i<26;i++) nx[spt][i]=0;
	ed[spt]=0;
	return spt++;
}
int add(char *s, int sptnow){
	for(int i=0;s[i];i++){
		int tmp=s[i]-'a';
		if(nx[sptnow][tmp]==0) nx[sptnow][tmp]=newnode();
		sptnow=nx[sptnow][tmp];
	}
	ed[sptnow]=1;
	return sptnow;
}
int bfsq[SZ], qs, qe;
void make_fl(int root){
	fl[root]=efl[root]=qs=qe=0;
	bfsq[qe++]=root;
	while(qs!=qe){
		int p=bfsq[qs++];
		for(int i=0;i<26;i++){
			int t=nx[p][i];
			if(t==0) continue;
			int tmp=fl[p];
			for(;tmp&&nx[tmp][i]==0;tmp=fl[tmp]);
			fl[t]=tmp?nx[tmp][i]:root;
			efl[t]=ed[fl[t]]?fl[t]:efl[fl[t]];
			bfsq[qe++]=t;
		}
	}
}
