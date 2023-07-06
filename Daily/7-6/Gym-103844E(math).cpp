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
using ull = unsigned long long;
#define pb push_back
#define vec vector
#define FOR(i, a, b) for (int i = a; i < b; ++i)
using namespace std;
 
template <typename T>
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} 
  out << "]";
  return out;
}


void solve() {
  ll L, R;
  cin >> L >> R;
  if(L == 1) {
      cout << 1 << endl;
      return;
  }
  
  if(L == R) {
    cout << -1 << endl;
    return;
  }

  ll d = R - L;
  ll k = (L - 1) / d;
  if((L - 1) % d != 0) k++;
  cout << L * k << endl;
}

int main() {
    int t = 1;
    //cin >> t;
    while(t--) {
      solve();
    }
    return 0;
}

