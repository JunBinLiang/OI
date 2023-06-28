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

template <typename U, typename T, class Cmp>
ostream& operator <<(ostream& out, const map<U, T, Cmp>& a) {
  out << "{"; bool first = true;
  for (auto& p : a) { out << (first ? "" : ", "); out << p.first << ":" << p.second; first = 0;} out << "}";
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

bool comp(string& s1, string& s2) {
  return s1.size() < s2.size();
}


const int N = 1e6 + 10;
int n, m, base = 101;
int res1 = 0, res2 = 0;
ull h[N];

ull getPrefix(string& s, int l, int r) {
    ull res = 0;
    for(int i = l; i <= r; i++) {
        res = res * base + s[i] - 'a' + 1;
    }
    return res;
}

ull getPost(string& s, int l, int r) {
    ull res = 0;
    for(int i = r; i >= l; i--) {
        res = res * base + s[i] - 'a' + 1;
    }
    return res;
}

unordered_map<ull, int> aAll, bAll;
vector<pair<ll, int>> g[N]; 
unordered_set<ll> sufset, common;

bool vis1[N], vis2[N];
char str[N];
void solve() {
  //memset(vis1, false, sizeof vis1);
  //memset(vis2, false, sizeof vis2);
  scanf("%d%d", &n, &m);
  vector<string> a(n), b(m);
  for(int i = 0; i < n; i++) {
    scanf("%s", str);
    int len = strlen(str);
    for(int j = 0; j < len; j++) a[i] += str[j];
  }
  for(int i = 0; i < m; i++) {
    scanf("%s", str);
    int len = strlen(str);
    for(int j = 0; j < len; j++) b[i] += str[j];
  }
  sort(a.begin(), a.end(), comp);
  sort(b.begin(), b.end(), comp);
  
  for(int i = 0; i < a.size(); i++) {
    string& s = a[i];
    ull pre = 0;
    for(int j = 0; j < s.size(); j++) {
      pre = pre * base + s[j] - 'a' + 1;
      if(aAll.find(pre) != aAll.end() && j + 1 < s.size()) {
        ull suf = getPrefix(s, j + 1, s.size() - 1);
        g[i].push_back({suf, aAll[pre]});
        sufset.insert(suf);
      }
    }
    aAll[pre] = i;
  }

  /////////////////////////////////

  for(int i = 0; i < b.size(); i++) {
    string& s = b[i];
    ull ha = 0;
    for(int j = 0; j < s.size(); j++) { //prefix
      ha = ha * base + s[j] - 'a' + 1;
      h[j] = ha;
    }

    ll suf = 0;
    for(int j = s.size() - 1; j >= 0; j--) {
      suf = suf * base + s[j] - 'a' + 1;
      if(j > 0 && bAll.find(suf) != bAll.end()) {
        ull pre = h[j - 1];
        /*if(aTriple.find(pre) != aTriple.end()) {
          auto& v = aTriple[pre];
          while(v.size()) {
            vis1[v.back().first] = vis1[v.back().second] = true;
            v.pop_back();
          }
          vis2[i] = vis2[bAll[suf]] = true;
        }*/
        if(sufset.find(pre) != sufset.end()) {
            common.insert(pre);
            vis2[i] = true;
            vis2[bAll[suf]] = true;
        }
      }
    }
    bAll[suf] = i;
  }
  
  for(int i = 0; i < n; i++) {
      if(!g[i].size()) continue;
      for(auto& p : g[i]) {
          if(common.find(p.first) != common.end()) {
              vis1[p.second] = true;
              vis1[i] = true;
          }
      }
  }
  
  
  for(int i = 0; i < n; i++) {
    if(!vis1[i]) res1++;
  }
  for(int i = 0; i < m; i++) {
    if(!vis2[i]) res2++;
  }

  cout << res1 << " " << res2 << endl;
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

