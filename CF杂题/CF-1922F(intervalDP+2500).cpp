#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <queue>
#include <list>
#include<fstream>
#include <bitset>

using namespace std;  
using ll = long long;
using ull = unsigned long long;
#define pb push_back
#define P pair
#define V vector
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define FFOR(i, a, b) for (int i = a; i <= b; ++i)

template <typename U, typename T, class Cmp>
ostream& operator <<(ostream& out, const map<U, T, Cmp>& a) {
  out << "{"; bool first = true;
  for (auto& p : a) { out << (first ? "" : ", "); out << p.first << ":" << p.second; first = 0;} out << "}";
  return out;
}

const int N = 105, INF = 1e5;
int f[N][N][N], g[N][N][N];
void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
      scanf("%d", &a[i]);
    }

    //clear
    for(int i = 0; i <= n; i++) {
      for(int j = 0; j <= n; j++) {
        for(int k = 0; k <= m; k++) {
          f[i][j][k] = g[i][j][k] = INF;
        }
      }
    }

    //base case
    for(int i = 0; i < n; i++) {
      for(int x = 1;  x <= m; x++) {
        f[i][i][x] = 1;
        g[i][i][x] = 0;
      }
      f[i][i][a[i]] = 0; 
      g[i][i][a[i]] = 1; 
    }

    for(int len = 2; len <= n; len++) {
      for(int l = 0; l < n; l++) {
        int r = l + len - 1;
        if(r >= n) break;
        for(int x = 1; x <= m; x++) {
          for(int i = l; i < r; i++) {
            //all x
            f[l][r][x] = min(f[l][r][x], f[l][i][x] + f[i + 1][r][x]);
            f[l][r][x] = min(f[l][r][x], g[l][i][x] + f[i + 1][r][x] + 1);
            f[l][r][x] = min(f[l][r][x], f[l][i][x] + g[i + 1][r][x] + 1);
            f[l][r][x] = min(f[l][r][x], g[l][i][x] + g[i + 1][r][x] + 1);
            //no x
            g[l][r][x] = min(g[l][r][x], g[l][i][x] + g[i + 1][r][x]);
            g[l][r][x] = min(g[l][r][x], f[l][i][x] + g[i + 1][r][x] + 1);
            g[l][r][x] = min(g[l][r][x], g[l][i][x] + f[i + 1][r][x] + 1);
            g[l][r][x] = min(g[l][r][x], f[l][i][x] + f[i + 1][r][x] + 1);
          }

          /*for(int x = 1; x <= m; x++) {
            g[l][r][x] = min(g[l][r][x], f[l][r][x] + 1); //single flip
          }*/
        }
        for(int x = 1; x <= m; x++) {
          for(int y = 1; y <= m; y++) {
            if(x != y) {
                g[l][r][x] = min(g[l][r][x], f[l][r][y]);
            }  
          }
        }
      }
    }

    //print answer
    int ans = INF;
    for(int i = 1; i <= m; i++) {
      ans = min(ans, f[0][n - 1][i]);
    }
    printf("%d\n", ans);
}
    

int main()
{
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
