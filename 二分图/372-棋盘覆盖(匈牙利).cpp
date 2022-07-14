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


//匈利亚讲解 : https://www.renfei.org/blog/bipartite-matching.html

int n, m;
const int N = 105;
bool block[N][N];
int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};
bool st[N][N];
pair<int, int> match[N][N];

bool dfs(int x, int y) {
    for(int i = 0; i < 4; i++) {
        int xx = x + dx[i], yy = y + dy[i];
        if(xx >= 1 && xx <= n && yy >= 1 && yy <= n && !block[xx][yy] && !st[xx][yy]) {
            st[xx][yy] = true;
            pair<int, int> p = match[xx][yy];
            if(p.first == -1 || dfs(p.first, p.second)) {
                match[xx][yy] = {x, y};
                return true;
            }
        }
    }
    return false;
}

int main() {
    cin >> n >> m;
    for(int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        block[x][y] = true;
    }
    
    int res = 0;
    memset(match, -1, sizeof match);
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            if((i + j) % 2 == 1 && !block[i][j]) {
                memset(st, false, sizeof st);
                if(dfs(i, j)) res++;
            }
        }
    }
    printf("%d \n", res);
}
