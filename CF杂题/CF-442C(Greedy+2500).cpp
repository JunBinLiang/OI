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
#define ve vector
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define RFOR(i, a, b) for (int i = a; i >= b; i--)
#define f first
#define se second
#define W while
#define um unordered_map
#define us unordered_set
#define be begin
#define en end

template <typename T>
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} 
  out << "]";
  return out;
}

const int N = 5e5 + 10;
int n;
int a[N];
ll res = 0;
void solve() {
    scanf("%d", &n);
    for(int i = 0; i < n; i++) scanf("%d", &a[i]);
    
    vector<int> stk;
    for(int i = 0; i < n; i++) {
        while(stk.size() > 1 && stk.back() <= a[i] && stk.back() <= stk[stk.size() - 2]) {
            stk.pop_back();
            res += min(stk.back(), a[i]);
        } 
        stk.pb(a[i]);
    }

    sort(stk.begin(), stk.end());
    for(int i = 0; i < (int)(stk.size()) - 2; i++) res += stk[i];
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
