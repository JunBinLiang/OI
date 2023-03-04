#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <cstring>
#include <algorithm>

using namespace std;  
using ll = long long;
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define pb push_back
#define ve vector

const int N = 82;
int dp1[N][N];
int dp2[N][N][N];
int res = 0;

void lcs1(string& s, int l) {
    int n = l, m = s.size() - l;
    for(int i = 0; i <= n; i++) {
        for(int j = 0; j <= m; j++) {
            dp1[i][j] = 0;
        }
    }
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            if(s[i - 1] == s[l + j - 1]) {
                dp1[i][j] = 1 + dp1[i - 1][j - 1]; 
            } else {
                dp1[i][j] = max(dp1[i - 1][j], dp1[i][j - 1]);
            }
            res = max(res, dp1[i][j] * 2);
        }
    }
}

void lcs2(string& s, int x, int y) {
    int n = x, m = y - x, t = s.size() - n - m;
    for(int i = 0; i <= n; i++) {
        for(int j = 0; j <= m; j++) {
            for(int k = 0; k <= t; k++) {
                dp2[i][j][k] = 0;
            }
        }
    }

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            for(int k = 1; k <= t; k++) {
                if(s[i - 1] == s[x + j - 1] && s[i - 1] == s[y + k - 1]) {
                    dp2[i][j][k] = 1 + dp2[i - 1][j - 1][k - 1];
                } else {
                    dp2[i][j][k] = max(dp2[i-1][j][k], max(dp2[i][j][k-1], dp2[i][j-1][k]));
                }
                res = max(res, dp2[i][j][k] * 3);
            }
        }
    }

}

void match(string& s, string& t) {
    int cnt = 0, j = 0;
    int m = t.size();
    for(int i = 0; i < s.size(); i++) {
        if(s[i] == t[j]) j++;
        if(j >= t.size()) {
            j = 0;
            cnt++;
        }
    }
    
    if(cnt > 1) res = max(res, cnt * m);
}

void solve() {
    string s;
    cin >> s;
    int n = s.size();
    int m = n / 5;
    
    for(int i = 1; i < n; i++) {
        lcs1(s, i);
    }

    for(int i = 1; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            lcs2(s, i, j);
        }
    }
    
    if(m == 0) {
        cout << res << endl;
        return;
    }
    
    int l = 0;
    while(l < n) {
        int r = min(n - 1, l + m - 1);
        int sz = r - l + 1;
        for(int st = 0; st < (1 << sz); st++) {
            string t = "";
            for(int i = 0; i < sz; i++) {
                if(st & (1 << i)) {
                    t += s[l + i];
                }
            }
            match(s, t);
        }
        l += m;
    }
    
    int r = n - 1;
    while(r >= 0) {
        l = max(0, r - m + 1);
        int sz = r - l + 1;
        for(int st = 0; st < (1 << sz); st++) {
            string t = "";
            for(int i = 0; i < sz; i++) {
                if(st & (1 << i)) {
                    t += s[l + i];
                }
            }
            match(s, t);
        }
        r -= m;
    }
    
    cout << res << endl;
}
 

int main() {
    int t = 1;
    //cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
