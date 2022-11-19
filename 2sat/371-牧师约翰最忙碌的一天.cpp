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

const int N = 2e3 + 10 , M = 4e6 + 10;
int h[N], e[M], ne[M];
int dfn[N], low[N], id[N];
bool is[N];
int sta[N];

int t = 1;
int idx = 0;
int scc = 0;

void tarjan(int u) {
  dfn[u] = low[u] = t++;
  sta[++idx] = u, is[u] = true;
  for(int i = h[u]; ~i; i = ne[i]) {
    int nxt = e[i];
    if(!dfn[nxt]) {
      tarjan(nxt);
      low[u] = min(low[u], low[nxt]);
    } else if(is[nxt]) {
      low[u] = min(low[u], dfn[nxt]);
    }
  }
  
  if (low[u] == dfn[u]) {
    int y;
    scc ++ ;
    do {
      y = sta[idx -- ], is[y] = false, id[y] = scc;
    } while (y != u);
  }
}

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}

bool over(pair<int, int>& p1, pair<int, int>& p2) {
    if(p1.first > p2.first) {
        return over(p2, p1);
    }
    return p2.first < p1.second;
}

int to(string& s) {
    int h = (s[0] - '0') * 10 + (s[1] - '0');
    int m = (s[3] - '0') * 10 + (s[4] - '0');
    return h * 60 + m;
}

string format(int t) {
    int h = t / 60;
    int m = t % 60;
    string res = "";
    if(h < 10) {
        res += "0";
        res += to_string(h);
    } else {
        res += to_string(h);
    }
    res += ":";
    if(m < 10) {
        res += "0";
        res += to_string(m);
    } else {
        res += to_string(m);
    }
    return res;
}

pair<int, int> a[N * 2];
int main() {
    int n;
    scanf("%d", &n);
    memset(h, -1, sizeof h);
    for(int i = 0; i < n; i++) {
        int d;
        string s, t;
        cin >> s >> t >> d;
        a[i] = {to(s), to(s) + d};
        a[i + n] = {to(t) - d, to(t)};
    }
    
    for(int i = 0; i < n; i++) {
        for(int j = i - 1; j >= 0; j--) {
            if(over(a[i], a[j])) add(i, j + n), add(j, i + n);
            if(over(a[i], a[j + n])) add(i, j), add(j + n, i + n);
            if(over(a[i + n], a[j]))  add(i + n, j + n), add(j, i);
            if(over(a[i + n], a[j + n])) add(i + n, j), add(j + n, i);
        }
    }
    
    idx = 0;
    for(int i = 0; i < 2 * n; i++) {
        if(!dfn[i]) {
            tarjan(i); 
        }
    }
    
    for(int i = 0; i < n; i++) {
        if(id[i] == id[i + n]) {
          printf("NO \n");
          return 0;
        }
    }
    
    printf("YES\n");
    for(int i = 0; i < n; i++) {
        if(id[i] < id[i + n]) {
            pair<int, int> p1 = a[i];
            string s1 = format(p1.first);
            string s2 = format(p1.second);
            cout << s1 << " " << s2 << endl;
        } else {
            pair<int, int> p1 = a[i + n];
            string s1 = format(p1.first);
            string s2 = format(p1.second);
            cout << s1 << " " << s2 << endl;
        }
    }
    
    return 0;
}
