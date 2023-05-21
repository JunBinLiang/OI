
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

using ll = long long;
#define pb push_back
#define ve vector
#define FOR(i, a, b) for (int i = a; i < b; ++i)
using namespace std;

template <typename T>
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} 
  out << "]";
  return out;
}

template <typename T>
ostream &operator<<(ostream &out, const unordered_set<T> &a)
{
  out << "[";
  bool first = true;
  for (auto v : a)
  {
    out << (first ? "" : ", ");
    out << v;
    first = 0;
  }
  out << "]";
  return out;
}

const int N = 1e5 + 10, M = 17;
int n, m;
bool is[M][M];
vector<int> g[M]; 
bool pre[M][M][(1 << M) + 5];
int cnt[M], dp[(1 << M) + 5];
string s;

void solve() {
    memset(is, 0, sizeof is);
    memset(cnt, 0, sizeof cnt);
    memset(pre, 0, sizeof pre);
    
    cin >> n >> m;
    cin >> s;

    FOR(i, 0, m) {
        FOR(j, 0, m) {
            int o;
            cin >> o;
            if(o) is[i][j] = true;
        }
    } 

    for(int i = 0; i < n; i++) {
        int d = s[i] - 'a';
        cnt[d]++;
        if(i == 0) {
            g[d].push_back(i);
            continue;
        } else {
            bool use[M];
            memset(use, false, sizeof use);
            int st = 0;
            for(int j = 1; j <= M; j++) {
                int mx = -1, idx = -1;
                for(int k = 0; k < m; k++) {
                    if(use[k] || g[k].size() == 0) continue;
                    int last = g[k].back();
                    if(last > mx) {
                        mx = last;
                        idx = k;
                    }
                }
                if(idx == -1) break;
                pre[d][idx][st] = true; 
                //cout << "add " << s[i] << " " << (char)(idx + 'a') << "  " << st << endl;
                if(idx == d && st != 0) break;
                st |= (1 << idx);
                use[idx] = true;
            }
        }
        g[d].push_back(i);
    }

    for(int i = 0; i < m; i++) {
        for(int j = 0; j < m; j++) {
            for(int st = 0; st < (1 << m); st++) {
                for(int k = 0; k < m; k++) {
                    if(st & (1 << k)) {
                        pre[i][j][st] |= pre[i][j][st ^ (1 << k)];
                    }
                }
            }
        }
    }

    int res = 0;
    memset(dp, -1, sizeof dp);
    dp[0] = 0;
    //1 : already delete
    //0 : non delete
    for(int st = 1; st < (1 << m); st++) {
        vector<int> v;
        int off = 0;
        int mx = -1;

        for(int i = 0; i < m; i++) {
            if(st & (1 << i)) { 
                off |= (1 << i);
                v.push_back(i);
            } else {   
                
            }
        }
        
        
        bool ok = true;
        for(int i = 0; i < m; i++) {
            if(off & (1 << i)) continue;
            for(int j = 0; j < m; j++) {
                if(is[i][j]) continue;
                if(off & (1 << j)) continue;
                if(pre[i][j][off]) {
                    ok = false;
                }
            }
        }
        
        for(int x : v) {
            if(dp[st ^ (1 << x)] != -1 && ok) {
                mx = max(mx, cnt[x] + dp[st ^ (1 << x)]);
            }
        }
        dp[st] = mx;
        res = max(res, mx);
    }

    cout << n - res << endl;
    
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
