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

int n, m;
const int N = 510;
const int mod = 1e9 + 7;
const int INF = 1e5;
bool is[N];
int dp[N], cnt[N];

void dfs(string& s, int i) {
    if(i >= s.size()) {
        dp[i] = 0;
        cnt[i] = 1;
        return;
    }
    if(dp[i] != -1) {
        return;
    }

    if(is[i]) {
        int res = INF, tot = 0;
        for(int j = i; j <= i + m - 1; j++) {
            if(is[j]) {
                dfs(s, j + m);
                if(1 + dp[j + m] <= res) {
                    if(1 + dp[j + m] == res) {
                        tot += cnt[j + m];
                        tot %= mod;
                    } else {
                        res = 1 + dp[j + m];
                        tot = cnt[j + m];
                    }
                }
            }
        }
        dp[i] = res;
        cnt[i] = tot;
    } else {
        dfs(s, i + 1);
        dp[i] = dp[i + 1];
        cnt[i] = cnt[i + 1];
    }
}


void solve() {
    string s, t;
    cin >> s >> t; 
    n = s.size(), m = t.size();
    memset(is, false, sizeof is);
    memset(dp, -1, sizeof dp);
    memset(cnt, -1, sizeof cnt);
    for(int i = 0; i < n; i++) {
        bool match = true;
        if(i + m - 1 >= n) continue;
        for(int j = 0; j < m; j++) {
            if(s[i + j] != t[j]) {
                match = false;
            }
        }
        is[i] = match;
    }
    dfs(s, 0);
    cout << dp[0] << " " << cnt[0] << endl;
}

int main() {
    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
