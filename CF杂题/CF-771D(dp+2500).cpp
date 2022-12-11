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


using namespace std;  
using ll = long long;
#define pb push_back

const int N = 77;
const int INF = 1e5;
int dp[N][N][N][3];

int dfs(string& s, int zero, int one, int x, int last) {
    if(zero + one + x >= s.size()) {
        return 0;
    }
    if(dp[zero][one][x][last] != -1) {
        return dp[zero][one][x][last];
    }

    int res = INF;
    int a = 0, b = 0, c = 0;
        for(int i = 0; i < s.size(); i++) {
            if(s[i] == '0') {
                a++;
                if(a > zero) {
                    break;
                }
            } else if(s[i] == '1') {
                b++;
            } else {
                c++;
            }
        }

        if(a > zero) {
            res = min(res, max(0, (b - one)) + max(0, (c - x)) + dfs(s, zero + 1, one, x, 0));
        }

        a = 0; b = 0; c = 0;
        for(int i = 0; i < s.size(); i++) {
            if(s[i] == '0') {
                a++;
            } else if(s[i] == '1') {
                b++;
            } else {
                c++;
                if(c > x) break;
            }
        }
        if(c > x) {
            res = min(res, max(0, (a - zero)) + max(0, (b - one)) + dfs(s, zero, one, x + 1, 2));
        }

    if(last == 0) { //can not add 1
    } else {
        a = 0; b = 0; c = 0;
        for(int i = 0; i < s.size(); i++) {
            if(s[i] == '0') {
                a++;
            } else if(s[i] == '1') {
                b++;
                if(b > one) break;
            } else {
                c++;
            }
        }
        if(b > one) {
            res = min(res, max(0, (a - zero)) + max(0, (c - x)) + dfs(s, zero, one + 1, x, 1));
        }
    }
    return dp[zero][one][x][last] = res;
}

void solve() {
    int n;
    string s;
    cin >> n >> s;
    for(int i = 0; i < n; i++) {
        if(s[i] == 'V') {
            s[i] = '0';
        } else if(s[i] == 'K') {
            s[i] = '1';
        } else {
            s[i] = 'x';
        }
    }

    memset(dp, -1, sizeof dp);
    int res = dfs(s, 0, 0, 0, 2);
    cout << res << endl;
}

int main() {
    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
