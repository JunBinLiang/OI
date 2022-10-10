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

int n;
const int N = 2e5 + 5;
int a[2][N];
int dp[2][N][2];
int dfs(int r, int c, int st) {
    if(c >= n) {
        return 0;
    }
    if(dp[r][c][st] != -1) {
        return dp[r][c][st];
    }

    int res = 0;
    if(st == 0) {
        if(a[r ^ 1][c] == 1 && a[r][c + 1] == 1) {
            res = max(res, 1 + dfs(r ^ 1, c + 1, 1));
            res = max(res, dfs(r, c + 1, 0));
        } else {
            if(a[r ^ 1][c] == 1) {
                res = max(res, 1 + dfs(r ^ 1, c + 1, 0));
            } else if(a[r][c + 1] == 1) {
                res = max(res, dfs(r, c + 1, 0));
            }  
            res = max(res, dfs(r, c + 1, 0));
        }
    } else {
        res = max(res, dfs(r, c + 1, 0));
    }
    return dp[r][c][st] = res + a[r][c];
}

void solve() {
    scanf("%d", &n);
    memset(a, 0, sizeof a);
    for(int i = 0; i < 2; i++) {
        string s; cin >> s;
        for(int j = 0; j < n; j++) {
            a[i][j] = s[j] - '0';
        }
    }
    memset(dp, -1, sizeof dp);
    int res = dfs(0, 0, 0);
    cout << res << endl;
}

int main() {
    int t = 1;
    //cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
