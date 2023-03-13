#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 310;

int n, m;
struct Edge
{
    int a, b, w;
    bool operator< (const Edge &t)const
    {
        return w < t.w;
    }
} e[N * N + N];
int k = 0;
int p[N], g[N][N];

int find(int x)
{
    if (p[x] != x) p[x] = find(p[x]);
    return p[x];
}

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i ++ ) p[i] = i;

    for(int i = 1; i <= n; i++) {
        int w;
        cin >> w;
        e[k++] = {0, i, w};
    }

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            int w;
            cin >> w;
            e[k++] = {i, j, w};
        }
    }

    sort(e, e + k);

    int res = 0;
    for (int i = 0; i < k; i ++ )
    {
        int a = find(e[i].a), b = find(e[i].b), w = e[i].w;
        if (a != b) p[a] = b, res += w;
    }

    cout << res << endl;

    return 0;
}
