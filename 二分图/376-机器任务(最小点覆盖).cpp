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

int n, m, k;
const int N = 110;
bool g[N][N];
bool st[N];
int match[N];

bool dfs(int x) {
    for(int i = 1; i <= m; i++) {
        if(g[x][i] && !st[i]) {
            st[i] = true;
            if(match[i] == -1 || dfs(match[i])) {
                match[i] = x;
                return true;
            }
        }
    }
    
    return false;
}

int main() {
    
    while(true) {
        cin >> n >> m >> k;
        if(n == 0) break;
        
        memset(g, 0, sizeof g);
        memset(match, -1, sizeof match);
        
        for(int i = 0; i < k; i++) {
            int idx, a, b;
            cin >> idx >> a >> b;
            g[a][b] = 1;
        }
        
        int res = 0;
        for(int i = 1; i <= n; i++) {
            memset(st, 0, sizeof st);
            if(dfs(i))res++;
        }
        
        cout << res << endl;
    }
    return 0;
}
