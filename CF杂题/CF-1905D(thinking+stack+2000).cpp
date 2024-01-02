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


//2:08
const int N = 1e6 + 10;
int p[N];
void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    int index = -1;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        if(a[i] == 0) index = i;
    }

    vector<int> b(n);
    for(int i = 0; i < n; i++) {
        b[i] = a[(i + index + 1) % n];
    }




    vector<pair<int, int>> stk;
    ll sum = 0, res = 0;

    for(int i = 0; i < n - 1; i ++) {
        int count = 1;
        while(stk.size() > 0 && b[i] < stk.back().first) {
            count += stk.back().second;
            sum -= ((stk.back().first + 0ll) * stk.back().second);
            stk.pop_back();
        }
        sum += ((count + 0ll) * b[i]);
        res = max(res, sum);
        stk.push_back({b[i], count});
    }

    cout << res + n << endl;
}

int main()
{

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
