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

template <typename T>
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} 
  out << "]";
  return out;
}


int cnt[26];
int n, m, k;
const int N = 3e5 + 10;
bool dp[N];

void get(int idx) {
  for(int i = 0; i <= n; i++) {
    dp[i] = false;
  }

  dp[0] = true;
  for(int i = 0; i < 26; i++) {
    if(i == idx || !cnt[i]) continue;
    vector<bool> cur (n + 1);
    for(int j = 1; j <= n; j++) {
      if(j >= cnt[i]) {
        cur[j] = cur[j] | dp[j - cnt[i]];
      }
    }
    for(int j = 0; j <= n; j++) {
      dp[j] = dp[j] | cur[j];
    }
  }
  
}

void solve() { 
  
  scanf("%d%d%d", &n, &m, &k);
  string s;
  cin >> s;
  ll res = 1000000000000000000ll;
  memset(cnt, 0, sizeof(cnt));
  for(char& c : s) {
    cnt[c - 'A']++;
  }
  
  for(int i = 0; i < 26; i++) {
    if(!cnt[i]) continue;
    get(i);
    for(int j = 0; j <= n; j++) {
      //cout << dp[j] << " ";
      if(dp[j] && j + cnt[i] >= n) {
        ll x = n - j;
        int tot = (k - j - cnt[i]);
        if(tot + (cnt[i] - x) >= m) {
          if(tot >= m) {
            res = 0;
          } else {
            ll y = m - tot;
            res = min(res, x * y);
          }
        }

      }
    } 
   // cout << endl;
  }
  cout << res << endl;
 
}

int main() {
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
}
  
  
