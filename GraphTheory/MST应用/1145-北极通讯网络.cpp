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
#define x first
#define y second
typedef pair<int, int> PII;
typedef pair<double, double> PDD;

const int N = 550, M = N * N;
int n, k;
int p[N];
pair<int, int> a[N];

struct Edge
{
    int u, v;
    double w;
    bool operator< (const Edge &t) const
    {
        return w < t.w;
    }
} e[M];

double get_dist(PII& a, PII& b)
{
    int dx = a.x - b.x;
    int dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

int find(int x)
{
    if (p[x] != x) p[x] = find(p[x]);
    return p[x];
}


void solve() {
    cin >> n >> k;
    int m = 0;
    for(int i = 0; i < n; i++) {
        cin >> a[i].x >> a[i].y;
    }
    
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            e[m++] = {i, j, get_dist(a[i], a[j])};
        }
    }
    
    for(int i = 0; i <= n; i++) p[i] = i;
    sort(e, e + m);
    
    double res = 0;
    int edges = n - 1;
    k--;
    for(int i = 0; i < m && edges > k; i++) {
        int u = e[i].u, v = e[i].v;
        double w = e[i].w;
        int r1 = find(u), r2 = find(v);
        if(r1 != r2) {
            p[r1] = r2;
            res = w;
            edges--;
        }
    }
    
    printf("%.2lf\n", res);
}

int main() {
    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
