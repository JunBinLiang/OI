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

//定理 : 对一个无向图G,若它不连通,则关于完全图的补图连通. 相反的类似.
const int mod = 998244353;
const int N = 5010;
ll dp[N];
ll C[N][N];
void solve() {
    int n;
    cin >> n;
    
    C[0][0] = 1;
    for(int i = 1; i < N; i++) {
        C[i][0]=1;
        for(int j = 1; j <= i;j++) {
            C[i][j] = (C[i-1][j] + C[i-1][j-1]) % mod;
        }
    }

    dp[1] = dp[2] = 1;
    for(int i = 3; i <= n; i++) {
        for(int j = 1; j < i; j++) {
            int mul = 2;
            if(i - j == 1) mul = 1;
            dp[i] += (dp[j] * (dp[i - j] * mul) % mod) * (C[i - 1][j - 1]);
            dp[i] %= mod;
        }
    }
    cout << ((dp[n] - 1) * 2) % mod << endl;
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
