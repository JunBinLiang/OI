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


/*
公式 : 
dp[i] = dp[j] + s * (C[N] - C[j]) + T[i] * (C[i] - C[j])

dp[i] = dp[j] + s * C[N] - s * C[j] + T[i] * C[i] - T[i] * C[j]

dp[j] = (T[i] + s) * C[j] + dp[i] - s * C[N] - T[i] * C[i]


dp[j] = ((T[i] + s) * C[j])     +     (dp[i] - s * C[N] - T[i] * C[i]) 


模型 ：y = mx + b
(dp[j], C[j]) => (y, x)   系数越小，dp[i] 越小  
系数越小，维护下凸包

//
*/
const int N = 3e5 + 100;
ll C[N], T[N], dp[N];
int q[N];

ll up(int x1, int x2) {
    return dp[x1] - dp[x2];
}

ll down(int x1, int x2) {
    return C[x1] - C[x2];
}

int main() {
    int n, s;
    scanf("%d%d", &n, &s);
    C[0] = T[0] = 0;
    for(int i = 1; i <= n; i++) {
        int t, c;
        scanf("%d%d", &t, &c);
        C[i] = c, T[i] = t;
        C[i] += C[i - 1], T[i] += T[i - 1];
    }
    
    int hh = 0, tt = 1;
    q[0] = 0;
    dp[0] = 0;
    
    for(int i = 1; i <= n; i++) {
        while(tt - hh > 1 && up(q[hh + 1], q[hh]) <= (T[i] + s) * down(q[hh + 1], q[hh]) ) {
            hh++;
        }
        
        int j = q[hh];
        dp[i] = dp[j] + s * (C[n] - C[j]) + T[i] * (C[i] - C[j]);
        
        while(tt - hh > 1 && up(q[tt-1], i) * down(q[tt-2], q[tt-1]) <= up(q[tt-2], q[tt-1])* down(q[tt-1], i)) {
            tt--;
        }
        q[tt++] = i;
    }
    
    cout << dp[n] << endl;
}
