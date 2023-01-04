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

//ifstream fcin("test/input.txt");
//ofstream fcout("test/output.txt");


const int N = 402, M = 160000 + 10;
const int INF = 1000;
int a[N][N];
int nxt[N][N], f[N][N];
int pre[N][N];
bool is[M];
int mono[N * 2];
int n, m;
void solve() {
    scanf("%d%d", &n, &m);
    int res = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            scanf("%d", &a[i][j]);
            nxt[i][j] = f[i][j] = INF;
        }
    }
    
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            pre[i][j] = -1;
            for(int k = j - 1; k >= 0; k--) {
                if(a[i][k] == a[i][j]) {
                    pre[i][j] = k;
                    nxt[i][k] = j;
                    f[i][k] = j;
                    break;
                }
            }
        }
    }
    

    memset(is, false, sizeof is);

    for(int i = n - 1; i >= 0; i--) {
        vector<int> dp(m, INF);
        vector<int> cur(M, -1);

        for(int j = i; j < n; j++) {

            if(j != i) {
                for(int k = 0; k < m; k++) {
                    int v = a[i][k];
                    cur[v] = k;
                    is[v] = true;
                }
            
                for(int k = m - 1; k >= 0; k--) {
                    int v = a[j][k];
                    if(!is[v]) {
                        continue;
                    }
                    
                    while(cur[v] >= k) {
                        nxt[j][k] = min(nxt[j][k], cur[v]);
                        cur[v] = pre[i][cur[v]];
                    }
                    
                    if(cur[v] != -1) {
                        dp[cur[v]] = min(dp[cur[v]], k);
                        f[j][cur[v]] = min(f[j][cur[v]], k);
                    }
                    
                }
                
                
                for(int k = 0; k < m; k++) {
                    int v = a[i][k];
                    is[v] = false;
                }
            }
            
            for(int k = 0; k < m; k++) {
                dp[k] = min(dp[k], nxt[j][k]);
                dp[k] = min(dp[k], f[j][k]);
            }
            
            
            int hh = 0, tt = 0;
            for(int k = 0, l = 0; k < m; k++) {
                int to = dp[k];
                while(tt - hh > 0 && dp[mono[tt - 1]] >= to) {
                    tt--;
                }
                mono[tt] = k;
                tt++;
                while(l <= k) {
                    while(tt - hh > 0 && mono[hh] < l) {
                        hh++;
                    }
                    if(dp[mono[hh]] <= k) {
                        l++;
                    } else {
                        break;
                    }
                }
                res = max(res, (k - l + 1) * (j - i + 1));
            }
        }
    }
    
    cout << res << endl;
}

int main() {
	// your code goes here
	int t = 1;
	//cin >> t;
	while(t--) {
	    solve();
	}
	return 0;
}
