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
#include <fstream>
#include <iomanip>
 
using ll = long long;
using ull = unsigned long long;
#define pb push_back
#define vec vector
#define var auto
#define FOR(i, a, b) for (int i = a; i < b; ++i)
using namespace std;
 
template <typename T>
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} 
  out << "]";
  return out;
}

unsigned long long seed = 75;
unsigned long long rands(){return seed = (seed << 15) + (seed << 8) + (seed >> 3);}



const int N = 4e5 + 10, M = N * 8;
const ll INF = 10000000000000000ll;
int n, m;

int h[N], e[M], w[M], ne[M], idx, nodeidx;
ll dist[N][2], dp[N];
bool st[N][2];

void add(int a, int b, int c)  // 添加一条边a->b，边权为c
{  
    //cout << "add " << a << " " << b << " " << c << endl;
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++ ;
}

void dij(int start)
{
    for(int i = 0; i < N; i++) dist[i][0] = dist[i][1] = INF;
    dist[start][0] = 0;
    memset(st, 0, sizeof st);
    priority_queue<vector<ll>, vector<vector<ll>>, greater<vector<ll>>> heap;
    heap.push({0, start, 0});

    while (heap.size())
    {
        auto t = heap.top();
        heap.pop();
        int u = t[1], x = t[2];
        if (st[u][x]) continue;
        st[u][x] = true;
        //cout << ver << "  "  <<"  " << dist[ver] << endl;
        
        for (int i = h[u]; ~i; i = ne[i]) {
            int j = e[i];
            if(u >= 1 && u <= n) { //always first enter, w[i] >= 0 always
                if(dist[u][x] + w[i] < dist[j][0]) {
                    dist[j][0] = dist[u][x] + w[i];
                    heap.push({dist[j][0], j, 0});
                }                
            } else {
                if(x == 0) { //first
                    if(j >= 1 && j <= n) {
                        if(dist[u][x] + w[i] < dist[j][0]) {
                            dist[j][0] = dist[u][x] + w[i];
                            heap.push({dist[j][0], j, 0});
                        }
                    } else {
                        //int cost = dp[j] + w[i] - dp[u];
                        if(dist[u][x] + w[i] + dp[j] < dist[j][1]) {
                            dist[j][1] = dist[u][x] + w[i] + dp[j];
                            heap.push({dist[j][1], j, 1});
                        }
                    }
                } else {
                    if(j >= 1 && j <= n) {
                        ll cost = (w[i] + dp[j] - dp[u]);
                        if(dist[u][x] + cost < dist[j][0]) {
                            dist[j][0] = dist[u][x] + cost;
                            heap.push({dist[j][0], j, 0});
                        }
                    } else {
                        ll cost = (w[i] + dp[j] - dp[u]);
                        if(dist[u][x] + cost < dist[j][1]) {
                            dist[j][1] = dist[u][x] + cost;
                            heap.push({dist[j][1], j, 1});
                        }
                    }
                }
            }   
        }
    }
}



vector<int> virs[N];

void solve() { 
    freopen("olympair.dat", "r", stdin); freopen("olympair.sol", "w", stdout);
    memset(h, -1, sizeof h);

    scanf("%d%d", &n, &m);
    idx = 0;
    nodeidx = n + 1;
    
    for(int i = 0; i < m; i++) {
        int op, u, v, w;
        scanf("%d%d%d%d", &op, &u, &v, &w);
        if(op == 1) {
            add(u, v, w);
            int newnode = nodeidx++;
            dp[newnode] = INF;
            if(virs[u].size() > 0) {
                add(newnode, virs[u].back(), 0);
                dp[newnode] = min(dp[newnode], dp[virs[u].back()]);
            }
            add(newnode, v, w);
            dp[newnode] = min(dp[newnode], w + 0ll);
            virs[u].push_back(newnode);
        } else {
            //v -> u
            if(virs[u].size() == 0) continue;
            int newnode = nodeidx++;
            dp[newnode] = INF;
            if(virs[v].size() > 0) {
                add(newnode, virs[v].back(), 0);
                dp[newnode] = min(dp[newnode], dp[virs[v].back()]);
                
            }
            add(newnode, virs[u].back(), w);
            dp[newnode] = min(dp[newnode], dp[virs[u].back()] + w);
            virs[v].push_back(newnode);
        }
    }

    for(int i = 1; i <= n; i++) {
        if(virs[i].size() > 0) {
            add(i, virs[i].back(), 0);
        }
    }
    dij(1);
    //for(int i = 1; i < idx; i++) cout << dist[i] << " ";
    //cout << endl << endl;
    
    for(int i = 2; i <= n; i++) {
        if(dist[i][0] == INF) printf("-1\n");
        else printf("%lld\n", dist[i][0]);
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

