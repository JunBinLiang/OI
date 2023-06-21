
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

using ll = long long;
#define pb push_back
#define ve vector
#define FOR(i, a, b) for (int i = a; i < b; ++i)
using namespace std;

template <typename T>
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} 
  out << "]";
  return out;
}


const int MOD = 1e9 + 7;
ll po(int x, int t) {
  ll res = 1;
  while(t--) {
    res *= x;
    res %= MOD;
  }
  return res;
}

void solve() {
  int n;
  cin >> n;
  cout << po(2, 2 * n * n - 2) << endl;
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

/*

x  x  x

x  x  x

*/

//(n * n)  (n - 1) * (n + 1) = 2 * n ^ 2 - 1

//64 / 4 = 16
