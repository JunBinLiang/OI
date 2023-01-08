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
ll dp[20][2][5];
ll dfs(string& s, int i, int sa, int cnt) {
    if(i >= s.size()) {
        if(cnt <= 3) {
            return 1;
        }
        return 0;
    }
    if(dp[i][sa][cnt] != -1) {
        return dp[i][sa][cnt];
    }
    
    ll res = 0;
    int d = s[i] - '0';
    if(sa == 1) {
        if(d == 0) {
            res += dfs(s, i + 1, 1, cnt);
        } else {
            if(1 + cnt <= 3) {
                res += dfs(s, i + 1, 1, cnt + 1);
                res += dfs(s, i + 1, 0, cnt + 1) * (d - 1);
            }
            if(i) res += dfs(s, i + 1, 0, cnt);
        }
        
    } else {
        res += dfs(s, i + 1, 0, cnt); //place 0
        if(1 + cnt <= 3) {
            res += dfs(s, i + 1, 0, cnt + 1) * 9; //0 - 9
        }
    }
    return dp[i][sa][cnt] = res;
}

ll get(ll n) {
    if(n == 0) return 0;
    ll res = 0;
    string s = to_string(n);
    memset(dp, -1, sizeof dp);
    res += dfs(s, 0, 1, 0);
    
    for(int i = 1; i < s.size(); i++) {
        res += (9);
        int x = i - 1;
        ll w1 = (x) * (x - 1) / 2;
        if(i >= 2) {
            res +=  x * 81;
        }
        if(i >= 3) {
            res += w1 * (81 * 9);
        }
    }

    return res;
}

void solve() {
    ll l, r;
    cin >> l >> r;
    cout << get(r) - get(l - 1) << endl;
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
 
