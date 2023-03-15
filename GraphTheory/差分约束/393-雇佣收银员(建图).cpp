#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 30, M = 100, INF = 0x3f3f3f3f;

int n;
int h[N], e[M], w[M], ne[M], idx;
int r[N], num[N];
int dist[N];
int q[N], cnt[N];
bool st[N];

void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++ ;
}

void build(int c)
{
    memset(h, -1, sizeof h);
    idx = 0;
    add(0, 24, c), add(24, 0, -c);//固定这的值
        
    for (int i = 1; i <= 7; i ++ ) add(i + 16, i, r[i] - c);
    for (int i = 8; i <= 24; i ++ ) add(i - 8, i, r[i]);
    for (int i = 1; i <= 24; i ++ )
    {
        add(i, i - 1, -num[i]);
        add(i - 1, i, 0);
    }
}

bool spfa(int c)
{
    build(c);

    memset(dist, -0x3f, sizeof dist);
    memset(cnt, 0, sizeof cnt);
    memset(st, 0, sizeof st);

    int hh = 0, tt = 1;
    dist[0] = 0;
    q[0] = 0;
    st[0] = true;

    while (hh != tt)
    {
        int t = q[hh ++ ];
        if (hh == N) hh = 0;
        st[t] = false;

        for (int i = h[t]; ~i; i = ne[i])
        {
            int j = e[i];
            if (dist[j] < dist[t] + w[i])
            {
                dist[j] = dist[t] + w[i];
                cnt[j] = cnt[t] + 1;
                if (cnt[j] >= 25) return false;
                if (!st[j])
                {
                    q[tt ++ ] = j;
                    if (tt == N) tt = 0;
                    st[j] = true;
                }
            }
        }
    }

    return true;
}

int main()
{
    int T;
    cin >> T;
    while (T -- )
    {
        for (int i = 1; i <= 24; i ++ ) cin >> r[i];
        cin >> n;
        memset(num, 0, sizeof num);
        for (int i = 0; i < n; i ++ )
        {
            int t;
            cin >> t;
            num[t + 1] ++ ;
        }

        bool success = false;
        for (int i = 0; i <= 1000; i ++ )
            if (spfa(i))
            {
                cout << i << endl;
                success = true;
                break;
            }

        if (!success) puts("No Solution");
    }

    return 0;
}
