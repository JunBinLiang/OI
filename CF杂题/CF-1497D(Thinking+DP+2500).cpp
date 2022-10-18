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


const int N = 5010;
int a[N], b[N];
ll dp[N];
int n;
void solve() {
    scanf("%d", &n);
    for(int i = 0; i < n; i++) scanf("%d", &a[i]);
    for(int i = 0; i < n; i++) scanf("%d", &b[i]);
    ll res = 0;
    for(int i = 0; i < n; i++) dp[i] = 0;
    dp[0] = 0;
    
    for(int i = 1; i < n; i++) {
        ll m1 = 0, m2 = 0;
        for(int j = i - 1; j >= 0; j--) {
            if(a[i] == a[j]) {
                continue;
            }
            m1 = max(m1, dp[j] + abs(b[i] - b[j]));
            dp[j] = max(dp[j], m2 + abs(b[i] - b[j]));
            dp[i] = max(dp[i], m1);
            m2 = max(m2, dp[i]);
            res = max(res, dp[i]);
            res = max(res, dp[j]);
        }
    }
    cout << res << endl;

} 

int main() {
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
