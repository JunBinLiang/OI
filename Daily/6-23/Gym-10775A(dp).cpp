
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

const int N = 1e6 + 10;
int a[N];
int dp[N][2];
int c = 0;
char s[N];

void reset(int n, int v) {
  for(int i = 0; i <= n; i++) dp[i][0] = dp[i][1] = v;
}

void solve() {
  c++;
  int x, y;
  scanf("%s", s);
  int n = strlen(s);
  scanf("%d%d", &x, &y);
  for(int i = 0; i < n; i++) {
    if(s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u') {
      a[i + 1] = 0;
    } else {
      if(s[i] == '?') a[i + 1] = -1;
      else a[i + 1] = 1;
    }
  }


  bool dislike = false;
  bool like = true;

  reset(n, -1);
  for(int i = 1; i <= n; i++) {
    if(a[i] == 0) {
      dp[i][0] = 1;
      if(dp[i - 1][0] != -1) {
        dp[i][0] = max(dp[i][0], 1 + dp[i - 1][0]);
      }

    } else if(a[i] == 1) {
      dp[i][1] = 1;
      if(dp[i - 1][1] != -1) {
        dp[i][1] = max(dp[i][1], 1 + dp[i - 1][1]);
      }
    } else {
      dp[i][0] = 1;
      if(dp[i - 1][0] != -1) {
        dp[i][0] = max(dp[i][0], 1 + dp[i - 1][0]);
      }
      dp[i][1] = 1;
      if(dp[i - 1][1] != -1) {
        dp[i][1] = max(dp[i][1], 1 + dp[i - 1][1]);
      }
    }
  }

  /*s = "";
  for(int i = 1; i <= n; i++) {
      s += to_string(a[i]);
  }
  cout << s << endl;*/

  for(int i = 1; i <= n; i++) {
    if(dp[i][0] >= x || dp[i][1] >= y) { //dislike
      dislike = true;
    }
  }

  if(!dislike) {
    cout << "Case #" << c << ": " << "LIKE" << endl;
    return;
  }

  int INF = 2 * n;
  reset(n, INF);
  dp[0][0] = dp[0][1] = 0;
  
  for(int i = 1; i <= n; i++) {
    if(a[i] == 0) {
      if(dp[i - 1][0] != INF && 1 + dp[i - 1][0] < x) {
        dp[i][0] = min(dp[i][0], 1 + dp[i - 1][0]);
      }
      if(dp[i - 1][1] != INF && 1 < x) {
        dp[i][0] = min(dp[i][0], 1);
      }
    } else if(a[i] == 1) {
      if(dp[i - 1][0] != INF && 1 < y) {
        dp[i][1] = min(dp[i][1], 1);
      }
      if(dp[i - 1][1] != INF && 1 + dp[i - 1][1] < y) {
        dp[i][1] = min(dp[i][1], 1 + dp[i - 1][1]);
      }
    } else {
      if(dp[i - 1][0] != INF && 1 + dp[i - 1][0] < x) {
        dp[i][0] = min(dp[i][0], 1 + dp[i - 1][0]);
      }
      if(dp[i - 1][1] != INF && 1 < x) {
        dp[i][0] = min(dp[i][0], 1);
      }

      if(dp[i - 1][0] != INF && 1 < y) {
        dp[i][1] = min(dp[i][1], 1);
      }
      if(dp[i - 1][1] != INF && 1 + dp[i - 1][1] < y) {
        dp[i][1] = min(dp[i][1], 1 + dp[i - 1][1]);
      }
    }
  }

  for(int i = 1; i <= n; i++) {
    if(a[i] == 0) {
        if(dp[i][0] >= x) like = false;
    } else if(a[i] == 1) {
        if(dp[i][1] >= y) like = false;
    } else {
        if(dp[i][0] >= x && dp[i][1] >= y) {
            like = false;
        }
    }
  }
  
  /*for(int i = 1; i <= n; i++) {
      cout << dp[i][0] << "  " << dp[i][1] << endl;
  }*/

  if(like) {
    cout << "Case #" << c << ": " << "SURPRISE" << endl;
  } else {
    cout << "Case #" << c << ": " << "DISLIKE" << endl;
  }
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
