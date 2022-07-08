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
void solve() {
    int n; int res = 0;
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    for(int i = 0; i < n; i++) {
        int mx = 0;
        for(int j = i - 1; j >= 0; j--) {
            if(a[i] > a[j]) mx = max(mx, dp1[j]);
        }
        dp1[i] = a[i] + mx;
        res = max(res, dp1[i]);
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
