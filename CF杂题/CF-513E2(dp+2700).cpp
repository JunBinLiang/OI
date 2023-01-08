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

const int N = 3e4 + 5;
const ll INF = 10000000000000000ll;
int a[N];
int n, k;
ll dp[N][205][2][2][2];
bool visit[N][205][2][2][2];

ll dfs(int i, int j, int psign, int csign, int taking) {
    if(i >= n) {
        if(j == k) {
            return 0;
        }
        return -INF;
    }

    if(visit[i][j][psign][csign][taking]) {
        return dp[i][j][psign][csign][taking];
    }

    ll res = -INF;
    int m1 = 1, m2 = 1;
    if(psign == 1) m1 *= -1;
    if(csign == 1) m2 *= -1;
    //m1 : pre   m2 : cur

    if(taking == 0) {
        res = max(res, dfs(i + 1, j, psign, csign, 0));
        res = max(res, dfs(i + 1, j, psign, csign, 1));
    } else { //must take
        if(j < k) {
        int sum = a[i];
            if(j == 0 || j == k - 1) {
                if(j == 0) {
                    res = max(res, m2 * sum + dfs(i + 1, j, psign, csign, 1));
                    res = max(res, m2 * sum + dfs(i + 1, j + 1, csign, 0, 1));
                    res = max(res, m2 * sum + dfs(i + 1, j + 1, csign, 1, 1));
                    
                    res = max(res, m2 * sum + dfs(i + 1, j + 1, csign, 0, 0));
                    res = max(res, m2 * sum + dfs(i + 1, j + 1, csign, 1, 0));
                    
                }
                else {
                    res = max(res, (-sum) * m1 + dfs(i + 1, j, psign, csign, 1));
                    res = max(res, (-sum) * m1 + dfs(i + 1, j + 1, csign, 0, 1));
                    res = max(res, (-sum) * m1 + dfs(i + 1, j + 1, csign, 1, 1));
                   
                    res = max(res, (-sum) * m1 + dfs(i + 1, j + 1, csign, 0, 0));
                    res = max(res, (-sum) * m1 + dfs(i + 1, j + 1, csign, 1, 0));
                }
            } else {
                    res = max(res, (m1) * (-sum) + (m2) * (sum) + dfs(i + 1, j, psign, csign, 1));
                    res = max(res, (m1) * (-sum) + (m2) * (sum) + dfs(i + 1, j + 1, csign, 0, 1));
                    res = max(res, (m1) * (-sum) + (m2) * (sum) + dfs(i + 1, j + 1, csign, 1, 1));
                   
                    res = max(res, (m1) * (-sum) + (m2) * (sum) + dfs(i + 1, j + 1, csign, 0, 0));
                    res = max(res, (m1) * (-sum) + (m2) * (sum) + dfs(i + 1, j + 1, csign, 1, 0));
                    
                    res = max(res, (m1) * (-sum) + (m2) * (sum) + dfs(i + 1, j + 1, csign, 0, 0));
                    res = max(res, (m1) * (-sum) + (m2) * (sum) + dfs(i + 1, j + 1, csign, 1, 0));
            }
        }
    }

    visit[i][j][psign][csign][taking] = true;
    return dp[i][j][psign][csign][taking] = res;
}

void solve() {
    scanf("%d%d", &n, &k);
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    memset(visit, false, sizeof visit);
    //+- (a - b)  +-  (b - c)  +-  (c - d) ...
    ll res = 0;
    for(int i = 0; i < n; i++) {
        res = max(res, dfs(i, 0, 0, 0, 1));
        res = max(res, dfs(i, 0, 0, 1, 1));
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

