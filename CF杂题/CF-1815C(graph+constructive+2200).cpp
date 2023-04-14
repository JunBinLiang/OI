
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

const int N = 5050;
vector<int> rev[N];
bool vis[N]; 
int in[N], d[N];
vector<int> L[N];

void solve() {
    int n, m;
    cin >> n >> m;
    
    for(int i = 0; i <= n; i++) {
        rev[i].clear();
        L[i].clear();
        in[i] = 0;
        d[i] = 0;
    }
    
    for(int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        if(u != 1){
            rev[v].push_back(u);
            in[u]++;
        }
    }
    
    queue<int> q;
    q.push(1);
    d[1] = 1;
    vis[1] = true;
    int mx = 1;
    while(q.size() > 0) {
        int u = q.front(); q.pop();
        for(int nxt : rev[u]) {
            if(!d[nxt]) {
                d[nxt] = d[u] + 1;
                q.push(nxt);
                mx = max(mx, d[nxt]);
            }
        }
    }
    
    for(int i = 1; i <= n; i++) {
        if(!d[i]) {
            cout << "INFINITE" << endl;
            return;
        }
        L[d[i]].push_back(i);
    }
    
    cout << "FINITE" << endl;
    int res = 0;
    for(int i = 1; i <= n; i++) {
        res += i * (L[i].size());
    }
    cout << res << endl;
    
    for(int i = 1; i <= mx; i++) {
        for(int j = mx; j >= i; j--) {
            for(int x : L[j]) {
                cout << x << " ";
            }
        }
    }
    cout << endl;
}   


int main()
{   
    int t = 1;
    cin >> t;
    while(t --) {
        solve();
    }
    return 0;
}
