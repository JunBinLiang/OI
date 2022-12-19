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



const int N = 505;
int a[N], b[N];
int dp[N][N];
int p[N][N][2];
int n, m;
void solve() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    scanf("%d", &m);
    for(int i = 1; i <= m; i++) {
        scanf("%d", &b[i]);
    }


    memset(dp, -1, sizeof dp);
    memset(p, -1, sizeof p);

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            if(a[i] == b[j]) {
                dp[i][j] = 1;
                for(int k = 1; k < j; k++) {
                    if(b[k] < b[j] && dp[i - 1][k] != -1) {
                        if(dp[i - 1][k] + 1 > dp[i][j]) {
                            dp[i][j] = dp[i - 1][k] + 1;
                            p[i][j][0] = i - 1;
                            p[i][j][1] = k; 
                        }
                    }
                }
            } else {
                dp[i][j] = dp[i - 1][j];
                p[i][j][0] = i - 1;
                p[i][j][1] = j;
            }
        }
    }

    int mx = 0;
    int x = -1, y = -1;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            if(dp[i][j] > mx) {
                mx = dp[i][j];
                x = i;
                y = j; 
            }
        }
    }
    
    /*for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            cout << dp[i][j] << "  ";
        } cout << endl;
    }*/

    vector<int> res;
    while(x != -1 && y != -1) {
        if(a[x] == b[y]) {
            res.push_back(b[y]);
        }
        int t1 = p[x][y][0], t2 = p[x][y][1];
        x = t1; y = t2;
    }
    reverse(res.begin(), res.end());

    cout << res.size() << endl;
    for(int i : res) cout << i << " ";
    cout << endl;
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
