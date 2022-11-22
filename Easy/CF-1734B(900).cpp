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


void solve() {
    int n;
    cin >> n;
    int cnt1 = 0, cnt2 = 0;
    while(n % 2 == 0) n /= 2, cnt1++;
    while(n % 3 == 0) n /= 3, cnt2++;
    if(n != 1 || cnt1 > cnt2) {
        cout << -1 << endl;
        return;
    }
    cout << (cnt2 - cnt1) + cnt2 << endl;
}  

int main() {
    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
