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


const int N = 5050, INF = 1e9;
int a[N];
int n, k;
int dp[N][(1 << 9) + 10];
int p[N];
int cnt[N];

int dfs(int curMin, int s) {
    if(s == 0) {
        return 0;
    }
    if(dp[curMin][s] != -1) {
        return dp[curMin][s];
    }
    int res = INF; 
    for(int i = 0; i < k; i++) {
        if(s & (1 << i)) {
            int x = 0;
            for(int j = 0; j < k; j++) {
                if((!(s & (1 << j))) && (curMin + j <= n) && (j > i) && (p[curMin + j] > p[curMin + i])) {
                    x++;
                }
            }
            
            for(int j = 0; j < i; j++) {
                if(s & (1 << j)) {
                    if(p[curMin + j] > p[curMin + i]) x--;
                }
            }
            
            int nxtMin = curMin, news = s ^ (1 << i);
            int to = -1;
            //find the first on bit
            for(int j = 0; j < k; j++) {
                if(news & (1 << j)) {
                    nxtMin = curMin + j;
                    to = j;
                    break;
                }
            }
            
            if(news == 0) {
                news = (1 << k) - 1;
                nxtMin = curMin + k;
                for(int j = 0; j < k; j++) {
                    if(news & (1 << j) && nxtMin + j > n) {
                        news ^= (1 << j);
                    }
                }
                res = min(res, dfs(nxtMin, news) + cnt[curMin + i] + x);
                continue;
            }
            
            for(int j = 0; j < to; j++) {
                news >>= 1;
                news += (1 << (k - 1));
            }
            for(int j = 0; j < k; j++) {
                if(news & (1 << j) && nxtMin + j > n) {
                    news ^= (1 << j);
                }
            } 
            res = min(res, dfs(nxtMin, news) + cnt[curMin + i] + x);
        } else {

        }
    }
    return dp[curMin][s] = res;
}

void solve() {
    scanf("%d%d", &n, &k);
    k++;
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        p[a[i]] = i;
    }
    memset(dp, -1, sizeof dp);
    memset(cnt, 0, sizeof cnt);
    for(int i = 1; i <= n; i++) {
        for(int j = i - 1; j >= 1; j--) {
            if(p[j] > p[i]) {
                cnt[i]++;
            }
        }
    }

    /*for(int i = 1; i <= n; i++) {
        cout << i << "     " << cnt[i] << endl;
    } cout << endl;*/

    int s = 0;
    for(int i = 0; i < k; i++) {
        if(i + 1 <= n) {
            s |= (1 << i);
        }
    }
    int res = dfs(1, s);
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
