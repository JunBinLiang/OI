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
 
using ll = long long;
using ull = unsigned long long;
#define pb push_back
#define vec vector
#define var auto
#define FOR(i, a, b) for (int i = a; i < b; ++i)
using namespace std;
 
void yes() {
    cout << "Hello, Deimos!" << endl;
}

void no() {
    cout << "Dire victory" << endl;
}

const int N = 1010, INF = 1e9;
int n, m, v;
int r1, c1, r2, c2;
char s[N][N];
int d[N][N];
bool st[N][N];
pair<int, int> q[N * N];

vector<vector<int>> dir = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};

void spfa()
{
    memset(st, false, sizeof st);
    d[r1][c1] = 0;
    int hh = 0, tt = 1;
    q[0] = {r1, c1}; st[r1][c1] = true;

    while (hh != tt)
    {
      auto p = q[hh ++];
      if(hh == N * N) hh = 0;
      int r = p.first, c = p.second;
      st[r][c] = false;
      
      for (auto& di : dir) {
        int rr = r + di[0], cc = c + di[1];
        if(rr < 0 || rr >= n || cc < 0 || cc >= m) continue;  

        int newd = d[r][c] + 1;
        if(s[rr][cc] == 'F') newd = 0;
        if(d[r][c] + 1 <= v && newd < d[rr][cc]) {
            d[rr][cc] = newd;
            if(!st[rr][cc]) {
                q[tt++] = {rr, cc};
                if (tt == N) tt = 0;
                st[rr][cc] = true;
            }
        }
      }
    }
}

void dijkstra()
{
    
    
    memset(st, 0, sizeof st);
    d[r1][c1] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> heap;
    heap.push({0, r1 * m + c1});

    while (heap.size())
    {
        auto t = heap.top();
        heap.pop();

        int id = t.second;
        int r = id / m, c = id % m;
        if (st[r][c]) continue;
        st[r][c] = true;

        /*for (int i = h[ver]; ~i; i = ne[i])
        {
            int j = e[i];
            if (dist[j] > dist[ver] + w[i])
            {
                dist[j] = dist[ver] + w[i];
                heap.push({dist[j], j});
            }
        }*/

        for (auto& di : dir) {
            int rr = r + di[0], cc = c + di[1];
            if(rr < 0 || rr >= n || cc < 0 || cc >= m) continue;  
            
            int newd = d[r][c] + 1;
            if(s[rr][cc] == 'F') newd = 0;
            if(d[r][c] + 1 <= v && newd < d[rr][cc]) {
                d[rr][cc] = newd;
                heap.push({d[rr][cc], rr * m + cc});
            }
        }
    }
}

void solve() {
    scanf("%d%d%d", &n, &m, &v);
    scanf("%d%d%d%d", &r1, &c1, &r2, &c2);
    r1--; c1--;
    r2--; c2--;
    for(int i = 0; i < n; i++) {
        scanf("%s", s[i]);
    }

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            d[i][j] = INF;
        }
    }

    dijkstra();
    
    /*for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cout << d[i][j] << "  ";
        }
        cout << endl;
    } cout << endl;*/
    
    if(d[r2][c2] <= v) {
        yes();
    } else {
        no();
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
