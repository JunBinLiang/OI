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
#include <bitset>

using namespace std;  
using ll = long long;
using ull = unsigned long long;
#define pb push_back

//ifstream fcin("test/input.txt");
//ofstream fcout("test/output.txt");



const int N = 1e5 + 10;
void solve() {
    int n;
    cin >> n;
    vector<int> a(2 * n + 1);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }

    bitset<200000 + 5> dp;
    dp[0] = 1;
    ll res = 0, sum = 0, to = 0;
    for(int i = 0; i < a.size(); i++) {
        sum += a[i];
        if(dp[i]) {
            res = max(res, sum - i);
        }

        if(i <= to) {
            to += a[i];
            dp |= (dp << a[i]);
            dp[i] = 0;
        }

    }
    cout << res << endl;
}

int main()
{
    int t = 1;
    //cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
