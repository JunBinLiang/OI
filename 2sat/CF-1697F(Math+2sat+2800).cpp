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

const int N = (2e4 + 10) * 25 , M = N * 25;
int h[N], e[M], ne[M];
int dfn[N], low[N], id[N];
bool is[N];
int sta[N];

int t = 1;
int idx = 0;
int scc = 0;
int n, m, k;
int nk = 0;
int top = 1;

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

int get(int i, int j, int op) {
    if(op == 0) {
        return i * (k + 1) + j;
    } else {
        return i * (k + 1) + j + nk;
    }
}


void solve() {
    for(int i = 0; i <= 2 * nk; i++) {
        h[i] = -1; dfn[i] = 0;
    }

    scanf("%d%d%d", &n, &m, &k);
    vector<int> res(n, -1);
    nk = n * (k + 1);
    idx = 0;
    t = 1;
    scc = 0;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < k; j++) {
            add(get(i, j, 0), get(i, j + 1, 0)); // <=
            
            add(get(i, j + 1, 1), get(i, j, 1));
        }
        for(int j = 0; j < k; j++) { //duplicate
            //add(get(i, j + 1, 1), get(i, j, 1)); // >
            
            //add(get(i, j, 0), get(i, j + 1, 0));
        }
        
        //ban
        add(get(i, 0, 0), get(i, 0, 1));
        add(get(i, k, 1), get(i, k, 0));
    } 
    
    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j <= k; j++) {
            //a[i] <= j than  a[i + 1] > j - 1
            add(get(i + 1, j, 0), get(i, j, 0));
            add(get(i, j, 1), get(i + 1, j, 1));
            
            add(get(i, j, 1), get(i + 1, j, 1));
            add(get(i + 1, j, 0), get(i, j, 0));
        }
    }
    
    while(m--) {
        int op;
        scanf("%d", &op);
        if(op == 1) {
            int i, x;
            scanf("%d%d", &i, &x);
            i--;
            // <= x - 1 or > x
            add(get(i, x - 1, 1), get(i, x, 1));
            add(get(i, x, 0), get(i, x - 1, 0));
            
            //duplicate
            //add(get(i, x, 0), get(i, x - 1, 0));
            //add(get(i, x - 1, 1), get(i, x, 1));
        } else if(op == 2) {
            int i, j, x;
            scanf("%d%d%d", &i, &j, &x);
            i--; j--;
            for(int t1 = 0; t1 < k; t1++) {
                int t2 = x - t1 - 1;
                if(t2 >= 1 && t2 <= k) {
                    add(get(i, t1, 1), get(j, t2, 0));
                    add(get(j, t2, 1), get(i, t1, 0));
                } else if(t2 <= 0) {
                    //ban i, t1
                    add(get(i, t1, 1), get(i, t1, 0));
                }
            }
            
        } else {
            int i, j, x;
            scanf("%d%d%d", &i, &j, &x);
            i--; j--;
            for(int t1 = 1; t1 <= k; t1++) {
                int t2 = x - t1 - 1;
                if(t2 >= 0 && t2 < k) {
                    add(get(i, t1, 0), get(j, t2, 1));
                    add(get(j, t2, 0), get(i, t1, 1));
                } else if(t2 >= k) {
                    add(get(i, t1, 0), get(i, t1, 1));
                }
            }
        }
    }

    for(int i = 0; i < 2 * nk; i++) {
        if(!dfn[i]) tarjan(i);
    }
    
    for(int i = 0; i < n; i++) {
        for(int j = 0; j <= k; j++) {
            if(id[get(i, j, 0)] == id[get(i, j, 1)]) {
                printf("-1\n");
                return;
            }
        }
    }
    
    for(int i = 0; i < n; i++) {
        for(int j = 1; j <= k; j++) {
            if(id[get(i, j, 0)] < id[get(i, j, 1)]) {
                res[i] = j;
                break;
            }
        }
    }


    for(int i : res) {
        if(i == -1) {
            printf("-1\n");
            return;
        }
    }

    for(int i : res) {
        printf("%d ", i);
    }
    printf("\n");
}  

int main() {
    memset(h, -1, sizeof h);
    memset(dfn, 0, sizeof dfn);
    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
