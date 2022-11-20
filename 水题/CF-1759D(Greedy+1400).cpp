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
    ll n, m;
    cin >> n >> m;
    int cnt1 = 0, cnt2 = 0, v = n;
    while(v % 2 == 0) cnt1++, v /= 2;
    while(v % 5 == 0) cnt2++, v /= 5;

    if(cnt1 == cnt2) {
        if(m >= 10) {
            ll x = 1;
            while(true) {
                if(x * 10 > m) break;
                x *= 10;
            }
            cout << n * x * (m / x) << endl;
        } else {
            cout << n * m << endl;
        }
    } else if(cnt1 > cnt2) {
        //more 2
        if(m < 5) {
            cout << n * m << endl;
        } else {
            ll x = 1;
            while(cnt1 > cnt2) {
                if(x * 5 > m) break;
                x *= 5;
                cnt1--;
            }
            while(true) {
                if(x * 10 > m) break;
                x *= 10;
            }
            cout << n * x * (m / x) << endl;
        }

    } else {
        //more 5
        if(m < 2) {
            cout << n * m << endl;
        } else {
            ll x = 1;
            while(cnt2 > cnt1) {
                if(x * 2 > m) break;
                x *= 2;
                cnt2--;
            }
            while(true) {
                if(x * 10 > m) break;
                x *= 10;
            }
            cout << n * x * (m / x) << endl;
        }
    }


}

int main() {
    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
