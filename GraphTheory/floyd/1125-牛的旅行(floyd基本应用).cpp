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

#define x first
#define y second

const int N = 155;
const double INF = 1e20;
int n;

PDD q[N];
double d[N][N];
double maxd[N];
char g[N][N];

double get_dist(PDD a, PDD b)
{
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

void solve() {
    cin >> n;
    for (int i = 0; i < n; i ++ ) cin >> q[i].x >> q[i].y;
    for (int i = 0; i < n; i ++ ) cin >> g[i];
    
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if (i == j) d[i][j] = 0;
            else if (g[i][j] == '1') d[i][j] = get_dist(q[i], q[j]);
            else d[i][j] = INF;
        }
    }

    //floyd
    for (int k = 0; k < n; k ++ )
        for (int i = 0; i < n; i ++ )
            for (int j = 0; j < n; j ++ )
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);


    double r1 = 0;
    for (int i = 0; i < n; i ++ )
    {
        for (int j = 0; j < n; j ++ )
        {
            if (d[i][j] < INF / 2) {
                maxd[i] = max(maxd[i], d[i][j]);
            }
        }
                
        r1 = max(r1, maxd[i]);
    }
    
    double r2 = INF;

    for (int i = 0; i < n; i ++ ) {
        for (int j = 0; j < n; j ++ ) {
            if (d[i][j] > INF / 2) { //not reacheable from each other
                r2 = min(r2, maxd[i] + maxd[j] + get_dist(q[i], q[j]));
            }
        }       
    }

    printf("%.6lf\n", max(r1, r2));
}

int main() {
    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
