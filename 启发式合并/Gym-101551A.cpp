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
#include <iomanip>
 
using ll = long long;
using ull = unsigned long long;
#define pb push_back
#define vec vector
#define var auto
#define FOR(i, a, b) for (int i = a; i < b; ++i)
using namespace std;
 
template <typename T>
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} 
  out << "]";
  return out;
}
 

const int N = 5e5 + 10;
char s[N];
int id = 1, tr[N][26];
vector<int> g[N * 26];

vector<string> a;
int cnt = 0;
void check(int x, int y) {
    string s = a[x], t = a[y];
    cnt++;
    if(s.size() > t.size()) {
        cout << "NO " << x << " " << y << endl;
        return;
    }
    for(int i = 0; i < s.size(); i++) {
        if(s[i] != t[i]) {
            cout << "NO " << x << " " << y << endl;
            return;
        }
    }
}

void add(int idx) {
    int len = strlen(s);
    int u = 0;
    //string t = "";
    for(int i = 0; i < len; i++) {
        int d = s[i] - 'a';
        //t += s[i];
        if(tr[u][d] == -1) {
            tr[u][d] = id++;
        }
        u = tr[u][d];
    }
    //a.push_back(t);
    g[u].push_back(idx);
}

vector<int> dfs(int u) {

    vector<int> cur;
    for(int i = 0; i < 26; i++) {
        if(tr[u][i] == -1) continue;
        vector<int> nxt = dfs(tr[u][i]);
        if(nxt.size() > cur.size()) swap(nxt, cur);
        for(int v : nxt) cur.push_back(v);
    }

    auto& v = g[u];
    
    while(v.size() > 0 && cur.size() > 0) {
        int x = v.back(); v.pop_back();
        int y = cur.back(); cur.pop_back();
        //check(x, y);
        cnt++;
        printf("%d %d\n", x, y);
    }
    
    while(v.size() >= 2) {
        int x = v.back(); v.pop_back();
        int y = v.back(); v.pop_back();
        //check(x, y);
        cnt++;
        printf("%d %d\n", x, y);
    }
    
    if(cur.size() < v.size()) swap(cur, v);
    for(int nxt : v) cur.push_back(nxt);
    return cur;
}



void solve() {
    memset(tr, -1, sizeof tr);
    int n;
    cin >> n;
    a.push_back("");
    for(int i = 1; i <= n * 2; i++) {
        scanf("%s", s);
        add(i);
    }
    
    dfs(0);
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

