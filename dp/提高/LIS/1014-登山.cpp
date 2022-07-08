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

const int N = 1010;
int a[N];
int dp1[N];
int dp2[N];
void solve() {
    int n;
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    for(int i = 0; i < n; i++) {
        int mx = 0;
        for(int j = i - 1; j >= 0; j--) {
            if(a[i] > a[j]) mx = max(mx, dp1[j]);
        }
        dp1[i] = 1 + mx;
    }
    
    for(int i = n - 1; i >= 0; i--) {
        int mx = 0;
        for(int j = i + 1; j < n; j++) {
            if(a[i] > a[j]) mx = max(mx, dp2[j]);
        }
        dp2[i] = 1 + mx;
    }
    
    int res = 0;
    for(int i = 0; i < n; i++) {
        res = max(res, dp1[i]);
        res = max(res, dp2[i]);
        for(int j = i + 1; j < n; j++) {
            if(a[j] < a[i]) {
                res = max(res, dp1[i] + dp2[j]);
            }
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
}
