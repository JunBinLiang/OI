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
const int N = 6000;
ll S[N], C[N];
ll dp[N];

ll get(ll p[], int l, int r) {
    if(l > r) return 0;
    if(l == 0) return p[r];
    return p[r] - p[l - 1];
}

int main() {
    int n, s;
    cin >> n >> s;
    for(int i = 0; i < n; i++) {
        int t, c;
        cin >> t >> c;
        S[i] = t, C[i] = c;
        if(i) {
            S[i] += S[i - 1];
            C[i] += C[i - 1];
        }
    }
    
    
    dp[0] = C[n - 1] * s + S[0] * C[0];
    for(int i = 1; i < n; i++) {
        ll mn = 1000000000000000000ll;
        for(int j = i; j >= 0; j--) {
            mn = min(mn, dp[j - 1] + get(C,j, i) * S[i] + get(C, j, n - 1)* s);
        }
        dp[i] = mn;
    }
    cout << dp[n - 1] << endl;
}
