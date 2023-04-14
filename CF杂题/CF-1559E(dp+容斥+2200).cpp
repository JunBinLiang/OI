
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

const int N = 1e5 + 10, mod = 998244353;
int n, m;
int dp[55][N];
int p[N], cur[N];

int get(int l, int r) {
    if(l == 0) return p[r];
    return (p[r] - p[l - 1] + mod) % mod;
}

pair<int, int> e[100];
int ans[N];
void solve() {
   cin >> n >> m;
   
   for(int i = 1; i <= n; i++) {
       int l, r;
       cin >> l >> r;
       e[i] = {l, r};
   }
   
   
   
   for(int g = m; g >= 1; g--) {
        for(int j = 0; j <= m / g; j++) {
            p[j] = 1;
            cur[j] = 0;
        }
           
        for(int i = 1; i <= n; i++) {
            int l = e[i].first / g, r = e[i].second / g;
            if(e[i].first % g != 0) {
                l++;
            }
            
            if(i != 1) {
                int sum = 0;
                for(int j = 0; j <= m / g; j++) {
                    sum += cur[j];
                    cur[j] = 0;
                    if(sum >= mod) sum -= mod;
                    p[j] = sum;
                }
                cur[0] = 0;
            }
            
            if(l > r) continue;

            for(int j = 1; j <= m / g; j++) {
                int R = j - l, L = max(0, j - r);
                if(j < l) continue;
                cur[j] = get(L, R);
            }
            
        }
        
        int sum = 0;
        for(int j = 1; j <= m / g; j++) {
            sum += cur[j];
            sum %= mod;
        }
       
        ans[g] = sum;
        for(int j = g + g; j <= m; j += g) {
            ans[g] -= ans[j];
            if(ans[g] < 0) ans[g] += mod;
        }
   }

   cout << ans[1] << endl;
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
