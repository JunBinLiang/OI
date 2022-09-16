#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

const int N = 10000010;

int n, m;
int tot = 1, last = 1;
char str[N];
struct Node
{
    int len, fa;
    int ch[4];
}node[N * 2];

inline int get(char c)
{
    if (c == 'E') return 0;
    if (c == 'S') return 1;
    if (c == 'W') return 2;
    return 3;
}

void extend(int c)
{
    int p = last, np = last = ++ tot;
    node[np].len = node[p].len + 1;
    for (; p && !node[p].ch[c]; p = node[p].fa) node[p].ch[c] = np;
    if (!p) node[np].fa = 1;
    else
    {
        int q = node[p].ch[c];
        if (node[q].len == node[p].len + 1) node[np].fa = q;
        else
        {
            int nq = ++ tot;
            node[nq] = node[q], node[nq].len = node[p].len + 1;
            node[q].fa = node[np].fa = nq;
            for (; p && node[p].ch[c] == q; p = node[p].fa) node[p].ch[c] = nq;
        }
    }
}

int main()
{
    scanf("%d%d", &n, &m);
    scanf("%s", str);
    for (int i = 0; str[i]; i ++ ) extend(get(str[i]));
    while (m -- )
    {
        scanf("%s", str);
        int p = 1, res = 0;
        for (int i = 0; str[i]; i ++ )
        {
            //直接遍历图
            int c = get(str[i]);
            if (node[p].ch[c]) p = node[p].ch[c], res ++ ;
            else break;
        }
        printf("%d\n", res);
    }

    return 0;
}
