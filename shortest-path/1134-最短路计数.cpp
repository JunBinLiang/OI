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

int mod = 100003;  
int n, m;
int INF = 1000000000;
const int N = 1e5 + 5, M = 4e5 + 100;

int h[N], e[M], w[M], ne[M], idx;
int q[N];
int dist[N], dp[N];
void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++ ;
}

void bfs() {
    int hh = 0, tt = 1;
    for(int i = 0; i < N; i++) {
        dist[i] = INF;
    }
    memset(dp, 0, sizeof(dp));
    q[0] = 1;
    dist[1] = 0;
    dp[1] = 1;
    
    while(hh != tt) {
        int root = q[hh++];
        if(hh == N) hh = 0;
        for (int i = h[root]; ~i; i = ne[i]) {
            int j = e[i];
            if(dist[j] >= dist[root] + 1) {
                if(dist[j] == dist[root] + 1) {
                    dp[j] += dp[root];
                    dp[j] %= mod;
                } else {
                    dist[j] = dist[root] + 1;
                    q[tt++] = j;
                    dp[j] += dp[root];
                    if(tt == N) tt = 0;
                }
            }
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    memset(h, -1, sizeof(h));
    for(int i = 0; i < m; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        add(a, b, 0); add(b, a, 0);
    }
    bfs();
    for(int i = 1; i <= n; i++) {
        printf("%d \n", dp[i]);
    }
}
