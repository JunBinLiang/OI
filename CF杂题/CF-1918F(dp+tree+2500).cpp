#include <bits/stdc++.h>
using namespace std;

const int NR=2e5+100;
int dep[NR],mx[NR],fa[NR];
vector <int> g[NR];
vector <int> ans;

void dfs(int now)
{
	dep[now]=dep[fa[now]]+1;
	mx[now]=dep[now];
	for(int i=0;i<g[now].size();i++)
	{
		int u=g[now][i];
		dfs(u);
		mx[now]=max(mx[now],mx[u]);
	}
	bool flag=true;
	for(int i=0;i<g[now].size();i++)
	{
		int u=g[now][i];
		if(now!=1&&flag==true&&mx[u]==mx[now])
		{
			flag=false;
			continue;
		}
		//printf("%d %d %d\n",2*dep[now]-mx[u],now,u);
		ans.push_back(2*dep[now]-mx[u]);
	}
}

int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	m++;
	for(int i=2;i<=n;i++) scanf("%d",&fa[i]);
	for(int i=2;i<=n;i++) g[fa[i]].push_back(i);
	dep[0]=-1;
	dfs(1);
	ans.push_back(-1e9);
	sort(ans.begin(),ans.end());
	int tot=2*(n-1);
	int len=ans.size()-1;
	for(int i=1;i<=min(m,len);i++)
	{
		if(ans[i]>0) break;
		tot+=ans[i];
		//printf("%d %d\n",i,ans[i]);
	}
	printf("%d",tot);
	return 0;
}
