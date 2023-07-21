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
#include <fstream>
#include <iomanip>
 
using ll = long long;
using ull = unsigned long long;
#define pb push_back
#define vec vector
#define var auto
#define FOR(i, a, b) for (int i = a; i < b; ++i)
using namespace std;
 
 
const int N = 2e5 + 10;
const ll INF = 9000000000000000000ll;
int n, m;

struct Flight {
    int u, v, s, e;
    bool operator < (const Flight& other) {
        if(s == other.s) return e < other.e;
        return s < other.s;
    }
} a[N];

deque<int> q[N];
ll dp[N];
/*
dp[i] = dp[j] + (S[i] - E[j]) * (S[i] - E[j])
dp[i] = dp[j] + S[i] ^ 2 + E[j] ^ 2 - 2S[i]E[j]

dp[j] + E[j]^2 = 2S[i] * (E[j]) + dp[i] - S[i] ^ 2
(dp[j] + E[j] ^ 2, E[j])
*/

ll up(int i, int j) {
    return (dp[i] + (a[i].e + 0ll) * a[i].e) - (dp[j] + (a[j].e + 0ll) * a[j].e);
}

ll down(int i, int j) {
    return a[i].e - a[j].e;
}

void solve() {
    scanf("%d%d", &n, &m);
    for(int i = 0; i < m; i++) {
        scanf("%d%d%d%d", &a[i].u, &a[i].v, &a[i].s, &a[i].e);
    }

    sort(a, a + m);
    memset(dp, -1, sizeof dp);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    
    for(int i = 0; i < m; i++) {
        int u = a[i].u, v = a[i].v, S = a[i].s, E = a[i].e;
        //cout << u << " " << v << " " << S << " " << E << endl;
        while(pq.size() > 0 && pq.top().first <= S) {
            auto pa = pq.top(); pq.pop();
            int index = pa.second;
            auto& q2 = q[a[index].v];
            while(q2.size() > 1 && (double)up(q2.back(), index) * down(q2.at(q2.size() - 2), q2.back()) <= (double)up(q2.at(q2.size() - 2), q2.back()) * down(q2.back(), index)) {
                q2.pop_back();
            }
            q2.push_back(index);
        }
        
        auto& q1 = q[u];
        if(u == 1) {
            dp[i] = (S + 0ll) * S;
            pq.push({E, i});
        }
        
        if(q1.size() > 0) {
            int p = q1.back();
            int l = 0, r = q1.size() - 2;
            while(l <= r) {
                int mid = l + (r - l) / 2;
                if(up(q1.at(mid + 1), q1.at(mid)) >= (double)(2 * S) * down(q1.at(mid + 1), q1.at(mid))) {
                    p = q1.at(mid);
                    r = mid - 1;
                } else {
                    l = mid + 1;
                }
            }
            
            int j = p;
            if(u == 1)
                dp[i] = min(dp[i], dp[j] + (S - a[j].e + 0ll) * (S - a[j].e + 0ll));
            else dp[i] = dp[j] + (S - a[j].e + 0ll) * (S - a[j].e + 0ll);
            if(u != 1) {
                pq.push({E, i});
            }
        }
        
    }
    
    //for(int i = 0; i < m; i++) cout << dp[i] << " ";
    //cout << endl;


    ll res = INF;
    for(int i = 0; i < m; i++) {
        if(a[i].v == n && dp[i] != -1) {
            res = min(res, dp[i]);
        }
    }
    if(res == INF) cout << -1 << endl;
    else cout << res << endl;
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

/*
4 5
1 2 20 20
1 3 40 50
3 3 70 100
3 4 110 1337
2 4 300 420
*/
