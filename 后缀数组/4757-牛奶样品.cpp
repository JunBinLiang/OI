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

const int N = 20000 + 10;
int s[N];
int sa[N], x[N], y[N], c[1000100], rk[N], height[N];
int n, m, K;

void SA() {
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
    scanf("%d%d", &n, &K);
    for(int i = 1; i <= n; i++) {
        scanf("%d", &s[i]);
    }
    
    m = 1e6 + 5;
    SA();
    Height();
    
    
    int res = 0;
    int l = 1, r = n;
    int h[N];
    /*for(int i = 1; i <= n; i++) {
        cout << height[i] << " ";
    } cout << endl;*/
    
    while(l <= r) {
        int mid = l + (r - l) / 2;
        for(int i = 1; i <= n; i++) {
            if(height[i] >= mid) {
                h[i] = 1;
            } else {
                h[i] = 0;
            }
        }
        
        /*cout << "mid  " << mid << endl;
        for(int i = 1; i <= n; i++) cout << h[i] << " ";
        cout << endl;*/
        
        int tot = 0;
        int sum = 0;
        int mx = 0;
        for(int i = 1; i <= n; i++) {
            if(h[i] == 0) {
                sum = 0;
            }
            else {
                sum++;
                mx = max(mx, sum + 1);
            }
        }
        
        if(mx >= K) {
            res = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
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
