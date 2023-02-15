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
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define pb push_back
#define ve vector

//ifstream fcin("test/input.txt");
//ofstream fcout("test/output.txt");

const int N = 5010;
int n, mod;
ll p[N];
ll dp[N][N], pre[N][N];
ll S[N];
void add(ll& x, ll y) {
    x += y;
    x %= mod;
    if(x < 0) {
        x += mod;
    }
}

void solve() {
    cin >> n >> mod;
    
    p[0] = 1;
    for(int i = 1; i < N; i++) {
        add(p[i], 2 * p[i - 1]);
    }

    memset(dp, 0, sizeof dp);
    memset(pre, 0, sizeof pre);
    memset(S, 0, sizeof S);
    dp[1][1] = 1;
    pre[1][1] = 1;

    for(int i = 2; i <= n; i++) {
        dp[i][i] = p[i - 2];
        for(int j = 1; j < i; j++) {
            if(i - j - j - 1 > 0) {
                add(dp[i][j], ((dp[j][j] * S[i - j - j - 1]) % mod));
                add(dp[i][i], -dp[i][j]);
            }
        }

        for(int j = 1; j <= i; j++) {
            pre[i][j] = dp[i][j];
            add(pre[i][j], pre[i][j - 1]);
        }

        for(int j = i - 1; j >= 1; j--) {
            int zero = i - j;
            add(S[i], pre[j][min(j, zero)]);
        }
    }
    
    /*for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            cout << dp[i][j] << "  "; 
        } cout << endl;
    } cout << endl;
    
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            cout << pre[i][j] << "  "; 
        } cout << endl;
    } cout << endl;
    
    
    cout << endl;
    for(int i = 1; i < 8; i++) {
        cout << S[i] << " ";
    } cout << endl << endl;*/
    
    cout << dp[n][n] << endl;

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

