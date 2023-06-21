
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

void solve() {
  int n;
  vector<int> a;
  cin >> n;
  for(int i = 0; i < n; i++) {
    int x;
    cin >> x;
    a.push_back(x);
  }
  sort(a.begin(), a.end());
  int an = a[0];
  for(int x : a) an = an & x;
  
  bool find = false;
  for(int x : a) {
    if(an == x) find = true;
  }

  if(!find) {
    cout << -1 << endl;
    return;
  }

  vector<int> res;
  for(int i = 0; i < a.size(); i++) {
    res.push_back(an);
    res.push_back(a[i]);
    res.push_back(an);
  }

  cout << res.size() << endl;
  for(int x : res) cout << x << " ";
  cout << endl;

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
