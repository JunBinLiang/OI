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

const int N = 1000 + 5;
ll dp[N][N * 2][4];
const int mod = 998244353;
void solve() {
    int n, k;
    cin >> n >> k;

    memset(dp, 0, sizeof dp);
    //0: black   1:white
    dp[1][1][0] = 1; 
    dp[1][2][1] = 1;
    dp[1][2][2] = 1;
    dp[1][1][3] = 1;

    for(int i = 2; i <= n; i++) {
        for(int j = 1; j <= k; j++) {
            dp[i][j][0] = dp[i - 1][j][0] + dp[i - 1][j][1] + dp[i - 1][j][2] + dp[i - 1][j - 1][3];
            

            dp[i][j][1] = dp[i - 1][j - 1][0] + dp[i - 1][j][1] + (j >= 2 ? dp[i - 1][j - 2][2] : 0) + dp[i - 1][j - 1][3];
            
            dp[i][j][2] = dp[i - 1][j - 1][0] + (j >= 2 ? dp[i - 1][j - 2][1] : 0) + dp[i - 1][j][2] + dp[i - 1][j - 1][3];
            
            dp[i][j][3] = dp[i - 1][j][0] + dp[i - 1][j][1] + dp[i - 1][j][2] + dp[i - 1][j - 1][3];

            dp[i][j][0] %= mod;
            dp[i][j][1] %= mod;
            dp[i][j][2] %= mod;
            dp[i][j][3] %= mod;

        }
    }

    ll res = 0;
    res += dp[n][k][0];
    res += dp[n][k][1];
    res += dp[n][k][2];
    res += dp[n][k][3];
    res %= mod;
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

