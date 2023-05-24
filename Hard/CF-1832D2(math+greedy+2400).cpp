
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

const int N = 2e5 + 10;
int a[N], b[N], ma[N];
ll p[N];

ll get(int l, int r) {
    if(l > r) return 0;;
    if(l == 0) return p[r];
    return p[r] - p[l - 1];
}

void solve() {
    int n, m;
    scanf("%d%d", &n, &m);

    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    sort(a, a + n);
    for(int i = 0; i < n; i++) {
        b[i] = a[i] - i;
        ma[i] = a[i] - i;
        if(i) ma[i] = max(ma[i], ma[i - 1]);
        if(i) b[i] = min(b[i - 1], b[i]);
    }
    
    vector<ll> c, d;
    for(int i = 0; i < n; i++) {
        c.push_back(a[i] + n - i);
    }
    sort(c.begin(), c.end());
    for(int i = 0; i < n; i++) {
        p[i] = c[i];
        if(i) p[i] += p[i - 1];
    }

    ll dsum = 0;
    for(int i = 0; i < n - 1; i++) {
        d.push_back(a[i] + n - i);
        dsum += d.back();
    }
    sort(d.begin(), d.end());


    //cout << c << endl;
    //cout << d << endl;

    for(int i = 0; i < m; i++) {
        int k;
        scanf("%d", &k);
        if(k <= n) {
            int mn = b[k - 1] + k;
            if(k < n) mn = min(mn, a[k]);
            cout << mn << " ";
        } else {
            int x = k - n;
            int sub = x / 2;
            if(x % 2 == 0) {
                ll tot = p[n - 1] + (k + 0ll - n) * n;
                ll o = tot - (c[0] + (k - n)) * n;
                if(o >= sub) {
                    cout << c[0] + (k - n) << " ";
                } else {
                    int v = 0;
                    if((sub - o) % n != 0) v++;
                    cout << c[0] + (k - n) - v - (sub - o) / n << " ";
                }
            } else { 
                if(n == 1) {
                    if(k % 2 == 1)
                        cout << a[0] + k - (k / 2) << " ";
                    else cout << a[0] - (k / 2) << " ";
                    continue;
                }
                int mn = min(a[n - 1], (int)(d[0] + (k - n)));
                int mx = max(a[n - 1], (int)(d.back() + (k - n)));
                int realmn = mn;
                if(mx == mn) realmn--;
                
                ll tot = dsum + a[n - 1] + (k - n + 0ll) * (n - 1) - 1;
                ll o = tot - (realmn + 0ll) * n;
                if(o >= sub) {
                    cout << realmn << " ";
                } else {
                     int v = 0;
                    if((sub - o) % n != 0) v++;
                    cout << realmn - v - (sub - o) / n << " ";
                }
                
            }
        }
    }
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
