#include<stdio.h>
#include<string.h>
const int N=1500;
const double inf=0x3fffffff;
const double eps=1e-8;
int gap[N],dis[N],start,end,ans,sum,head[N],num,dep[N],n,m;
bool vis[N];
struct edge
{
	int st,ed,next;
	double flow;
}e[80*N];
struct node
{
	int x,y;
}P[1100];
void addedge(int x,int y,double w)
{
	e[num].st=x;e[num].ed=y;e[num].flow=w;e[num].next=head[x];head[x]=num++;
	e[num].st=y;e[num].ed=x;e[num].flow=0;e[num].next=head[y];head[y]=num++;
}
void makemap(double g)
{
	int i;
	memset(head,-1,sizeof(head));
	num=0;
	for(i=1;i<=n;i++)
		addedge(i,end,g);
	for(i=0;i<m;i++)
	{
		addedge(n+i+1,P[i].y,inf);
		addedge(n+i+1,P[i].x,inf);
		addedge(start,n+i+1,1.0);
	}
}
double dfs(int u,double minflow)  
{  
    if(u==end)return minflow;  
    int i,v;  
    double f,flow=0.0;  
    for(i=head[u];i!=-1;i=e[i].next)  
    {  
        v=e[i].ed;  
        if(e[i].flow>0)  
        {  
            if(dis[v]+1==dis[u])  
            {  
                f=dfs(v,e[i].flow>minflow-flow?minflow-flow:e[i].flow);  
                flow+=f;  
                e[i].flow-=f;  
                e[i^1].flow+=f;  
                if(minflow-flow<=1e-8)return flow;    
                if(dis[start]>=ans)return flow;    
            }  
        }  
    }  
    if(--gap[dis[u]]==0)  
        dis[start]=ans;  
    dis[u]++;  
    gap[dis[u]]++;  
    return flow;  
}  
double isap()  
{  
    double maxflow=0.0;  
    memset(gap,0,sizeof(gap));  
    memset(dis,0,sizeof(dis));  
    gap[0]=ans;  
    while(dis[start]<ans)  
        maxflow+=dfs(start,inf);  
    return 1.0*m-maxflow;   
}
void dfs1(int u)
{
	vis[u]=true;
	if(u>=1&&u<=n)
	sum++;
	for(int i=head[u];i!=-1;i=e[i].next)
	{
		int v=e[i].ed;
		if(vis[v]==false&&e[i].flow>0)
		  dfs1(v);
	}
}
int main()
{
	int i;
	double Left,Right,mid,flow;
	while(scanf("%d%d",&n,&m)!=-1)
	{
		if(m==0){printf("1\n1\n");continue;}
		start=0,end=n+m+1,ans=end+1;
		for(i=0;i<m;i++)
		{
			scanf("%d%d",&P[i].x,&P[i].y);
		}
		Left=0;Right=m;
		while(Right-Left>=1.0/n/n)//胡伯涛的论文给出了证明,不同解之间误差的精度不超过1/(n*n）  
		{
			mid=(Left+Right)/2;
			makemap(mid);
			flow=isap();//求出最大权值闭合图
			if(flow<eps)//如果小于0，g值太大
				Right=mid;
			else Left=mid;
		}
		makemap(Left);//最大密度建图
		isap();
		memset(vis,false,sizeof(vis));
		sum=0;
		dfs1(start);
		printf("%d\n",sum);
		for(i=1;i<=n;i++)
		  if(vis[i]==true)//残留网络中源点能到达的点
			  printf("%d\n",i);
	}
	return 0;
}

