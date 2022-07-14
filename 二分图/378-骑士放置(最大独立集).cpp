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

int n, m, k;
const int N = 110;
bool is[N][N];
bool st[N][N];
pair<int, int> match[N][N];
int dx[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};

bool dfs(int x, int y) {
    for(int i = 0; i < 8; i++) {
        int xx = x + dx[i], yy = y + dy[i];
        if(xx < 1 || xx > n || yy < 1 || yy > m || is[xx][yy] || st[xx][yy]) continue;
        pair<int, int> p = match[xx][yy];
        st[xx][yy] = true;
        if(p.first == -1 || dfs(p.first, p.second)) {
            match[xx][yy] = {x, y};
            return true;
        }
    }
    return false;
}

//找最大独立集
int main() {
    cin >> n >> m >> k;
    int res = 0;
    for(int i = 0; i < k; i++) {
        int x, y;
        cin >> x >> y;
        is[x][y] = true;
    }

    memset(match, -1, sizeof match);
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            if(is[i][j] || (i + j) % 2 == 1) continue;
            memset(st, false, sizeof st);
            if(dfs(i, j)) res++;
        }
    }
    
    cout << n * m - k - res << endl;
    return 0;
}

