
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
#define FOR(i, a, b) for (int i = a; i < b; ++i)

template <typename U, typename T, class Cmp>
ostream& operator <<(ostream& out, const map<U, T, Cmp>& a) {
  out << "{"; bool first = true;
  for (auto& p : a) { out << (first ? "" : ", "); out << p.first << ":" << p.second; first = 0;} out << "}";
  return out;
}

int l; 
ll r;

int cal(int L, int R) {
    int d = l / L;
    int ll = L, rr = R;
    if(l % R == 0) rr--;
    int p = -1;
    while(ll <= rr) {
        int mid = ll + (rr - ll) / 2;
        if((mid + 0ll) * d + 2 * mid <= r) {
            p = mid;
            ll = mid + 1;
        } else {
            rr = mid - 1;
        }
    }
    
    int cnt = 0;
    if(p != -1) {
        cnt = p - L + 1;
    }
    if(l % R == 0 && l + R <= r) {
        cnt++;
    }
    return cnt;
} 

void solve() {
    cin >> l >> r;
    ll res = max(0ll, r / 2 - l + 1);
    for(int j = 1; j < l; j++) {
        int L = j;
        int R = min((int)(l - 1), l / (l / L));
        res += cal(L, R);
        j = R;
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
