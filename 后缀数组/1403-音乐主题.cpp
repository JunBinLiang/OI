#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;  
using ll = long long;
using ull = unsigned long long;
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define pb push_back
#define ve vector
typedef pair<int, int> PII;
typedef pair<double, double> PDD;

const int N = 1010;
char s[N];
int sa[N], x[N], y[N], c[N], rk[N], height[N];
int n, m;

void SA() {
    memset(c, 0, sizeof c);
    
    for(int i = 1; i <= n; i++) c[x[i] = s[i]]++;
    for(int i = 1; i <= m; i++) c[i] += c[i - 1];
    for(int i = n; i >= 1; i--) sa[c[x[i]] -- ] = i;
    
    for (int k = 1; k <= n; k <<= 1) {
        int num = 0;
        for (int i = n - k + 1; i <= n; i++ ) y[++num] = i;
        for (int i = 1; i <= n; i ++ )
            if (sa[i] > k)
                y[ ++ num] = sa[i] - k; //第二关键字排序
                
        //第一关键字排序
        for (int i = 1; i <= m; i ++ ) c[i] = 0;
        for (int i = 1; i <= n; i ++ ) c[x[i]] ++ ;
        for (int i = 2; i <= m; i ++ ) c[i] += c[i - 1];
        for (int i = n; i; i -- ) sa[c[x[y[i]]] -- ] = y[i], y[i] = 0;
        swap(x, y);
        
        x[sa[1]] = 1, num = 1;
        for (int i = 2; i <= n; i ++ )
            x[sa[i]] = (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k]) ? num : ++ num;
        if (num == n) break;
        m = num;  
    }
    
}

void Height() {
    for (int i = 1; i <= n; i ++ ) rk[sa[i]] = i;
    for(int i = 1, k = 0; i <= n; i++) {
        if(rk[i] == 1) continue;
        if(k) k--;
        int j = sa[rk[i] - 1];
        while(i + k <= n && j + k <= n && s[i + k] == s[j + k]) k++;
        height[rk[i]] = k;
    }
}


void solve() {
    scanf("%s", s + 1);
     n = strlen(s + 1);
     m = 256;
     SA();
     Height();
     
     int res = n - sa[1] + 1;
     for(int i = 2; i <= n; i++) {
         res += (n - sa[i] + 1);
         res -= height[i];
     }
     
     cout << res << endl;
}

int main() {
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
