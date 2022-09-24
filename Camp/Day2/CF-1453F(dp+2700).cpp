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
const int N = 3010;
const int INF = 1e5;
int a[N];
int dp[N][N];
void solve() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) scanf("%d", &a[i]);

    for(int i = 2; i <= n + 1; i++) {
        for(int j = 0; j <= n + 1; j++) {
            dp[i][j] = INF;
        }
    }

    for(int i = 2; i <= n; i++) {
        int add = 0;
        for(int j = i - 1; j >= 1; j--) {
            if(a[j] + j >= i) { //can reach
                dp[i][a[j] + j] = min(dp[i][a[j] + j], dp[j][i - 1] + add);
                add++;
            }
        }
        for(int j = 1; j <= n; j++) dp[i][j] = min(dp[i][j], dp[i][j - 1]);
    }

    cout << dp[n][n] << endl;
}


int main() {
    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
