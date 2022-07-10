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
#include <sstream>

using namespace std;
int n, m;
const int N = 600;
int stop[N];
int dist[N];
int q[N * 4];
bool is[N][N];
int INF = 1000000000;

void bfs() {
    for(int i = 0; i < N; i++) {
        dist[i] = INF;
    }
    
    int hh = 0, tt = 1;
    q[0] = 1;
    dist[1] = 0;
    
    while(hh != tt) {
        int root = q[hh++];
        for(int i = 1; i <= n; i++) {
            if(is[root][i] && dist[root] + 1 < dist[i]) {
                dist[i] = dist[root] + 1;
                q[tt++] = i;
            }
        }
    }
}

int main() {
    cin >> m >> n;
    string line;
    getline(cin, line);
    for(int i = 0; i < m; i++) {
        getline(cin, line);
        stringstream ssin(line);
        int cnt = 0, p;
        while (ssin >> p) stop[cnt ++ ] = p;
        for(int j = 0; j < cnt; j++) {
            for(int k = j + 1; k < cnt; k++) {
                is[stop[j]][stop[k]] = 1;
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
