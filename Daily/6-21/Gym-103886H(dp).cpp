
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
#define pb push_back
#define ve vector
#define FOR(i, a, b) for (int i = a; i < b; ++i)
using namespace std;

template <typename T>
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} 
  out << "]";
  return out;
}

vector<string> a;
const int N = 3030;
int p[N][N];
int L[N][N], R[N][N];
int dp[N][N];

/*bool ok(int l, int r) {
  int sz = r - l + 1;
}*/

void solve() {
  int n, m;
  cin >> n >> m;
  bool block = false;
  for(int i = 0; i < n; i++) {
    string s;
    cin >> s;
    a.push_back(s);
    
    int sum = 0;
    for(int j = 0; j < m; j++) {
      if(s[j] == '.') {
        sum++;
      }
      p[i][j] = sum;
    }

    if(sum == 0) block = true;

    for(int j = 0; j < s.size(); j++) {
      int k = j;
      while(k < s.size() && s[k] == '.') {
        k++;
      }

      for(int x = j; x < k; x++) {
        L[i][x] = j - 1;
        R[i][x] = k;
      }
      j = k;
    }
  }

  if(block) {
    cout << -1 << endl;
    return;
  }

  memset(dp, -1, sizeof dp);
  for(int j = 0; j < m; j++) {
    if(a[0][j] == '#') continue;
    int l = L[0][j], r = R[0][j];
    dp[0][j] = max(j - l - 1 + 1, r - j - 1 + 1);
  }

  for(int i = 1; i < n; i++) {
    for(int j = 0; j < m; j++) {
      if(a[i][j] == '#') continue;
      
      vector<int> indexs;
      int pivot = j;
      while(pivot < m && a[i][pivot] == '.') {
          int lsz = pivot - L[i][j] - 1, rsz = R[i][j] - pivot - 1;
          if(dp[i - 1][pivot] != -1) { //not move pivot
            dp[i][pivot] = max(dp[i][pivot], dp[i - 1][pivot] + max(lsz + 1, rsz + 1));
          }
          indexs.push_back(pivot);
          pivot++;
      }
      
      int mx = -1000000000, last = -1;
      int delta = m;
      for(int index : indexs) {
          if(dp[i - 1][index] != -1 && dp[i - 1][index] + delta > mx) {
              mx = dp[i - 1][index] + delta;
              last = index;
          }
          
          if(last != -1) {
              dp[i][index] = max(dp[i][index], dp[i - 1][last] + (index - last + 1));
          }
          delta--;
      }
      
      reverse(indexs.begin(), indexs.end());
      mx = -1000000000; last = -1;
      delta = m;
      for(int index : indexs) {
          if(dp[i - 1][index] != -1 && dp[i - 1][index] + delta > mx) {
              mx = dp[i - 1][index] + delta;
              last = index;
          }
          
          if(last != -1) {
              dp[i][index] = max(dp[i][index], dp[i - 1][last] + (last - index + 1));
          }
          delta--;
      }
      
      j = pivot;
    }
  }
  
  /*for(int i = 0; i < n; i++) {
      for(int j = 0; j < m; j++) {
          cout << dp[i][j] << " ";
      }
      cout << endl;
  }
  cout << endl;*/

  int res = -1;
  for(int j = 0; j < m; j++) {
    res = max(res, dp[n - 1][j]);
  }
  cout << res << endl;
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
