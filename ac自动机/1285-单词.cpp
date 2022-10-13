#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;


const int N = 1e6 + 10;
int tr[N][26];
int q[N], ne[N];
int ids[250];
int f[N];
int idx = 0;
char str[N];
int tail = -1;
void insert(int id)
{
    int p = 0;
    for (int i = 0; str[i]; i ++ )
    {
        int t = str[i] - 'a';
        if (!tr[p][t]) tr[p][t] = ++ idx;
        p = tr[p][t];
        f[p] ++;
    }
    ids[id] = p;
}

void build()
{
    int hh = 0, tt = -1;
    for (int i = 0; i < 26; i ++ )
        if (tr[0][i])
            q[ ++ tt] = tr[0][i];
    
    while (hh <= tt)
    {
        int t = q[hh ++ ];
        for (int i = 0; i < 26; i ++ )
        {
            int p = tr[t][i];
            if (!p) tr[t][i] = tr[ne[t]][i];
            else
            {
                ne[p] = tr[ne[t]][i];
                q[ ++ tt] = p;
                tail = tt;
            }
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        scanf("%s", str);
        insert(i);
    }
    
    build();
    
    for(int i = tail; i >= 0; i -- ) f[ne[q[i]]] += f[q[i]];
    for(int i = 0; i < n; i++) printf("%d \n", f[ids[i]]);
    
    return 0;
}
