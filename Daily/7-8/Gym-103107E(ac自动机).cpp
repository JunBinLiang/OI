#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <set>
#include <vector>
#include <queue>

using namespace std;

const int N = 500010;
int tr[N][26], idx;
int q[N * 2], ne[N * 2], cnt[N * 2], in[N * 2], dp[N * 2];
int ids[N];
vector<int> g[N * 2];

void insert(int j, string& str) {
  int p = 0;
  for (int i = 0; i < str.size(); i ++ ) {
    int t = str[i] - 'a';
    if (!tr[p][t]) tr[p][t] = ++ idx;
    p = tr[p][t];
    //cout << str[i] << "  " << p << endl;
  }
  cnt[p]++;
  ids[j] = p;
}

void build()
{
  int hh = 0, tt = -1;
  for (int i = 0; i < 26; i ++ )
    if (tr[0][i])
      q[ ++ tt] = tr[0][i];

  while (hh <= tt)
  {
    int t = q[hh ++ ];
    for (int i = 0; i < 26; i ++ )
    {
      int p = tr[t][i];
      if (!p) tr[t][i] = tr[ne[t]][i];
      else
      {
        ne[p] = tr[ne[t]][i];
        //cout <<"fail :" << p << " " << ne[p] << endl;
        q[ ++ tt] = p;
      }
     }
     
     g[ne[t]].push_back(t);
     in[t]++;
     //cout << "add " << ne[t] << " " << t << endl;
  }
}

bool comp(string& a, string& b) {
  if(a.size() == b.size()) return a < b;
  return a.size() > b.size();
}

int topo() {
  queue<int> q;
  for(int i = 0; i <= idx; i++) {
    if(!in[i]) {
      q.push(i);
    }
  }

  while(q.size()) {
    int u = q.front(); q.pop();
    dp[u] += cnt[u];
    //cout << u << " "  << dp[u] << endl;
    for(int& nxt : g[u]) {
      dp[nxt] = max(dp[nxt], dp[u]);
      in[nxt]--;
      if(!in[nxt]) {
        q.push(nxt);
      }
    }
  }

  int res = 0;
  for(int i = 0; i <= idx; i++) {
    res = max(res, dp[i]);
  }
  return res;
}

int n;
void solve() {
  memset(tr, 0, sizeof tr);
  memset(cnt, 0, sizeof cnt);
  memset(in, 0, sizeof in);

  cin >> n;
  vector<string> a(n);
  for(int i = 0; i < n; i++) {
    cin >> a[i];
  }
  
  sort(a.begin(), a.end(), comp);
  for(int i = 0; i < n; i++) {
    insert(i, a[i]);
  }
  
  //for(int i = 0; i <= idx; i++) cout << cnt[i] << " ";
  //cout << endl;
  build();
  

  for(int i = 0; i < n; i++) {
    string& s = a[i];
    int p = 0;
    for(char& c : s) {
      int d = c - 'a';
      p = tr[p][d];
      if(p != ids[i]) {
        g[p].push_back(ids[i]);
        in[ids[i]]++;
        //cout << "add1 " << p << " " << ids[i] << endl;
      }
    }
  }
  cout << topo() << endl;
}

int main() {
    int t = 1;
    //cin >> t;
    while(t--) {
      solve();
    }
    return 0;
}

