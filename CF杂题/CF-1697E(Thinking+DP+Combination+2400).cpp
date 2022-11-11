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

template <typename U, typename T, class Cmp>
ostream& operator <<(ostream& out, const unordered_map<U, T, Cmp>& a) {
  out << "{"; bool first = true;
  for (auto& p : a) { out << (first ? "" : ", "); out << p.first << ":" << p.second; first = 0;} out << "}";
  return out;
}

unsigned long long seed = 131;
unsigned long long rands() { return seed = (seed << 15) + (seed << 8 ) + (seed >> 3);}

void debug() {
    cout << "________________" << endl;
}


int di(const pair<int, int>& p1, const pair<int, int>& p2) {
    return abs(p1.first - p2.first) + abs(p1.second - p2.second);
}

const int N = 110, mod = 998244353;
pair<int, int> a[N];
int color[N];
int dis[N][N];
ll dp[N][N];
ll C[510][510];
ll fact[N];
vector<int> g[N];
int n = 0, c = 1;

void dfs1(set<int>& cur, int root) {
    for(int nxt : g[root]) {
        if(cur.find(nxt) == cur.end()) {
            cur.insert(nxt);
            dfs1(cur, nxt);
        }
    }
}

ll dfs(vector<int>& p, int i, int take) {
    if(i >= p.size()) {
        return 1;
    }
    if(dp[i][take] != -1) {
        return dp[i][take];
    }
    ll res = 0;
    int w = p[i];
    ll remain = n - take;
    
    
    if(w != 1){
        ll ways = fact[w] * C[remain][w];
        ways %= mod;
        res += (dfs(p, i + 1, take + w) * ways);
        res %= mod;
        res += (dfs(p, i + 1, take + 1) * remain);
        res %= mod;
    } else {
        res += (dfs(p, i + 1, take + 1) * remain);
        res %= mod;
    }
    
    return dp[i][take] = res;
}

void solve() {
    cin >> n;
    for(int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        a[i] = {x, y};
    }

    memset(color, 0, sizeof color);

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            dis[i][j] = di(a[i], a[j]);
        }
    }

    for(int i = 0; i < n; i++) {
        int minD = 2e9;
        for(int j = 0; j < n; j++) {
            if(i != j)
                minD = min(minD, dis[i][j]);
        }

        for(int j = 0; j < n; j++) {
            if(i != j && dis[i][j] == minD) {
                g[i].push_back(j);
            }
        }
    }


    vector<int> item;
    for(int i = 0; i < n; i++) {
        if(color[i] > 0) continue;

        int minD = 2e9;
        for(int j = 0; j < n; j++) {
            if(i != j)
                minD = min(minD, dis[i][j]);
        }
        set<int> cur;
        cur.insert(i);
        dfs1(cur, i);
        vector<int> b(cur.begin(), cur.end());
        vector<int> d(cur.begin(), cur.end());
        bool bad = false;
        for(int x : b) {
            for(int y : d) {
                if(x != y && dis[x][y] != minD) bad = true;
            }
        }
        
        if(bad) {
            color[i] = c++;
            item.push_back(1);
        } else {
            int sz = 0;
            for(int x : b) {
                if(!color[x]) {
                    color[x] = c;
                    sz++;
                }
            }
            c++;
            item.push_back(sz);
        }
        
        /*cout << b << endl;
        for(int j = 0; j < n; j++) cout << color[j] << " ";
        cout << endl << endl;*/
    }
    
    C[0][0] = 1;
    for(int i = 1;i <= 500; i++) {
        C[i][0]=1;
        for(int j = 1;j <= i;j++) {
            C[i][j] = ( C[i-1][j] + C[i-1][j-1] ) % mod;
        }
    }
    
    fact[0] = fact[1] = 1;
    for(int i = 2; i < N; i++) fact[i] = (fact[i - 1] * i) % mod;
    
    memset(dp, -1, sizeof dp);
    ll res = dfs(item, 0, 0);
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

