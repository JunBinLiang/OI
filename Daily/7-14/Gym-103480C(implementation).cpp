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
#include <fstream>
 
using ll = long long;
using ull = unsigned long long;
#define pb push_back
#define vec vector
#define var auto
#define JBFOR(i, a, b) for (int i = a; i < b; ++i)
using namespace std;
 
template <typename T>
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} 
  out << "]";
  return out;
}


struct S{
  vector<int> X, Y;
  int xp, yp;
  int sum;
  void init(vector<pair<int, int>>& a) {
    xp = yp = sum = 0;
    for(auto& p : a) {
      int x = p.first, y = p.second;
      if(x == 0) Y.push_back(y);
      if(y == 0) X.push_back(x);
    }
    sort(X.begin(), X.end());
    sort(Y.begin(), Y.end());
  }

  void op1(char c, int v) {
    if(v != 0 && ((c == 'X' && yp != 0) || (c == 'Y' && xp != 0))) { 
      xp = yp = 0; //reset to origin
      return;
    }


    if(c == 'X') {
      int L = xp, R = xp + v;
      if(L > R) swap(L, R);
      vector<int> newX;
      for(int x : X) {
        if(x >= L && x <= R) {
        } else {
          newX.push_back(x);
        }
      }
      sum += (X.size() - newX.size());
      X = newX;
      xp += v;
    } else {
      int L = yp, R = yp + v;
      if(L > R) swap(L, R);
      vector<int> newY;
      for(int y : Y) {
        if(y >= L && y <= R) {
        } else {
          newY.push_back(y);
        }
      }
      sum += (Y.size() - newY.size());
      Y = newY;
      yp += v;
    }
  }

  void op2(char op) {
    if(op == 'X') {
      for(auto& x : X) x = -x;
    } else {
      for(auto& y : Y) y = -y;
    }
    op1('X', 0); op1('Y', 0);
  }

  void op3() {
    swap(X, Y);
    op1('X', 0); op1('Y', 0);
  }
};


int n, m;
char c[2];
void solve() {


  scanf("%d", &n);
  vector<pair<int, int>> a(n);
  for(int i = 0; i < n; i++) {
    scanf("%d%d", &a[i].first, &a[i].second);
  }

  S cur;
  cur.init(a);
  vector<S> T;
  T.push_back(cur);

  scanf("%d", &m);
  for(int i = 1; i <= m; i++) {
    int op;
    scanf("%d", &op);
    if(op == 1) {
      scanf("%s", c);
      int v;
      scanf("%d", &v);
      cur.op1(c[0], v);
    } else if(op == 2) {
      scanf("%s", c);
      cur.op2(c[0]);
    } else if(op == 3) {
      cur.op3();
    } else {
      int t;
      scanf("%d", &t);
      if(t != i) cur = T[t - 1];
    }
    T.push_back(cur); //auto copy all info
  }

  printf("%d\n", cur.sum);
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
