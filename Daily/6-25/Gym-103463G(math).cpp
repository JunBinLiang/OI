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

ull fpow(int x, int t) {
  ull res = 1;
  while(t--)res *= x;
  return res;
}


void solve() {
  int m, x;
  cin >> m >> x;

  if(m == 1) {
    cout << x + 1 << endl;
    return;
  }
  
  if(x == 2) {
      ull t = 3;
      for(int i = 0; i < m - 1; i++) {
        t *= 2;
        t += 1;
      }
      cout << t << endl;
      return;
  }

  ull xp = fpow(x, m);
  cout << xp - (x - 1) << endl;
  
  /*ull t = xp - (x - 1);
  for(int i = 0; i < m; i++) {
      t = (t - 1);
      if(t % x != 0 || t == 0) {
          cout <<"gg " << m <<"  " << x <<"  " << i << endl;
          return;
      }
      t /= x;
      t *= (x - 1);
      cout << i << " " << t << endl;
  }*/
}

int main()
{
    int t = 1;
    while(t--) {
      solve();
    }
    
    //testing
    /*for(int m = 1; m <= 15; m++) {
        for(int x = 2; x <= 15; x++) {
            solve(m, x);
        }
    }*/
    
    return 0;
}
