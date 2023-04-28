
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <queue>
#include <deque>

using namespace std;

using ll = long long;
#define pb push_back
#define ve vector



template <typename U, typename T, class Cmp>
ostream& operator <<(ostream& out, const map<U, T, Cmp>& a) {
  out << "{"; bool first = true;
  for (auto& p : a) { out << (first ? "" : ", "); out << p.first << ":" << p.second; first = 0;} out << "}";
  return out;
}

const int mod = 998244353;
int n, k;

void solve() {
    cin >> n >> k;
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }

    for(int i = n - 1; i >= n - k; i--) {
        if(a[i] != 0 && a[i] != -1) {
            cout << 0 << endl;
            return;
        }
        if(a[i] > i) {
            cout << 0 << endl;
            return;
        }
    }

    ll res = 1;
    for(int i = 1; i <= k; i++) {
        res *= i;
        res %= mod;
    }

    for(int i = 0; i < n - k; i++)  {
        if(a[i] == 0) {
            res *= (1 + k);
            res %= mod;
        } else if(a[i] == -1) {
            res *= ((i + 1 + k));
            res %= mod;
        }
    }


    cout << res << endl;


}


int main()
{   

    int t = 1;
    cin >> t;
    while(t --) {
        solve();
    }
    return 0;
}
