
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

using namespace std;

using ll = long long;
#define pb push_back
#define ve vector



template <typename U, typename T, class Cmp>
ostream& operator <<(ostream& out, const map<U, T, Cmp>& a) {
  out << "{"; bool first = true;
  for (auto& p : a) { out << (first ? "" : ", "); out << p.first << ":" << p.second; first = 0;} out << "}";
  return out;
}

const int N = 2e5 + 20;
int a[N], b[N], c[N];
int dp1[N];
bool v1[N];
int p[N], p1[N];
int res = 1e9;

int get(int l, int r) {
    if(l == 0) return p[r];
    return p[r] - p[l - 1];
}

int get1(int l, int r) {
    if(l == 0) return p1[r];
    return p1[r] - p1[l - 1];
}

void solve() {
    memset(v1, false, sizeof v1);
    memset(p, 0, sizeof p);
    
    int n, m, k, tot;
    cin >> n >> m >> k;
    tot = n + m + k;
    
    res = min(res, tot - n);
    res = min(res, tot - m);
    res = min(res, tot - k);
    
    for(int i = 0; i < n; i++) cin >> a[i], v1[a[i]] = true;
    for(int i = 0; i < m; i++) cin >> b[i], p[b[i]] = 1;
    for(int i = 0; i < k; i++) cin >> c[i], p1[c[i]] = 1;
    
    for(int i = 1; i < N; i++) {
        p[i] += p[i - 1];
        p1[i] += p1[i - 1];
    }
    
    int cnt = 0;
    dp1[0] = n;
    for(int i = 1; i <= tot; i++) {
        if(v1[i]) {
            cnt++;
        }
        dp1[i] = (i - cnt) + (n - cnt);
        
        int y = get1(0, i);
        y += (tot - i - get1(i + 1, tot));
        

        res = min(res, (dp1[i] + m + y) / 2);
    }
    
    //cout << endl;
    
    
    priority_queue<int> pq;
    pq.push(-(dp1[0] + (tot - get(1, tot))));
    
    for(int i = 1; i <= tot; i++) {
        int x = get(0, i) + (tot - i - get(i + 1, tot));
        int best = -pq.top();
        
        int o1 = (tot - i - get(i + 1, tot));
        int o2 = get(i + 1, tot);
        
        
        //cout << i << "  " << best <<"  " << o1 << " " << o2 << endl;
        
        best +=  (o2 - o1);
        best += get1(0, i) + (tot - i - get1(i + 1, tot));
        
        //cout << i << "  " << dp1[i] << "  " << x << endl << endl;
        
        res = min(res, best / 2);
        pq.push(-(dp1[i] + x));
    }


    cout << res << endl;
}   


int main()
{   
    int t = 1;
    //cin >> t;
    while(t --) {
        solve();
    }
    return 0;
}

