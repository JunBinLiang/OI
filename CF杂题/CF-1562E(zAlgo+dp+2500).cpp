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

vector<int> z(string s) {
    int n = (int) s.length();
    vector<int> z(n);
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r)
            z[i] = min (r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            ++z[i];
        if (i + z[i] - 1 > r)
            l = i, r = i + z[i] - 1;
    }
    return z;
}

const int N = 5010;
int lcp[N][N];
int dp[N];
void solve() {
    int n;
    string s;
    cin >> n >> s;
    int res = 0;
    
    for(int i = 0; i < n; i++) {
        string sub = s.substr(i, n - i);
        vector<int> p = z(sub);
        for(int j = 0; j < p.size(); j++) {
            lcp[i][i + j] = p[j];
        }
    }
    
    memset(dp, 0, sizeof dp);
    dp[0] = n;
    for(int i = 1; i < n; i++) {
        int mx = n - i;
        for(int j = i - 1; j >= 0; j--) {
            if(s[i] < s[j]) continue;
            if(s[i] == s[j]) {
                int com = lcp[j][i];
                if(i + com < n && s[i + com] > s[j + com]) {
                    mx = max(mx, dp[j] + (n - i) - com);
                }

            } else {
                mx = max(mx, dp[j] + (n - i));
            }
        }
        dp[i] = mx;
    }
    
    for(int i = 0; i < n; i++) res = max(res, dp[i]);
    
    /*for(int i = 0; i < n; i++) {
        cout << dp[i] << "  ";
    }
    cout << endl;*/

    printf("%d\n", res);
}

int main() {
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
