#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <queue>
#include <deque>
 
using ll = long long;
using ull = unsigned long long;
#define pb push_back
#define vec vector
#define FOR(i, a, b) for (int i = a; i < b; ++i)
using namespace std;
 
template <typename T>
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} 
  out << "]";
  return out;
}



int dis[305][305];
void solve()
{
	int N, M;
	scanf("%d %d", &N, &M);
	for(int i = 1 ; i <= N ; i ++)
	{
		for(int j = 1 ; j <= N ; j ++)
		{
			if(i == j) dis[i][j] = 0;
			else dis[i][j] = 1e6;
		}
	}
	for(int i = 1 ; i <= M ; i ++)
	{
		int u, v;
		scanf("%d %d", &u, &v);
		dis[u][v] = 1;
	}
  
	for(int i = 1 ; i <= N ; i ++)
	{
		for(int j = 1 ; j <= N ; j ++)
		{
			if(i != j && dis[i][j] + dis[j][i] <= 3)
			  dis[i][j] = dis[j][i] = 0;
			for(int k = 1 ; k <= N ; k ++)
			{
				if(i != j && i != k && j != k && dis[i][j] + dis[j][k] + dis[k][i] <= 3)
				{
					dis[i][j] = dis[j][k] = dis[k][i] = 0;
					dis[i][k] = dis[j][i] = dis[k][j] = 0;
				}	
			}
		}
	}
	for(int k = 1 ; k <= N ; k ++)
	{
		for(int i = 1 ; i <= N ; i ++)
		{
			for(int j = 1 ; j <= N ; j ++)
			{
				if(dis[i][j] > dis[i][k] + dis[k][j])
				dis[i][j] = dis[i][k] + dis[k][j];
			}
		}
	}
	for(int i = 1 ; i <= N ; i ++)
	{
		if(dis[1][i] == 1e6) printf("-1 ");
		else printf("%d ", dis[1][i]);
	}
}



int main()
{
    int t = 1;
    //cin >> t;
    while(t--) {
      solve();
    }
    return 0;
}
