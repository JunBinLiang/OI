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

const int N = 2e5 + 10;
int mod = 9, base = 10;
int h[N], p[N];
vector<int> g[9];
int get(int left, int right) {
    if(left == 0) {
        return h[right];
    }
    ll res = (h[right] - (h[left - 1] * p[right - left + 1] % mod) + mod) % mod;
    if(res < 0)res += mod;
    return (int)(res % mod);
}

void doit(int c1, int c2, int& res1, int& res2) {
    if(res1 >= c1) {
        if(res1 > c1) {
            res1 = c1;
            res2 = c2;
        } else {
            if(res2 > c2) {
                res2 = c2;
            }
        }
    }
}

void solve() {
    string s;
    cin >> s;
    int k, m;
    scanf("%d%d", &k, &m);
    int n = s.size();
    
    p[0] = 1;
    for(int i = 1; i < n + 5; i++) {
        p[i] = p[i - 1] * 10;
        p[i] %= mod;
    }

    int ha = 0;
    for(int i = 0; i < s.size(); i++) {
        int d = s[i] - '0';
        ha = ha * 10 + d;
        ha %= mod;
        h[i] = ha;
    }

    for(int i = 0; i < 9; i++) g[i].clear();
    for(int i = 0, j = 0; i < n; i++) {
        if(i + 1 >= k) {
            int hh = get(j, i);
            g[hh].push_back(j);
            j++;
        }
    }
    
    for(int i = 0; i < m; i++) {
        int l, r, x;
        scanf("%d%d%d", &l, &r, &x);
        l--; r--;
        int v = get(l, r);
        int res1 = 5e5, res2 = 5e5;
        for(int a = 0; a < 9; a++)
        {
            for(int b = 0; b < 9; b++) {
                if((a * v + b) % 9 != x) continue;
                if(a == b) {
                    if(g[a].size() > 1) {
                        int c1 = g[a][0], c2 = g[a][1];
                        doit(c1, c2, res1, res2);
                    }
                } else {
                    if(g[a].size() > 0 && g[b].size() > 0) {
                        int c1 = g[a][0], c2 = g[b][0];
                        doit(c1, c2, res1, res2);
                    }
                }
            }
        }
        if(res1 >= n) {
            printf("-1 -1\n");
        } else {
            printf("%d %d\n", res1 + 1, res2 + 1);
        }
        
    }
    
} 

int main() {
    int t = 1;
    cin >> t;
    
    while(t--) {
        solve();
    }
    return 0;
}

