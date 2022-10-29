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

int n;
void solve() {
    scanf("%d", &n);
    map<ll, set<ll>> del;
    map<ll, set<ll>> dp;
    map<ll, int> cur;
    
    for(int i = 0; i < n; i++) {
        char c;
        ll v;
        cin >> c >> v;
        if(c == '+') {
            cur[v] = 1;
        } else if(c == '-') {
            for(ll e : del[v]) {
               dp[e].insert(v);
            }
            del.erase(v);
            cur[v] = 0;
        } else {
            ll k = v;
            if(dp.find(k) == dp.end() || dp[k].size() == 0) {
                dp[k].insert(k);
            }
            
            ll now = *(dp[k].begin());
            while(true) {
                del[now].insert(k);
                if(cur.find(now) != cur.end() && cur[now] > 0) {
                    dp[k].erase(now);
                    if(dp[k].size() == 0) {
                        now += k;
                        dp[k].insert(now);
                    } else {
                        now = *(dp[k].begin());
                    }
                } else { 
                    dp[k].insert(now);
                    break;
                }
            }
            del[now].insert(k);
            printf("%lld\n", now);
        }
    }
} 

int main() {
    int t = 1;
    //cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}

