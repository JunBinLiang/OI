#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <cstring>
#include <algorithm>
#include <cmath>


using namespace std;  
using ll = long long;
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define pb push_back
#define ve vector
typedef pair<int, int> PII;
typedef pair<double, double> PDD;

//3:35 - 5:15
const int N = 2e5 + 100, M = N * 4; //points
const int INF = 2e9 + 100;
int n, m;
int h[N], e[M], w[M], ne[M], idx;
ll dist[N];

void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++ ;
}

struct Point {
    int x, y, idx;
    ll d;
    bool operator < (const Point& p) {
        if(y == p.y) {
            return x < p.x;
        }
        return y < p.y;
    }
} p1[N * 2], p2[N * 2];

int get(Point& pp1, Point& pp2) {
    return abs(pp1.x - pp2.x) + abs(pp1.y - pp2.y);
}


void solve() {
    scanf("%d%d", &n, &m);
    memset(h, -1, sizeof h);
    
    p1[2 * m] = {0, 0, 2 * m, 0};
    p2[2 * m] = {0, 0, 2 * m, 0};
    for(int i = 0; i < m; i++) {
        int x1, y1, x2, y2;
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        p1[i * 2 + 0] = {x1, y1, i * 2 + 0, x1 + y1};
        p1[i * 2 + 1] = {x2, y2, i * 2 + 1, x2 + y2};
        
        p2[i * 2 + 0] = {x1, y1, i * 2 + 0, x1 + y1};
        p2[i * 2 + 1] = {x2, y2, i * 2 + 1, x2 + y2};
        
        add(i * 2 + 1, i * 2, 0);
    }
    sort(p1, p1 + 2 * m + 1);
    
    /*for(int i = 0; i <= 2 * m; i++) {
        cout << "point : " << p1[i].x << " " << p1[i].y << " " << p1[i].idx << endl;
    }*/
    
    for(int i = 0; i < N; i++) {
        dist[i] = INF;
    }
    int S = 2 * m;
    dist[S] = 0;
    
    
    ll res = INF;
    map<int, Point> f;
    for(int i = 0; i <= 2 * m; i++) {
        int j = i;
        while(j <= 2 * m && p1[j].y == p1[i].y) {
            int x = p1[j].x, y = p1[j].y, index = p1[j].idx;
            for(int k = h[index]; ~k; k = ne[k]) {
                dist[index] = min(dist[index], dist[e[k]]);
            }
            
            auto it = f.upper_bound(x);
            ll dd = -1;
            if(it == f.begin()) {
                f[x] = {x, y, index, dist[index]};
                dd = dist[index];
            } else {
                it--;
                auto p = it -> second;
                dist[index] = min(dist[index], p.d + (abs(x - p.x) + 0ll) + abs(y - p.y));
                if(dist[index] < p.d + (abs(x - p.x) + 0ll) + abs(y - p.y)) {
                     f[x] = {x, y, index, dist[index]};
                     dd = dist[index];
                } else {
                     
                }
            }
            
            while(dd != -1) {
                auto itt = f.upper_bound(x);
                if(itt == f.end()) break;
                auto pp = itt -> second;
                if(dd + abs(x - pp.x) < pp.d + abs(pp.y - y)) {
                    f.erase(itt);
                } else {
                    break;
                }
            }
            
            res = min(res, dist[index] + (abs(n - x) + 0ll) + abs(n - y));
            j++;
        }
        i = j - 1;
    }
    

    cout << res << endl;
    
}

int main() {
    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}



