
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


const int N = 1e6 + 10;
vector<int> pri[N];
bool isp[N];
void init() {
  memset(isp, false, sizeof isp);
  for(int i = 2; i < N; i++) {
    if(isp[i]) continue;
    for(int j = i; j < N; j += i) {
      pri[j].push_back(i);
      isp[j] = true;
    }
  }
}


void solve() {
  int m;
  cin >> m;
  auto& p = pri[m];

  int n = p.size();
  ll sum = 0;
  
  for(int st = 1; st < (1 << n); st++) {
    int x = 1, mul = -1;
    for(int i = 0; i < n; i++) {
      if(st & (1 << i)) {
        x *= p[i];
        mul *= -1;
      }
    }
    sum += (mul * (m / x));
  }
  cout << (m - sum) * (m - 1) << endl;

} 

int main()
{   
    init();
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
