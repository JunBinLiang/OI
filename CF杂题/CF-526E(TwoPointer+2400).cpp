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

template <typename T>
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} 
  out << "]";
  return out;
}

const int N = 1e6 + 5;
int n, m;
int a[N];
ll pre[N];
ll dp[N], cnt[N];
ll get(int l, int r) {
  if(l == 0) return pre[r];
  return pre[r] - pre[l - 1];
}

void solve(ll k) {
  if(pre[n - 1] <= k) {
    cout << 1 << endl;
    return;
  }

  ll sum = 0;
  int j = -1;
  for(int i = n - 1; i >= 0; i--) {
    if(sum + a[i] <= k) {
      sum += a[i];
      j = i - 1;
    } else {
      break;
    }
  }

  for(int i = 0; i <= n; i++) {
    dp[i] = i;
    cnt[i] = 0;
  }

  ll tot = 0;
  int res = n;
  int r = j, rr = j;


  for(int i = j; i >= 0; i--) {
    tot += a[i];
    while(tot > k) {
      tot -= a[r--];
    }
    cnt[i] = 1 + cnt[r + 1];
    if(cnt[i] > 1) {
        if(dp[r + 1] == rr) {
            dp[i] = r;
        } else {
            dp[i] = dp[r + 1];
        }
    } else {
        dp[i] = rr;
    }
  }
  
  for(int i = 0; i <= n && sum <= k; i++) {
    if(i > rr) {
      res = min(res, 2);
      break;
    }
    
    
    int to = dp[i];
    int stp = cnt[i];
    if(stp == 1) {
        if(get(i, j) > k) {
            stp ++;
        }
    } else {
        if(get(to + 1, j) > k) {
            stp ++;
        } else {
            
        }
    }
    
    res = min(res, stp + 1);
    
    if(i + 1 < n) {
      sum += a[i];
      while(j + 1 < n && sum > k) {
        sum -= a[j + 1];
        j++;
      }
    }
  }
  cout << res << endl;
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    pre[0] = a[0];
    for(int i = 1; i < n; i++) {
      pre[i] = a[i] + pre[i - 1];
    }

    while(m--) {
      ll k; cin >> k;
      solve(k);
    }
    return 0;
}   
