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

string o(int x, char c) {
  if(x < 0) return "";
  string s = "";
  while(x--) s += c;
  return s;
}

void solve() {
  int a, b, c;
  cin >> a >> b >> c;
  
  if(a == 0) {
      if(c != 0) {
          cout << -1 << endl;
          return;
      }
      cout << o(b, '0') << endl;
      cout << o(b, '0') << endl;
      return;
  }
  
  if(b == 0) {
      if(c != 0) {
          cout << -1 << endl;
          return;
      }
      cout << o(a, '1') << endl;
      cout << o(a, '1') << endl;
      return;
  }
  
  if(c == 0) {
    string s = "";
    FOR(i, 0, a) s += "1";
    FOR(i, 0, b) s += "0";
    cout << s << endl;
    cout << s << endl;
    return;
  }

  if(c >= a + b) {
    cout << -1 << endl;
    return;
  }

  if(c <= b) {
    string t = o(a - 1, '1') + o(b, '0') + "1";
    string s = o(a - 1, '1');
    while(b > c) {
      b--;
      s += "0";
    }
    s += "1";
    s += o(b, '0');
    cout << s << endl;
    cout << t << endl;
    return;
  }

  string s = o(a, '1') + o(b, '0');
  string t = "";
  t += "1"; a--;
  t += o(b - 1, '0');
  c -= b;
  while(c--) {
    t += '1';
  }
  t += '0';
  while(t.size() != s.size()) t += "1";
  reverse(t.begin(), t.end());
  cout << s << endl;
  cout << t << endl;

}

int main() {
    int t = 1;
    //cin >> t;
    while(t--) {
      solve();
    }
    return 0;
}

