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

// Some predefined templates
template <typename T>
ostream &operator<<(ostream &out, const vector<T> &a)
{
  out << "[";
  bool first = true;
  for (auto v : a)
  {
    out << (first ? "" : ", ");
    out << v;
    first = 0;
  }
  out << "]";
  return out;
}

template <typename T>
ostream &operator<<(ostream &out, const unordered_set<T> &a)
{
  out << "[";
  bool first = true;
  for (auto v : a)
  {
    out << (first ? "" : ", ");
    out << v;
    first = 0;
  }
  out << "]";
  return out;
}

template <typename T>
ostream &operator<<(ostream &out, const set<T> &a)
{
  out << "[";
  bool first = true;
  for (auto v : a)
  {
    out << (first ? "" : ", ");
    out << v;
    first = 0;
  }
  out << "]";
  return out;
}

template <typename U, typename T, class Cmp>
ostream &operator<<(ostream &out, const map<U, T, Cmp> &a)
{
  out << "{";
  bool first = true;
  for (auto &p : a)
  {
    out << (first ? "" : ", ");
    out << p.first << ":" << p.second;
    first = 0;
  }
  out << "}";
  return out;
}

template <typename U, typename T, class Cmp>
ostream &operator<<(ostream &out, const unordered_map<U, T, Cmp> &a)
{
  out << "{";
  bool first = true;
  for (auto &p : a)
  {
    out << (first ? "" : ", ");
    out << p.first << ":" << p.second;
    first = 0;
  }
  out << "}";
  return out;
}


ll gcd(ll x, ll y)
{
  return (y == 0 ? x : gcd(y, x % y));
}
ll lcm(ll x, ll y)
{
  return x * y / gcd(x, y);
}

int to_int(string &s)
{
  int res = 0;
  for (char c : s)
  {
    res = res * 10 + (c - '0');
  }
  return res;
}

string substring(string& s, int l, int r) {
  string res = "";
  for(int i = l; i <= r; i++) res += s[i];
  return res;
}

/*class Compare
{
public:
    bool operator() (pair<int, int>& a, pair<int, int>& b)
    {
        return a.first > b.first;
    }
    //a[0] > b[0] : min
};*/


struct Tuple {
  int l, r, idx;
};

bool COMP(pair<int, int>& p1, pair<int, int>& p2) {
  return p1.first < p2.first;
}

bool same(int x1, int y1, int x2, int y2) {
  return x1 == x2 && y1 == y2;
}

int a[101][101];
int dp[55][55][55][55];
void solve() {
  int n, m;
  scanf("%d%d", &n, &m);
  for(int i = 0; i < n; i++) {
      for(int j = 0; j < m; j++) {
          cin >> a[i][j];
      }
  }

  memset(dp, 0, sizeof(dp));

  dp[0][0][0][0] = a[0][0];
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < m; j++) {
      for(int r = 0; r < n; r++) {
        for(int c = 0; c < m; c++) {
          int add = a[i][j] + a[r][c];
          if(same(i, j, r, c)) add = a[i][j];
          if(i - 1 >= 0 && j >= 0) {
            if(r - 1 >= 0 && c >= 0) {
              dp[i][j][r][c] = max(dp[i][j][r][c], dp[i - 1][j][r-1][c] + add);
            }
            if(c - 1 >= 0 && r >= 0) {
              dp[i][j][r][c] = max(dp[i][j][r][c], dp[i - 1][j][r][c - 1] + add);
            }
          }
          if(i >= 0 && j - 1 >= 0) {
            if(r - 1 >= 0 && c >= 0) {
              dp[i][j][r][c] = max(dp[i][j][r][c], dp[i][j - 1][r-1][c] + add);
            }
            if(c - 1 >= 0 && r >= 0) {
              dp[i][j][r][c] = max(dp[i][j][r][c], dp[i][j - 1][r][c - 1] + add);
            }
          }
        } 
      }
    }
  }

  cout << dp[n - 1][m - 1][n - 1][m - 1] << endl;

}

//pick cherry dp
int main()
{

  int t = 1;
  //cin >> t;
  W (t--)
  { 
    solve();
  }
  return 0;
}
