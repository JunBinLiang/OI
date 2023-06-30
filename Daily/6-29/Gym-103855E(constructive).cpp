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

int to(char c) {
  if(c == 'R') {
    return 0;
  } else if(c == 'S') {
    return 1;
  }
  return 2;
}

char back(int x) {
  if(x == 0) return 'R';
  else if(x == 1) return 'S';
  else return 'P';
}

int judge(int x, int y) {
  if(x == 0 && y == 1) return 0;
  if(x == 0 && y == 2) return 2;
  if(x == 1 && y == 2) return 1;
  return -1;
}

const int N = 5e5 + 10;
char s[N];
int a[N];
bool vis[N];
int n, k;

void dfs(int l) {
  set<int> se;
  int r = -1;
  for(int i = l; i < n; i++) {
    if(se.size() < 2) {
      se.insert(a[i]);
    } else {
      if(se.find(a[i]) == se.end()) {
        r = i;
        break;
      }
    }
  }

  if(r != -1) {
    dfs(r);
    r--;
  } else {
    r = n - 1;
  }

  //solve [l : r]
  if(se.size() > 1) {
    auto it = se.begin();
    int x = (*it);
    it++;
    int y = (*it);
    int best = judge(x, y);
    int cnt = 0;
    for(int i = l ; i <= r; i++) {
      if(a[i] == best && cnt < k) {
        cnt++;
        vis[i] = true;
      }
    }

    int j = 0;
    vector<int> b;
    for(int i = l ; i <= r; i++) {
      if(!vis[i]) {
        b.push_back(a[i]);
      }
    }
    while(cnt--) b.push_back(best);
    for(int i = l; i <= r; i++) {
      a[i] = b[i - l];
    }

  }
}

void solve() {
  memset(vis, 0, sizeof vis);
  scanf("%d%d", &n, &k);
  scanf("%s", s);
  for(int i = 0; i < n; i++) a[i] = to(s[i]);
  
  /*for(int i = 0; i < n; i++) cout << a[i] << "  ";
  cout << endl;*/
  
  dfs(0);


  string t = "";
  for(int i = 0; i < n; i++) t += back(a[i]);
  cout << t << endl; 
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
