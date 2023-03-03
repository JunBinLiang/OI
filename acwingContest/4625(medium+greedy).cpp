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




void solve() {
    int n, m;
    cin >> n >> m;
    ll sum = 0;
    vector<int> d;
    for(int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        sum += a;
        d.push_back(a - b);
    }

    int res = 0;
    sort(d.begin(), d.end());
    while(d.size() > 0 && sum > m) {
        sum -= d.back();
        res++; 
        d.pop_back();
    }
    
    if(sum > m) {
        cout << -1 << endl;
        return;
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
