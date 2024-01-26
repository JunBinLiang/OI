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

int n, a, b, c;
string s;
ll cal(vector<pair<int, int>> v, int one, int zero, int endzero, int x) {
  ll res = 0;
  int i = 0;
  while(true) {
    if(x % 2 == 0) { //0 
      if(b > c && (zero > 0)) {
        zero--;
        one++;
        res -= c;
      } else {
        if(i < v.size()) {
          v[i].second--;
          if(v[i].second== 0) {
            if(v[i].first == 0) zero++;
            else endzero++;
            i++; 
          }
          res += a;
        } else {
          if(endzero > 0 && one > 0 && b > c) {
              endzero--;
              res -= c;
          } else {
              break;
          }
        }
      }
    } else { //1
      if(one > 0) {
        one--;
        res += b;
      } else {
        break;
      }
    }
    x++;
  }
  return res;
}

void solve() {
  cin >> n >> a >> b >> c >> s;
  ll res = 0;
  int one = 0, zero = 0, endzero = 0;
  vector<pair<int, int>> v;
  for(int i = 0; i < n; i++) {
    int j = i;
    int cnt = 0;
    while(j < n && s[i] == s[j]) {
      cnt++;
      j++;
    }
    if(s[i] == '0') {
      if(cnt == 1) {
        if(i != 0 && j != n) {
          zero++;
        } else {
          endzero++;
        }
        i = j - 1;
        continue;
      }
      if(i == 0 || j == n) {
        v.push_back({1, cnt - 1});
      } else {
        v.push_back({0, cnt - 1});
      }
    } else {
      one += (cnt - 1);
    }
    i = j - 1;
  }
  
  //for(auto p : v) cout << p.first << "  " << p.second << endl;
  //cout << one << " " << zero << endl;

  sort(v.begin(), v.end());
  res = max(cal(v,one, zero, endzero, 0), cal(v, one, zero, endzero, 1));
  cout << res << endl;
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
