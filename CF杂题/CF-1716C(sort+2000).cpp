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

   
using namespace std;  

using ll = long long;
#define pb push_back
#define ve vector
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define RFOR(i, a, b) for (int i = a; i >= b; i--)
#define f first
#define se second
#define W while
#define um unordered_map
#define us unordered_set
#define be begin
#define en end




//11 : 40
const int N = 2e5 + 10;
int a[2][N];
int b[2][N];
bool is[2][N];

int run(int m) {
  int t = 0;
  for(int i = 1; i < m; i++) {
    t = max(t + 1, a[0][i] + 1);
  }

  for(int i = m - 1; i >= 0; i--) {
    t = max(t + 1, a[1][i] + 1);
  }
  return t;
}

void solve() { 
  int m;
  int res = 2e9;
  scanf("%d", &m);
  for(int i = 0; i < 2; i++) {
    for(int j = 0; j < m; j++) {
      scanf("%d", &a[i][j]);
      is[i][j] = false;
    }
  }
    
  is[0][0] = true;
  int r = 1, c = 0;
  int t = 0;
  while(c < m) {
    t = max(t + 1, a[r][c] + 1);
    b[r][c] = t;
    is[r][c] = true;
    if(is[r ^ 1][c]) { // to nxt column
      c++;
    } else { 
      r ^= 1;
    }
  }
  res = min(res, t);
  res = min(res, run(m));
  
  /*cout << t << " " << run(m) << endl;
  
  for(int i = 0; i < 2; i++) {
      for(int j = 0; j < m; j++) {
          cout << b[i][j] << " ";
      }cout << endl;
  }
  cout << endl;*/
  
  for(int i = 0; i < 2; i++) {
      for(int j = 0; j < m; j++) a[i][j]++;
  }
  

  set<pair<int, int>> se;
  for(int i = m - 1; i >= 1; i--) {
    int idx1 = i;
    int idx2 = (1 * m) + i;
    se.insert({-(b[0][i] - (i + 1)), idx1});
    if(i % 2 == 1) {
      for(auto p : se) {
        int idx = p.second;
        int rr = idx / m, cc = idx % m; 
        int tt = a[rr][cc];
        if(rr == 0) {
          tt += (m - cc - 1);
          tt += (m - i - 1);
        } else {
          tt += (cc - i - 1);
        }
        if(rr == 0 &&  cc == i) {
            tt -= (a[rr][cc]);
            tt += b[rr][cc];
        }
        res = min(res, tt);
        break;
      }
    }
    se.erase({-(b[0][i] - (i + 1)), idx1});
    se.insert({-(a[0][i] - (i + 1)), idx1});
    se.insert({-(a[1][i] - (m + (m - i))), idx2});
    
  }
  
  
  
  se.clear();
  for(int i = m - 1; i >= 0; i--) {
    int idx1 = i;
    int idx2 = (1 * m) + i;
    se.insert({-(b[1][i] - (i + 1)), idx2});
    if(i % 2 == 0) {
      for(auto p : se) {
        int idx = p.second;
        int rr = idx / m, cc = idx % m; 
        int tt = a[rr][cc];
        
        if(rr == 1) {
          tt += (m - cc - 1);
          tt += (m - i - 1);
        } else {
          tt += (cc - i - 1);
        }
        
        if(rr == 1 &&  cc == i) {
            tt -= (a[rr][cc]);;
            tt += b[rr][cc];
        }
        res = min(res, tt);
        break;
      }
    }
    se.erase({-(b[1][i] - (i + 1)), idx2});
    se.insert({-(a[1][i] - (i + 1)), idx2});
    se.insert({-(a[0][i] - (m + (m - i))), idx1});
  }
  cout << res << "  " << endl;
}

int main() {
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
}
  
  
