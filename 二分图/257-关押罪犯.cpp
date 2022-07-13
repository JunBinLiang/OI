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

int n, m;
const int N = 2e4 + 50, M = 2e5 + 50;
int h[N], e[M], w[M], ne[M], idx;
int C[N];
bool good = true;
void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++ ;
}

struct Node{
  int u, v, w;  
};

bool COMP(Node& n1, Node& n2) {
    return n1.w < n2.w;
}

void dfs(int u, int c) {
    C[u] = c;
    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        if(C[j] == -1) { 
            dfs(j, c ^ 1);
        } else {
            if(C[j] == c) {
                good = false;
            }
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    ve<Node> a(m);
    for(int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        a[i] = {u, v, w};
    }
    sort(a.begin(), a.end(), COMP);
    
    int l = 0, r = m - 1, res = -1;
    while(l <= r) {
        int mid = l + (r - l) / 2;
        idx = 0;
        good = true;
        memset(h, -1, sizeof(h));
        memset(C, -1, sizeof(C));
        for(int i = mid; i < m; i++) {
            add(a[i].u, a[i].v, a[i].w);
            add(a[i].v, a[i].u, a[i].w);
        }
        
        for(int i = 1; i <= n; i++) {
            if(C[i] != -1) continue;
            dfs(i, 0);
        }
        
        if(good) {
            res = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    
    if(res == -1) {
        printf("%d\n", 0);
    } else {
        printf("%d\n", a[res - 1].w);
    }
}
