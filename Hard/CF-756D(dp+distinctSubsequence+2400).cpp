#include<iostream>
#include<string>
#include<cstring>
#include<vector>

using namespace std;

int n;
string s;
const int N = 5050, mod = 1e9 + 7;
int C[N][N];
void init() {
    C[0][0] = 1;
    for(int i = 1;i < N; i++) {
      C[i][0]=1;
      for(int j = 1;j <= i;j++) {
        C[i][j] = ( C[i-1][j] + C[i-1][j-1] ) % mod;
      }
    }
}

//C(n - 1, m -1)
long long dp[N][2][26];
long long sums[N];
long long res = 0;
void solve() {
    init();
    cin >> n >> s;
    
    memset(dp, 0, sizeof dp);
    vector<int> a;
    for(char& c : s) {
        if(a.size() && c - 'a' == a.back()) continue;
        a.push_back(c - 'a');
    }
    
    /*for(int x : a) cout << x << " ";
    cout << endl;*/
    
    memset(sums, 0, sizeof sums);
    for(int i = 0; i < a.size(); i++) {
        dp[1][1][a[i]] = 1;
        for(int len = 2; len <= i + 1; len++) {
            dp[len][1][a[i]] = (sums[len - 1] - dp[len - 1][0][a[i]]);
            dp[len][1][a[i]] %= mod;
            if(dp[len][1][a[i]] < 0) dp[len][1][a[i]] += mod;
        }
        
        for(int len = 1; len <= i + 1; len++) {
            sums[len] += (dp[len][1][a[i]] - dp[len][0][a[i]]);
            sums[len] %= mod;
            if(sums[len] < 0) sums[len] += mod;
        }
        
        for(int len = 1; len <= i + 1; len++) {
            dp[len][0][a[i]] = dp[len][1][a[i]];
        }
    }
    
    for(int len = 1; len <= a.size(); len++) {
        for(int j = 0; j < 26; j++) {
            res += dp[len][0][j] * C[n - 1][len - 1];
            res %= mod;
        }
    }
    
    
    cout << res << endl;
}

//1  10   101
//01  0

int main() {
    solve();
    return 0;
}
