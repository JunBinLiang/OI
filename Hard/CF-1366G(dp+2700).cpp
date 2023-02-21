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

const int N = 1e4 + 5, INF = 1e9;
int dp[N][N];
int to[N];

int dfs(string& s, string& t, int i, int j) {
    if(i >= s.size()) {
        if(j >= t.size()) {
            return 0;
        }
        return INF;
    }
    if(dp[i][j] != -1) {
        return dp[i][j];
    }
    int res = INF;
    //skip
    res = min(res, 1 + dfs(s, t, i + 1, j));
    if(j >= t.size()) {
        if(to[i] != -1) {
            res = min(res, dfs(s, t, to[i] + 1, j));
        }
        if(s[i] == '.') {
            res = min(res, dfs(s, t, i + 1, j - 1));
        }
    } else {
        if(s[i] == t[j]) {
            res = min(res, dfs(s, t, i + 1, j + 1));
        } else {
            if(s[i] == '.') {
                if(j > 0) {
                    res = min(res, dfs(s, t, i + 1, j - 1));
                }
            } else {
                if(to[i] != -1) {
                    res = min(res, dfs(s, t, to[i] + 1, j));
                }
            }
        }
    }

    
    return dp[i][j] = res;
}

void solve() {
    memset(dp, -1, sizeof dp);
    
    string s, t;
    cin >> s >> t;
    int n = s.size(), m = t.size();
    
    for(int i = 0; i < n; i++) {
        int o = 0;
        to[i] = -1;
        for(int j = i; j < n; j++) {
            if(s[j] == '.') o--;
            else o++;
            if(o == 0) {
                to[i] = j; 
                break;
            } else if(o < 0) {
                break;
            }
        }
    }

    int res = dfs(s, t, 0, 0);
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
