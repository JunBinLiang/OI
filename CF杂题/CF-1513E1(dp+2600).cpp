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

const int N = 410;
const ll INF = 10000000000000000ll;
int a[N];
int n, k;
ll dp[N][55][2][2];
bool visit[N][55][2][2];

ll dfs(int i, int j, int psign, int csign) {
    if(i >= n) {
        if(j == k) {
            return 0;
        }
        return -INF;
    }

    if(visit[i][j][psign][csign]) {
        return dp[i][j][psign][csign];
    }

    ll res = -INF;
    res = max(res, dfs(i + 1, j, psign, csign)); // skip
    int sum = 0;
    
    int m1 = 1, m2 = 1;
    if(psign == 1) m1 *= -1;
    if(csign == 1) m2 *= -1;

    if(j < k) {
        for(int idx = i; idx < n; idx++) {
            sum += a[idx];
        
            if(j == 0 || j == k - 1) {
                if(j == 0) {
                    res = max(res, m2 * sum + dfs(idx + 1, j + 1, csign, 0));
                    res = max(res, m2 * sum + dfs(idx + 1, j + 1, csign, 1));
                    //cout << "yes  " << m2 * sum << "  " << res << endl;
                }
                else {
                    res = max(res, m1 * (-sum) + dfs(idx + 1, j + 1, csign, 0));
                }
            } else {
                res = max(res, (m1) * (-sum) + (m2) * (sum) + dfs(idx + 1, j + 1, csign, 0));
                res = max(res, (m1) * (-sum) + (m2) * (sum) + dfs(idx + 1, j + 1, csign, 1));
            }
        }

    }
    visit[i][j][psign][csign] = true;
    return dp[i][j][psign][csign] = res;
}

void solve() {
    scanf("%d%d", &n, &k);
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    memset(visit, 0, sizeof visit);

    //+- (a - b)  +-  (b - c)  +-  (c - d) ...
    ll res = dfs(0, 0, 0, 0);
    res = max(res, dfs(0, 0, 0, 1));
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

