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

const int N = 1e6 + 10;
ve<int> g[N];
int n, k;
int dp[N], dep[N];
int res = 0;
void dfs1(int root) {
    if(g[root].size() == 0) { //leaf
        dp[root] = 1;
        dep[root] = k;
        return;
    }
    for(int& nxt : g[root]) {
        dfs1(nxt);
        if(dep[nxt]) {
            dp[root] += dp[nxt];
        }
        dep[root] = max(dep[root], dep[nxt] - 1);
    }
}

void dfs2(int root, int sum) {
    if(g[root].size() == 0) {
        res = max(res, sum + 1);
        return;
    }
    for(int& nxt : g[root]) {
        if(dep[nxt] != 0) {
            dfs2(nxt, sum + dp[root] - dp[nxt]);
        } else {
            dfs2(nxt, sum + dp[root]);
        }
    }
}

int main() {
    scanf("%d%d", &n, &k);
    for(int i = 2; i <= n; i++) {
        int pa;
        scanf("%d", &pa);
        g[pa].pb(i);
    }
    dfs1(1);
    dfs2(1, 0);
    cout << res << endl;    return 0;
}
