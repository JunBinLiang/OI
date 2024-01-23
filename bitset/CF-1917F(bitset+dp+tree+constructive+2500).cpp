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
#define P pair
#define V vector
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define FFOR(i, a, b) for (int i = a; i <= b; ++i)

template <typename U, typename T, class Cmp>
ostream& operator <<(ostream& out, const map<U, T, Cmp>& a) {
  out << "{"; bool first = true;
  for (auto& p : a) { out << (first ? "" : ", "); out << p.first << ":" << p.second; first = 0;} out << "}";
  return out;
}

template <typename T>
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} 
  out << "]";
  return out;
}

const int N = 2010;
bitset<2001> b[N][2];

void solve() {
  int n, d;
  cin >> n >> d;
  vector<int> a(n);
  for(int i = 0; i < n; i++) cin >> a[i];

  sort(a.begin(), a.end());
  if(a[n - 1] + a[n - 2] > d) {
    cout << "No" << endl;
    return;
  }
  
  int best = a.back();
  vector<bool> dp(d + 1); //best is included
  dp[0] = true;
  for(int i = 0; i < n - 1; i++) {
    vector<bool> cur(d + 1);
    for(int j = a[i]; j <= d; j++) {
      if(dp[j - a[i]]) cur[j] = true;
    }
    for(int j = 0; j <= d; j++) {
      if(dp[j]) cur[j] = true;
    }
    swap(dp, cur);
  }
  if(dp[d - best]) {
    cout << "Yes" << endl;
    return;
  }


  for(int i = 0; i <= d; i++) b[i][0] = b[i][1] = 0;
  b[0][0] = 1;
  for(int i = 0; i < n; i++) {
    int x = a[i];
    for(int j = 0; j <= d; j++) b[j][1] = 0;
    for(int j = x; j <= d; j++) {
      b[j][1] |= (b[j - x][0] << x);
      b[j][1] |= (b[j - x][0]);
    }
    for(int j = 0; j <= d; j++) b[j][1] |= b[j][0];
    for(int j = 0; j <= d; j++) swap(b[j][0], b[j][1]);
  }

  string s = b[d][0].to_string();
  reverse(s.begin(), s.end());
  for(int i = 0; i <= d; i++) {
    if(best <= min(i, d - i) && s[i] == '1') {
      cout << "Yes" << endl;
      return;
    }
  }
  cout << "No" << endl;
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
