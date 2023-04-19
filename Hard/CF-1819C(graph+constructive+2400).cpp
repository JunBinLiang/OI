
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


const int N = 2e5 + 100;
vector<int> g[N];
int best[N], c[2];
bool is[N];
int n;
int mx = 0, center = -1;

int dfs(int pa, int u) {
    vector<pair<int, int>> a;
    for(int& nxt : g[u]) {
        if(nxt == pa) continue;
        int len = dfs(u, nxt);
        a.push_back({len, nxt});
    }
    sort(a.begin(), a.end());
    
    if(a.size() == 0) {
        if(mx == 0) {
            mx = 1;
            center = u;
        }
        return 1;
    } else {
        if(a.size() == 1) {
            int dia = a.back().first + 1;
            if(dia > mx) {
                mx = dia;
                center = u;
                c[0] = a.back().second;
                c[1] = -1;
            }
        } else {
            int dia = 1 + a.back().first + a[a.size() - 2].first;
            if(dia > mx) {
                mx = dia;
                center = u;
                c[0] = a.back().second;
                c[1] = a[a.size() - 2].second;
            }
        }
        best[u] = a.back().second;
        return 1 + a.back().first;
    }
    
}

bool check(int u) {
    return g[u].size() - 1 <= 0;    
}

void solve() {
    cin >> n;
    for(int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    
    memset(is, false, sizeof is);
    memset(best, -1, sizeof best);
    c[0] = c[1] = -1;
    
    dfs(0, 1);
    
    vector<int> p1, p2;
    
    while(c[0] != -1) {
        p1.push_back(c[0]);
        c[0] = best[c[0]];
    }
    while(c[1] != -1) {
        p2.push_back(c[1]);
        c[1] = best[c[1]];
    }
    
    //cout << mx << "  " << center << endl;
    
    reverse(p1.begin(), p1.end());
    p1.push_back(center);
    for(int x : p2) p1.push_back(x);
    
    for(int x : p1) is[x] = true;
    
    for(int i = 0; i < p1.size(); i++) {
        int l1 = i, l2 = p1.size() - i - 1;
        int cnt = 0;
        if(l1 >= 2) cnt++;
        if(l2 >= 2) cnt++;
        
        for(int nxt : g[p1[i]]) {
            if(!is[nxt] && !check(nxt)) {
                cnt++;
            }
        }
        if(cnt >= 3) {
            cout << "No" << endl;
            return;
        }
    }
    
    cout << "Yes" << endl;
    
    for(int i = 0; i < p1.size(); i += 2) {
        cout << p1[i] << " ";
        if(i + 1 < p1.size()) {
            int nxt = p1[i + 1];
            for(int u : g[nxt]) {
                if(!is[u]) {
                    cout << u << " ";
                }
            }
        }
    }
    
    int last = p1.size() - 1;
    if(last % 2 == 0) {
        last--;
    }
    
    for(int i = last; i >= 0; i -= 2) {
        cout << p1[i] << " ";
        if(i - 1 >= 0) {
            int nxt = p1[i - 1];
            for(int u : g[nxt]) {
                if(!is[u]) {
                    cout << u << " ";
                }
            }
        }
    }
    
    
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

