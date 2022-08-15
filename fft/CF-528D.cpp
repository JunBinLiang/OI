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

const int N = 8e5 + 10;
const double PI = acos(-1);

int rev[N], bit = 0, tot = 0;
int n, m, k;
string s, t;
int res = 0;
ve<char> ma = {'A','T', 'G', 'C'};
map<char, int> f;
bool is[N];
int cnt[4][N];
struct Complex
{
    double x, y;
    Complex operator+ (const Complex& t) const
    {
        return {x + t.x, y + t.y};
    }
    Complex operator- (const Complex& t) const
    {
        return {x - t.x, y - t.y};
    }
    Complex operator* (const Complex& t) const
    {
        return {x * t.x - y * t.y, x * t.y + y * t.x};
    }
}a[N], b[N];

void fft(Complex a[], int inv)
{
  for (int i = 0; i < tot; i ++ )
      if (i < rev[i])
          swap(a[i], a[rev[i]]);
  for (int mid = 1; mid < tot; mid <<= 1)
  {
      auto w1 = Complex({cos(PI / mid), inv * sin(PI / mid)});
      for (int i = 0; i < tot; i += mid * 2)
      {
          auto wk = Complex({1, 0});
          for (int j = 0; j < mid; j ++, wk = wk * w1)
          {
              auto x = a[i + j], y = wk * a[i + j + mid];
              a[i + j] = x + y, a[i + j + mid] = x - y;
          }
      }
  }
}
void solve() { 
  cin >> n >> m >> k;
  cin >> s >> t;
  memset(is, true, sizeof(is));
  memset(cnt, 0, sizeof(cnt));

  while ((1 << bit) < n + m + 1 - 2) bit ++;
  tot = 1 << bit;
  for (int i = 0; i < tot; i ++ )
  {
    rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bit - 1));
  }

  for(int i = 0; i < t.size(); i++) {
    f[t[i]]++;
  }
  
  for(int i = 0; i < ma.size(); i++) {
    for(int j = 0; j < tot; j++) {
      a[j].x = a[j].y = b[j].x = b[j].y = 0;
    }

    for(int j = 0; j < t.size(); j++) {
      if(t[j] == ma[i]) {
        b[j].x = 1;
      }
    }

    ve<int> c(s.size(), 0);
    for(int j = 0; j < s.size(); j++) {
      if(s[j] == ma[i]) {
        c[j] = 1;
      }
    }

    ve<int> d(s.size());
    int last = -100000000;
    for(int j = 0; j < s.size(); j++) {
      if(c[j] == 1) {
        d[j] = 1;
        last = j;
      } else {
        if(j - last <= k) {
          d[j] = 1;
        }
      }
    }
    last = 100000000;
    for(int j = s.size() - 1; j >= 0; j--) {
      if(c[j] == 1) {
        last = j;
      } else {
        if(last - j <= k) {
          d[j] = 1;
        }
      }
    }
    reverse(d.begin(), d.end());
    for(int j = 0; j < d.size(); j++) {
      if(d[j]) {
        a[j].x = 1;
      }
    }
    
    /*if(ma[i] == 'A') {
        for(int j = 0; j < n; j++) {
            cout << a[j].x << " ";
        }cout << endl;
        
        for(int j = 0; j < m; j++) {
            cout << b[j].x << " ";
        }cout << endl;
    }*/
    
    
    fft(a, 1);
    fft(b, 1);
    for (int i = 0; i < tot; i ++ ) a[i] = a[i] * b[i];
    fft(a, -1);
    for (int j = t.size() - 1; j < n; j ++ ) {
      int x = (int)(a[j].x / tot + 0.5);
      if(x > 0) {
        cnt[i][j]+= x;
      }
    }
  }
  
  for(int i = 0; i < 4; i++) {
      for(int j = t.size() - 1; j < n; j++) {
          if(cnt[i][j] != f[ma[i]]) {
              is[j] = false;
          }
      }
  }
  
  /*cout << endl;
  for(int i = 0; i < 4; i++) {
    for(int j = 0; j < n; j++) {
        cout << cnt[i][j] << " ";
    }
    cout << endl;
  }*/
  
  

  for(int i = t.size() - 1; i < n; i++) {
    if(is[i]) {
      res++;
    }
  }
  printf("%d", res);
}

int main() {
    int t = 1;
    //cin >> t;
    while(t--) {
        solve();
    }
}
  
