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
#include<fstream>


using namespace std;  
using ll = long long;
#define pb push_back

//ifstream fcin("test/input.txt");
//ofstream fcout("test/output.txt");


const int N = 2e5 + 10;
ll a[N];
int n;
void solve() {
    scanf("%d", &n);
    ll res = 0;
    ll mx = 0;
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        res += a[i];
        mx = max(mx, a[i]);
    }

    if(n >= 4) {
        cout << mx * n << endl;
        return;
    }

    if(n == 1) {
        cout << res << endl;
        return;
    }
    if(n == 2) {
        res = max(res, abs(a[1] - a[0]) * 2);
        cout << res << endl;
        return;
    }

    if(a[0] == mx || a[2] == mx) {
        cout << mx * n << endl;
        return;
    }

    res = max(res, a[0] * 3);
    res = max(res, a[2] * 3);
    res = max(res, a[0] + 2 * abs(a[1] - a[2]));
    res = max(res, a[2] + 2 * abs(a[0] - a[1]));
    res = max(res, 3 * abs(a[0] - a[1]));
    res = max(res, 3 * abs(a[2] - a[1]));
    cout << res << endl;
}

int main() {
	// your code goes here
	int t = 1;
	cin >> t;
	while(t--) {
	    solve();
	}
	return 0;
}

