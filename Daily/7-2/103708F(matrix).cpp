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

const int MOD = 1e9 + 7;

int a[2][2]; int f1[2];
int temp[2]; int temp1[2][2];
void mul1() {
  for(int i = 0; i < 2; i++) temp[i] = f1[i];
  for(int c = 0; c < 2; c++) {
      int sum = 0;
      for(int r = 0; r < 2; r++) {
        sum += ((temp[r] + 0ll) * a[r][c] % MOD);
        sum %= MOD;
      }
      f1[c] = sum;
  }
}

void mul2() {
  for(int i = 0; i < 2; i++)
    for(int j = 0; j < 2; j++)
        temp1[i][j] = a[i][j];
            
  for(int i = 0; i < 2; i++) {
    for(int j = 0; j < 2; j++) {
      int sum = 0;
      for(int k = 0; k < 2; k++) {
          sum += ((temp1[i][k] + 0ll) * temp1[k][j] % MOD);
          sum %= MOD;
      }
      a[i][j] = sum;
    }
  }
}

int fastFib(int l, int r, int v1, int v2) {
  if(l == r) {
    return v1;
  }
  if(r == l + 1) {
    return v2;
  }
  
  memset(a, 0, sizeof a);
  a[0][1] = a[1][0] = a[1][1] = 1;
  f1[0] = v1;
  f1[1] = v2;
  int n = (r - l + 1) - 2;
  //cout <<"sz  " << v1 <<"  " << v2  << "  " << n << endl;
  while(n) {
      if (n & 1) mul1();// res = res * a
      mul2();  // a = a * a
      n >>= 1;
  }
  
  //cout << f1[0] << "  " << f1[1] << "  " << f1[2] << endl;
  
  return f1[1];
}


void solve() {
  int n, m;
  cin >> n >> m;
  vector<int> a(m);
  for(int i = 0; i < a.size(); i++) {
    scanf("%d", &a[i]);
  }

  sort(a.begin(), a.end());
  for(int i = 1; i < a.size(); i++) {
    if(a[i] - a[i - 1] == 1) {
      cout << 0 << endl;
      return;
    }
  }

  if(a.size() == 0) {
    int res = fastFib(0, n, 1, 1);
    printf("%d", res);
    return;
  }

  int res = fastFib(0, a[0] - 1, 1, 1);
  for(int i = 1; i < a.size(); i++) {
    res = fastFib(a[i - 1] - 1, a[i] - 1, res, 0);
  }
  res = fastFib(a.back() - 1, n, res, 0);
  printf("%d", res);

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
