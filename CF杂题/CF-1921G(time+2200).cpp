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


vector<string> rotate(vector<string>& a) {
  int n = a.size(), m = a[0].size();
  vector<string> b(m, "");
  for(int i = 0; i < m; i++) {
    for(int j = 0; j < n; j++) {
      b[i] += " ";
    }
  }
  for(int i = 0; i < n; i++) {
    for(int j= 0; j < m; j++) {
      b[j][n - i - 1] = a[i][j];
    }
  }
  return b;
}

int get(vector<int>& p, int l, int r) {
  return l == 0 ? p[r] : p[r] - p[l - 1];
}


void solve() {
  int n, m, k;
  cin >> n >> m >> k;
  vector<string> a;
  k++;
  for(int i = 0; i < n; i++) {
    string s;
    cin >> s;
    a.push_back(s);
  }

  if(n > m) {
    a = rotate(a);
    swap(n, m);
  }

  vector<vector<int>> p(n, vector<int>(m, 0));
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < m; j++) {
      if(a[i][j] == '#') p[i][j] = 1;
      if(j) p[i][j] += p[i][j - 1];
    }
  }
  
  /*for(int i = 0; i < n; i++) {
      for(int j = 0; j < m; j++) {
          cout << p[i][j] << " ";
      }cout << endl;
  }
  cout << endl;*/

  int res = 0;
  for(int r = 0; r < n; r++) {
    for(int c = 0; c < m; c++) {
      int row = r, sum1 = 0, sum2 = 0;
      for(int i = k; i >= 1 && row >= 0; i--) {
        sum1 += get(p[row], c, min(m - 1, c + i - 1));
        sum2 += get(p[row], max(0, c - i + 1), c);
        row--;
      }
      res = max(res, sum1);
      res = max(res, sum2);
      row = r; sum1 = 0; sum2 = 0;
      for(int i = k; i >= 1 && row < n; i--) {
        sum1 += get(p[row], c, min(m - 1, c + i - 1));
        sum2 += get(p[row], max(0, c - i + 1), c);
        row++;
      }
      res = max(res, sum1);
      res = max(res, sum2);
    }
  }
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

/*
1
3 7 2
.#.....
..####.
.##.##.
*/
