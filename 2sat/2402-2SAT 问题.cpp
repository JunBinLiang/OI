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



/*class Compare
{
public:
    bool operator() (pair<int, int>& a, pair<int, int>& b)
    {
        return a.first > b.first;
    }
    //a[0] > b[0] : min
};*/



int n, m;
const int N = 2000010;
const int M = 2000010;
int h[N], e[M], ne[M];
int dfn[N], low[N], id[N];
bool is[N];
int sta[N];

int t = 1;
int idx = 0;
int scc = 0;
int cnt = 0;
int top = 0;

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

void solve() {
  scanf("%d%d", &n, &m);
  memset(h, -1, sizeof(h));
  while (m -- ) {
    int i, a, j, b;
    scanf("%d%d%d%d", &i, &a, &j, &b);
    i--, j--;
    add(2 * i + a ^ 1, 2 * j + b);
    add(2 * j + b ^ 1, 2 * i + a);
  }

  idx = 0;
  for(int i = 0; i < 2 * n; i++) {
    if(!dfn[i]) {
      tarjan(i); 
    }
  }
  
  for(int i = 0; i < n; i++) {
    if(id[i * 2] == id[i * 2 + 1]) {
      printf("IMPOSSIBLE \n");
      return;
    }
  }

  printf("POSSIBLE \n");
  for(int i = 0; i < n; i++) { //tarjan is reverse as Topo
    if(id[i * 2] < id[i * 2 + 1]) {
      printf("0 ");
    } else {
      printf("1 ");
    }
  }
}

int main()
{

  int t = 1;
  //cin >> t;
  W (t--)
  { 
    solve();
  }
  return 0;
}
