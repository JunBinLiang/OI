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
#include <fstream>
 
using ll = long long;
using ull = unsigned long long;
#define pb push_back
#define vec vector
#define var auto
#define FOR(i, a, b) for (int i = a; i < b; ++i)
using namespace std;
 
template <typename T>
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} 
  out << "]";
  return out;
}
 
const int N = 100;
bool stop = false;
int ca = 0;
ull ans[N];
bool DEBUG = false;
void solve() {
    memset(ans, 0, sizeof ans);

    int n, p;
    cin >> n >> p;
    if(n == 0 && p == 0) {
        stop = true;
        return;
    }
    
    ca++;
    vector<pair<int, int>> a;
    for(int i = 0; i < n; i++) {
        int w, m;
        cin >> w >> m;
        a.push_back({w, m});
    }

    for(int i = 0; i < a.size(); i++) {
        vector<int> b;
        for(int j = 0; j < a.size(); j++) {
            int w = a[j].first, t = a[j].second;
            if(i == j) t--;
            while(t--) b.push_back(w);
        }
        
        ull dp[65], cur[65];
        memset(dp, 0, sizeof dp);
        dp[0] = 1;
        for(int w : b) {
            for(int j = 0; j < p; j++) {
                cur[j] = dp[j];
                if(j - w >= 0) {
                    cur[j] += dp[j - w];
                }
            }
            swap(cur, dp);
        }
        
        for(int j = 0; j < p; j++) {
            if(j + a[i].first >= p) {
                ans[i] += dp[j];
            }
        }
        
        if(DEBUG) {
            cout << b << endl;
            for(int j = 0; j <= p; j++) cout << dp[j] << " ";
            cout << endl << endl;
        }
    }


    cout << "Case " << ca << ": ";
    for(int i = 0; i < n; i++) {
        cout << ans[i] << " ";
    }
    cout << endl;
}
    

int main()
{
  int t = 1;
  //cin >> t;
  while(!stop) {
    solve();
  }
  return 0;
}
