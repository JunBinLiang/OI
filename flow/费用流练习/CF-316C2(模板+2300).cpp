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
#include<fstream>
 

using namespace std;  
using ll = long long;
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define pb push_back
#define ve vector

//ifstream fcin("test/input.txt");
//ofstream fcout("test/output.txt");

const int N = 10010, M = N * 4, INF = 1e8;
int n, m, S, T;

int h[N], e[M], f[M], w[M], ne[M], idx;
int q[N], d[N], pre[N], incf[N];
bool st[N];

void add(int a, int b, int c, int d)
{
    e[idx] = b, f[idx] = c, w[idx] = d, ne[idx] = h[a], h[a] = idx ++ ;
    e[idx] = a, f[idx] = 0, w[idx] = -d, ne[idx] = h[b], h[b] = idx ++ ;
}

bool spfa()
{
    int hh = 0, tt = 1;
    memset(d, 0x3f, sizeof d);
    memset(incf, 0, sizeof incf);
    q[0] = S, d[S] = 0, incf[S] = INF;
    while (hh != tt)
    {
        int t = q[hh ++ ];
        if (hh == N) hh = 0;
        st[t] = false;

        for (int i = h[t]; ~i; i = ne[i])
        {
            int ver = e[i];
            if (f[i] && d[ver] > d[t] + w[i])
            {
                d[ver] = d[t] + w[i];
                pre[ver] = i;
                incf[ver] = min(f[i], incf[t]);
                if (!st[ver])
                {
                    q[tt ++ ] = ver;
                    if (tt == N) tt = 0;
                    st[ver] = true;
                }
            }
        }
    }
    return incf[T] > 0;
}

void EK(int& flow, int& cost)
{
    flow = cost = 0;
    while (spfa())
    {
        int t = incf[T];
        flow += t, cost += t * d[T];
        for (int i = T; i != S; i = e[pre[i] ^ 1])
        {
            f[pre[i]] -= t;
            f[pre[i] ^ 1] += t;
        }
    }
}

int a[85][85];
vector<vector<int>> di = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

void solve() {
    scanf("%d%d", &n, &m);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    memset(h, -1, sizeof h);
    S = n * m; T = n * m + 1;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            int id1 = i * m + j;
            if((i + j) % 2 == 1) {
                add(S, id1, 1, 0);
                for(vector<int>& p : di) {
                    int r = i + p[0], c = j + p[1];
                    if(r < 0 || c < 0 || r >= n || c >= m) continue;
                    int id2 = r * m + c;
                    if(a[i][j] != a[r][c]) {
                        add(id1, id2, 1, 1);
                    } else {
                        add(id1, id2, 1, 0);
                    }
                }
            } else {
                add(id1, T, 1, 0);
            }
        }
    }  
    
    int flow, cost;
    EK(flow, cost);
    int tot = n * m;
    cout << cost << endl;
    
} 


int main() {
	// your code goes here
	int t = 1;
	//cin >> t;
	while(t--) {
	    solve();
	}
	return 0;
}  
