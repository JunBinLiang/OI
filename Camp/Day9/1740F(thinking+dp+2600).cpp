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

template <typename U, typename T, class Cmp>
ostream& operator <<(ostream& out, const unordered_map<U, T, Cmp>& a) {
  out << "{"; bool first = true;
  for (auto& p : a) { out << (first ? "" : ", "); out << p.first << ":" << p.second; first = 0;} out << "}";
  return out;
}

void debug() {
    cout << "________________" << endl;
}



const int N = 2010, mod = 998244353;
int cnt[N];
ll dp[N][N];
int setsz[N];
ll res = 0;
int n;
void solve() {
    scanf("%d", &n);
    memset(cnt, 0, sizeof cnt);
    memset(setsz, 0, sizeof setsz);
    memset(dp, 0, sizeof dp);

    for(int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        cnt[x] ++;
    }

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            setsz[i] += min(i, cnt[j]);
        }
    }

    dp[0][0] = 1;
    for(int sz = n; sz >= 1; sz--) {
        for(int j = 0; j <= n / sz; j++) {
            for(int k = j * sz; k <= setsz[j]; k++) {
                if(k + sz <= setsz[j + 1]) {
                    dp[j + 1][k + sz] += dp[j][k];
                    dp[j + 1][k + sz] %= mod;
                }
            }
        }
    }
    
    for(int i = 1; i <= n; i++) res += dp[i][n], res %= mod;
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

