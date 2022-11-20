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

const int N = 100000 + 10;
const int M = 200000 + 10;
int h[N], e[M], ne[M];
int dfn[N], low[N], id[N];
bool is[N];
int sta[N];

int t = 1;
int idx = 0;
int scc = 0;
int top = 0;
int n, d, m;
vector<int> pos;

struct op {
    int h1, h2;
    char x, y;
} a[M];

void tarjan(int u) {
  dfn[u] = low[u] = t++;
  sta[++top] = u, is[u] = true;
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
      y = sta[top -- ], is[y] = false, id[y] = scc;
    } while (y != u);
  }
}

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}


map<char, int> ma[3];
vector<char> b[3];

bool work(string& s) {
    memset(h, -1, sizeof h);
    memset(dfn, 0, sizeof dfn);
    memset(id, 0, sizeof id);
    t = 1;
    idx = 0;
    scc = 0;
    for(int i = 0; i < m; i++) {
        int idx1 = a[i].h1 - 1, idx2 = a[i].h2 - 1;
        int h1 = idx1, h2 = idx2;
        char A = a[i].x, B = a[i].y;
        if(ma[s[idx1] - 'a'].find(A) == ma[s[idx1] - 'a'].end()) {
            continue;
        }
        
        if(idx1 == idx2) {
            if(A == B) continue;
            int e1 = ma[s[idx1] - 'a'][A];
            if(e1 == 0) add(h1, h1 + n);
            else add(h1 + n, h1);
            continue;
        }
        
        if(ma[s[idx2] - 'a'].find(B) != ma[s[idx2] - 'a'].end()) {
            int e1 = ma[s[idx1] - 'a'][A], e2 = ma[s[idx2] - 'a'][B];
            if(e1 == 0 && e2 == 0) add(h1, h2), add(h2 + n, h1 + n);
            if(e1 == 0 && e2 == 1) add(h1, h2 + n), add(h2, h1 + n);
            if(e1 == 1 && e2 == 0) add(h1 + n, h2), add(h2 + n, h1);
            if(e1 == 1 && e2 == 1) add(h1 + n, h2 + n), add(h2, h1);
        } else {
            //a -> b, b not exist, a can not be taken.
            int e1 = ma[s[idx1] - 'a'][A];
            if(e1 == 0) add(h1, h1 + n);
            else add(h1 + n, h1);
        }
    }
    
    for(int i = 0; i < 2 * n; i++) {
        if(!dfn[i]) {
            tarjan(i); 
        }
    }
    
    for(int i = 0; i < n; i++) {
        if(id[i] == id[i + n]) {
          return false;
        }
    }
    
    string res = "";
    for(int i = 0; i < n; i++) {
        if(id[i] < id[i + n]) {
            res += b[s[i] - 'a'][0];
        } else {
            res += b[s[i] - 'a'][1];
        }
    }
    cout << res << endl;
    return true;
}

int main() {
    ma[0]['B'] = 0;
    ma[0]['C'] = 1;
    
    ma[1]['A'] = 0;
    ma[1]['C'] = 1;
    
    ma[2]['A'] = 0;
    ma[2]['B'] = 1;
    
    b[0] = {'B', 'C'};
    b[1] = {'A', 'C'};
    b[2] = {'A', 'B'};
    
    
    scanf("%d%d", &n, &d);
    string s;
    cin >> s;
    
    for(int i = 0; i < s.size(); i++) {
        if(s[i] == 'x') pos.push_back(i);
    }
    
    scanf("%d", &m);
    for(int i = 0; i < m; i++) {
        int h1, h2;
        char x, y;
        cin >> h1 >> x >> h2 >> y;
        a[i] = {h1, h2, x, y};
    }
    
    for(int i = 0; i < (1 << d); i++) {
        for(int j = 0; j < d; j++) {
            if(i & (1 << j)) {
                s[pos[j]] = 'a';
            } else {
                s[pos[j]] = 'b';
            }
        }
        if(work(s)) {
            return 0;
        }
    }
    printf("-1\n");
    return 0;
}

/*
2 1
xc
2
2 A 1 C
2 B 1 A
output: AB


2 1
xc
2
2 A 1 C
2 B 1 A
output : CA
*/
