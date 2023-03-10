#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <cstring>
#include <algorithm>


using namespace std;  
using ll = long long;
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define pb push_back
#define ve vector



const int N = 200, M = 6200 * 2 + 10;
int INF = 1000000000;
int n, m;
int dist[N][N];


void floyd() {
    for (int k = 1; k <= n; k ++ ) {
        for (int i = 1; i <= n; i ++ ) {
            for (int j = 1; j <= n; j ++ ) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
}



void solve() {
    cin >> n >> m;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            dist[i][j] = INF;
        }
    }
    
    for(int i = 0; i < N; i++) {
        dist[i][i] = 0;
    }
    
    
    for (int i = 0; i < m; i ++ )
    {
        int a, b, c;
        cin >> a >> b >> c;
        dist[a][b] = dist[b][a] = min(dist[a][b], c);
    }


    floyd();
    int res = 0;
    
    for(int i = 1; i <= n; i++) {
        if(dist[1][i] == INF) {
            cout << -1 << endl;
            return;
        }
        res = max(res, dist[1][i]);
    }
    cout << res << endl;
}


int main()
{

  int t = 1;
  //cin >> t;
  while(t--)
  { 
    solve();
  }
  return 0;
}
