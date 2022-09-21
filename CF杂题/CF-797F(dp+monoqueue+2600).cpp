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

const int N = 5005;
ll dp[N][N];
vector<ll> dis[N];
ll res = 1000000000000000000ll;
pair<ll, int> mono[N + 10];

ll get(vector<ll>& a, int l, int r) {
    if(l > r) return 0;
    if(l == 0) return a[r];
    return a[r] - a[l - 1];
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    vector<pair<int, int>> b(m);
    for(int i = 0; i < n; i++) cin >> a[i];
    for(int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        b[i] = {x, y}; 
    }
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            dp[i][j] = 1000000000000000ll;
        }
    }

    /*for(int i = 0; i < m; i++) {
        ll s = 0;
        dis[i].pb(0);
        for(int j = 0; j < n; j++) {
            s += abs(a[j] - b[i].first);
            dis[i].pb(s);
        }
    }*/

    //first i hole, j mice
    ll sum = 0;
    dp[0][0] = 0;
    for(int i = 1; i <= n; i++) {
        if(i > b[0].second) break;
        sum += abs(a[i - 1] - b[0].first);
        dp[0][i] = sum; 
    }


    ll tot = b[0].second;
    for(int i = 1; i < m; i++) {
        vector<ll> pre;
        pre.push_back(0);
        ll ss = 0;
        for(int j = 0; j < a.size(); j++) {
            ss += abs(b[i].first - a[j]);
            pre.push_back(ss);
        }
        int sz = b[i].second;
        tot += sz;
        
        mono[0] = {dp[i - 1][0] + ss, 0};
        int hh = 0, tt = 1;
        
        for(int j = 1; j <= n; j++) {
            if(j > tot) break;
            while(tt - hh > 0 && j - mono[hh].second > sz) {
                hh++;
            }
            
            int idx = mono[hh].second;
            dp[i][j] = min(dp[i][j], dp[i - 1][idx] + get(pre, idx + 1, j));
            
            

            while(tt - hh > 0 && dp[i - 1][j] + get(pre, j + 1, n) <= mono[tt - 1].first) {
                tt--;
            }
            mono[tt++] = {dp[i - 1][j] + get(pre, j + 1, n), j};
        }
        //推
        dp[i][0] = 0;
        for(int j = 0; j <= n; j++) {
            dp[i][j] = min(dp[i][j], dp[i - 1][j]);
        }
    }
    
    if(tot < n) {
        cout << -1 << endl;
        return 0;
    }
    
    for(int i = 0; i < m; i++) {
        res = min(res, dp[i][n]);
    }
    cout << res << endl;
    return 0;
}
