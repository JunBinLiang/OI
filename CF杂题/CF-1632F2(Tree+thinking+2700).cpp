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
#include<fstream>
 

using namespace std;  
using ll = long long;
#define pb push_back

const int N = 3e5 + 10;
vector<int> g[N];
int to[N], dep[N];
int n;

int dp[N];
int maxH = 0;
int dfs(int pa, int root, int h) {
    maxH = max(maxH, h);
    vector<int> a;
    for(int nxt : g[root]) {
        if(nxt == pa) continue;
        int v = dfs(root, nxt, h + 1);
        a.push_back(v);
    }

    sort(a.begin(), a.end());
    reverse(a.begin(), a.end());
    if(a.size() == 0) {
        return h;
    } else if(a.size() == 1) {
        int l1 = a[0];
        dp[h - 1] = max(dp[h - 1], l1 - h); 
        return a[0];
    } else {
        int l1 = a[0], l2 = a[1];
        dp[l2 - 2] = max(dp[l2 - 2], l1 + l2 - 2 * h + 1);
        return l1;
    }
}

void solve() {
    scanf("%d", &n);

    maxH = 0;
    for(int i = 0; i <= n; i++) {
        g[i].clear();
        dp[i] = 0;
    }

    for(int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        u--; v--;
        g[u].pb(v);
        g[v].pb(u);
    }

    dfs(-1, 0, 1);
    
    //for(int i = 0; i <= n; i++) cout << dp[i] << " ";
    //cout << endl;
    
    for(int i = maxH - 1; i >= 0; i--) dp[i] = max(dp[i], dp[i + 1]);
    
    //for(int i = 0; i <= n; i++) cout << dp[i] << " ";
    //cout << endl;
    
    int last = -1;
    for(int x = 1; x <= n; x++) {
        int l = 0, r = maxH - 1;
        int res = -1;
        while(l <= r) {
            int mid = l + (r - l) / 2;
            if(dp[mid] / 2 + x <= mid) {
                res = mid;
                r = mid - 1;
            } else {    
                l = mid + 1;
            }
        }
        
        if(res != -1) last = res;
        if(res == -1) res = last;

        printf("%d ", res);
    }
    printf("\n");
} 


int main() {
	// your code goes here
	int t = 1;
	cin >> t;
	while(t--) {
	    solve();
	}
	return 0;
}
