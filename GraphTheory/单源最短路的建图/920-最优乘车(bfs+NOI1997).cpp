#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <cstring>
#include <algorithm>
#include <sstream>


using namespace std;  
using ll = long long;
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define pb push_back
#define ve vector


const int N = 600, M = N * N, INF = 1e9;
int stop[N];
bool is[N][N];
int m, n, S, T;
int dist[N];
int q[N * 4];

void bfs() {
    for(int i = 0; i < N; i++) dist[i] = INF;
    
    
    int hh = 0, tt = 1;
    q[0] = S;
    dist[S] = 0;
    
    while(hh != tt) {
        int cur = q[hh++];
        for(int i  = 1; i <= n; i++) {
           if(is[cur][i] && dist[cur] + 1 < dist[i]) {
               dist[i] = dist[cur] + 1;
               q[tt++] = i;
           }
        }
    }
}

void solve() {
    scanf("%d%d", &m, &n);
    S = 1; T = n;
    
    memset(is, false, sizeof is);
    
    for(int i = 0; i < m + 1; i++ ) {
        string line;
        getline(cin, line);
        stringstream ssin(line);
        int cnt = 0, p;
        while (ssin >> p) stop[cnt ++ ] = p;
        for(int j = 0; j < cnt; j++) {
            for(int k = j + 1; k < cnt; k++) {
                is[stop[j]][stop[k]] = true;
            }
        }
    }
    
    bfs();
    if(dist[n] == INF) {
        cout << "NO" << endl;
    } else {
        cout << dist[n] - 1 << endl;
    }
}



int main() {
    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
