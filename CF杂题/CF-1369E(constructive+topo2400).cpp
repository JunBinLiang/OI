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

int n, m;
const int N = 1e5 + 10;
const int M = 2e5 + 10;
int a[N], cnt[N];
ve<pair<int, int>> g[N];
bool is1[M];bool is2[M];
void solve() {
    scanf("%d%d", &n, &m);
    for(int i = 0; i < n; i++) {
      scanf("%d", &a[i]);
    }
    
    
    
    memset(cnt, 0, sizeof(cnt));
    memset(is1, false, sizeof(is1));
    memset(is2, false, sizeof(is2));

    ve<int> ans;
    for(int i = 0; i < m; i++) {
      int x, y;
      scanf("%d%d", &x, &y);
      x--;
      y--;
      cnt[x]++; cnt[y]++;
      g[x].pb({y, i});
      g[y].pb({x, i});
    }

    
    queue<int> q;
    for(int i = 0; i < n; i++) {
        if(cnt[i] <= a[i]) {
            q.push(i);
            is2[i] = true;
        }
    }
    
    while(q.size() > 0) {
        int top = q.front(); q.pop();
        //cout << top << endl;
        for(pair<int, int>& p : g[top]) {
            int ty = p.first, idx = p.second;
            cnt[ty]--;
            if(!is1[idx]) {
                is1[idx] = true;
                ans.pb(idx + 1);
            }
            if(!is2[ty] && cnt[ty] <= a[ty]) {
                is2[ty] = true;
                q.push(ty);
            }
        }
    }
    
    
    if(ans.size() == m) {
        printf("ALIVE \n");
        for(int i = ans.size() - 1; i >= 0; i--) {
            printf("%d ", ans[i]);
        }
    } else {
        printf("DEAD");
    }
    printf("\n");
}

int main() {
    int t = 1;
    //cin >> t;
    while(t--) {
        solve();
    }
}
