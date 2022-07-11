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

const int N = 50000 + 100, M = 2e5 +10;
int n, m;
int INF = 1000000000;
int pos[6];
int h[N], e[M], w[M], ne[M], idx;
int q[N];
bool st[N];
int dist[6][N];
typedef pair<int ,int > PII;
void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++ ;
}

void dijkstra(int start, int dist[]){
    memset(dist, 0x3f,  4*(n + 1));
    memset(st,0, sizeof st);
    dist[start] = 0;
    priority_queue<PII,vector<PII>, greater<PII>> heap;

    heap.push({0,start}); // 距离，点

    while(heap.size()){
        auto t = heap.top();
        heap.pop();
        int ver = t.second, distance = t.first;
        if(st[ver]) continue;
        st[ver] = true;

        for(int i = h[ver]; ~i; i = ne[i]){
            int j = e[i];
            if(dist[j] > distance + w[i]){
                dist[j] = distance + w[i];
                heap.push({dist[j], j});
            }
        }
    }
}



int dfs(int u, int start, int distance){
    // u== 6表示：拜访完5个亲戚，此时返回最短路
    if( u == 6) return distance;
    // res存距离最短的分支
    int res = INF;
    for(int i = 1; i<=5; i ++)
        if(!st[i]){
            int next = pos[i]; // 走亲戚i
            st[i] = true;
            res = min(res, dfs(u + 1, i, dist[start][next] + distance));
            st[i] = false;
        }
    return res;
}


int main() {
    cin >> n >> m;
    memset(h, -1, sizeof h);
    pos[0] = 1;
    for(int i = 1; i <= 5; i++) {
        cin >> pos[i];
    }
    
    
    while (m -- ){
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c); add(b, a, c);
    }
    
    for(int i = 0; i < 6; i++) {
        dijkstra(pos[i], dist[i]);
    }
    
    memset(st, 0, sizeof st);
    printf("%d\n", dfs(1, 0, 0));
    return 0;
}
