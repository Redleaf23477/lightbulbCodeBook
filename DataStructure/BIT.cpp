#define lowbit(x) x&-x

int arr[N]; //紀錄前綴和
int bit[N];

void conv(int a[], int n)  //離散化
{
    vector<int> tmp;
    for(int i=1; i<=n; i++) tmp.push_back(a[i]);
    sort(tmp.begin(), tmp.end());
    for(int i=1; i<=n; i++) a[i] = lower_bound(tmp.begin(), tmp.end(), a[i]) - tmp.begin() + 1;
}

void buildbit() //每個bit[x]紀錄[x-lowbit(x)+1, x]的總和
{
    for(int i = 0; i < n; i++) bit[i] = arr[i]-arr[i-lowbit(i)];
}

int sum(int x) //查詢[1,x]的總和
{
    int rtn = 0;
    for(;x;x-=lowbit(x)) rtn += bit[x];
    return rtn;
}

void modify(int x, int d) //把位置x的東西加上d
{
    for(;x<=n;x+=lowbit(x)) bit[x] += d;
}
