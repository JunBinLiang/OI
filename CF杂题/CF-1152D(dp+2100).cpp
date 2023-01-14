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


const int N = 1005;
const int mod = 1e9 + 7;
ll dp[N][N][2];
int n;
ll dfs(int o, int c, int t) { //0:first taken node  1:second taken node
    if(o == n && c == n) {
        return 0;
    }
    if(dp[o][c][t] != -1) {
        return dp[o][c][t];
    }

    ll res = 0;
    int add = 0;
    if(c + 1 <= o) {
        if(t == 0) {
            add = 1;
            res += dfs(o, c + 1, 1);
        } else {
            res += dfs(o, c + 1, 0);
        }
    }

    if(o + 1 <= n) {
        if(t == 0) {
            if(add == 0) {
                add = 1; 
                res += dfs(o + 1, c, 1);
            } else {
                res += dfs(o + 1, c, 0);
            }
        } else {
           res += dfs(o + 1, c, 0);
        }
    }
    
    res += add;
    res %= mod;  
    return dp[o][c][t] = res;
}

void solve() {
    cin >> n;
    memset(dp, -1, sizeof dp);
    ll res = dfs(1, 0, 0);
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
