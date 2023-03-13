#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 310, M = 10010;

int n, m;
struct Edge
{
    int a, b, w;
    bool operator< (const Edge &t) const
    {
        return w < t.w;
    }
}e[M];
int p[N];

int find(int x)
{
    if (p[x] != x) p[x] = find(p[x]);
    return p[x];
}

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i ++ ) p[i] = i;
    for (int i = 0; i < m; i ++ )
    {
        int a, b, w;
        cin >> a >> b >> w;
        e[i] = {a, b, w};
    }
    sort(e, e + m);

    int res = 0;
    for (int i = 0; i < m; i ++ )
    {
        int a = find(e[i].a), b = find(e[i].b), w = e[i].w;
        if (a != b)
        {
            p[a] = b;
            res = w;
        }
    }

    cout << n - 1 << ' ' << res << endl;

    return 0;
}
