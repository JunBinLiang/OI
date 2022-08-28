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


int mod = 998244353;
const int N = 1e5 + 10;
ve<pair<int, int>> g[N];
ll ans[N];
int in[N];
int to[N];
bool leaf[N];
bool visit[N * 2];
int n;
int id = 0;
ll fpow(ll x, int y){
	ll res = 1;
	while(y){
		if(y & 1) res = (res * x) % mod;
		x = (x * x) %mod;
		y >>= 1;
	}
	return res;
}  

void out() {
  for(int i = 1; i <= n; i++) {
    printf("%lld ", ans[i]);
  }
  printf("\n");
}

bool check(int k) {
  for(int i = 0; i < n; i++) {
    in[i] = 0;
    to[i] = 0;
    leaf[i] = false;
  }
  
  for(int i = 0; i <= id; i++) {
      visit[i] = false;
  }

  for(int i = 0; i < n; i++) {
    for(pair<int, int>& p : g[i]) {
      in[p.first]++;
    }
  }

  queue<int> q;
  for(int i = 0; i < n; i++) {
    if(in[i] == 1) {
      q.push(i);
      to[g[i][0].first] += 1;
      leaf[i] = true;
    }
  }
  

  while(q.size() > 0) {
    int top = q.front(); q.pop();
    for(pair<int, int>& p : g[top]) {
      int nxt = p.first, idx = p.second;
      if(visit[idx]) continue;
      visit[idx] = true;
      in[nxt]--; 
      if(in[nxt] == 1) {
        q.push(nxt);
      }
      if(!leaf[top]) {
        if((to[top] + 1) % k == 0) {
          to[top] += 1;
        } else {
          to[nxt] += 1;
        }
      }
    }
  }
  
  /*if(k == 2) {
      for(int i = 0; i < n; i++) cout << to[i] << " ";
      cout << endl;
  }*/

  int g = -1;
  for(int i = 0; i < n; i++) {
    if(to[i] == 0) continue;
    if(g == -1) g = to[i];
    else g = __gcd(g, to[i]);
  }
  return g == k;
}

void solve() { 
  scanf("%d", &n);
  for(int i = 0; i <= n; i++) g[i].clear();
    
  id = 0;
  for(int i = 0; i < n - 1; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    u--; v--;
    g[u].pb({v, id}); 
    g[v].pb({u, id++});
  }

  for(int i = 0; i <= n; i++) {
    ans[i] = 0;
  }

  for(int i = 2; i <= n; i++) {
    if((n - 1) % i == 0) {
      if(check(i)) {
        ans[i] = 1;
      }
    }
  }

  ans[1] = fpow(2, n - 1);
  for(int i = 2; i <= n; i++) {
    ans[1] -= ans[i];
    ans[1] += mod;
    ans[1] %= mod;
  }
  out();
}

int main() {
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
}
  
  
