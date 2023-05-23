
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
#include <list>

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

const int N = 1e5 + 10, INF = 1e9;
const int mod = 1e9 + 7, base = 26;
ll ha[N], p[N];
int a[N];
map<int, list<int>> f;
int n;

ll get(int l, int r) {
    if(l == 0) return ha[r];
    ll res = (ha[r] - (ha[l - 1] * p[r - l + 1] % mod) + mod) % mod;
    if(res < 0) res += mod;
    return res;
}

void solve() {
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        f[a[i]].push_back(i);
    } 

    p[0] = 1;
    for(int i = 1; i < N; i++) {
        p[i] = p[i - 1] * base;
        p[i] %= mod;
    }

    ll h = 0;
    for(int i = 0; i < n; i++) {
        h = h * base + a[i]; h %= mod;
        ha[i] = h;
    }


    int to = 0;
    int curMin = INF;
    for(int i = 0; i < n; i++) {
        f[a[i]].pop_front();
        for(int j : f[a[i]]) { //new delete
            int sz = j - i;
            if(j + sz - 1 < n && get(i, j - 1) == get(j, j + sz - 1)) {
                //delete 0 - [j - 1]
                if(to <= i) {
                    to = j;
                    curMin = sz;
                } else {
                    if(sz < curMin) {
                        to = j;
                        curMin = sz;
                    }
                }
                break;
            }
        }
    }

    vector<int> res;
    for(int i = to; i < n; i++) res.push_back(a[i]);
    cout << res.size() << endl;
    for(int x : res) cout << x << " ";
    cout << endl;
    
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
