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

const int N = 505;
int a[N];
int n;
int dp[N][N][N], p[N][N];
int res = 0;
void solve() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            for(int k = 0; k < N; k++) {
                dp[i][j][k] = -1000000000;
            }
        }
    }
    
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            for(int k = 0; k <= i; k++) {
                if(k > 0){ //same number from last round
                    dp[i][j][k] = max(dp[i][j][k], dp[i - 1][j][k - 1] + a[j]);
                }
                if(j >= i) {
                    int move = j - i;
                    if(move > k) continue;
                    dp[i][j][k] = max(dp[i][j][k], p[k - move][j - 1] + a[j]);
                }
            }
        }

        for(int j = 1; j <= n; j++) {
            for(int k = 0; k <= i; k++) {
                p[k][j] = max(p[k][j], dp[i][j][k]);
            }
        }

        for(int k = 0; k <= i; k++) {
            for(int j = 1; j <= n; j++) {
                p[k][j] = max(p[k][j], p[k][j - 1]);
                res = max(res, p[k][j]);
            }
        }
    }

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
