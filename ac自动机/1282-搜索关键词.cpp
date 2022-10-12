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

using namespace std;

using ll = long long;
#define pb push_back
#define ve vector
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define RFOR(i, a, b) for (int i = a; i >= b; i--)
#define f first
#define se second
#define W while
#define um unordered_map
#define us unordered_set
#define be begin
#define en end

const int N = 10010, S = 55, M = 1000010;
int q[N * S], ne[N * S];
int cnt[N * S];
int tr[N * S][26];
char str[M];
int n, idx;



void insert()  // 将str插入Trie中
{
    int p = 0;
    for (int i = 0; str[i]; i ++ )
    {
        int u = str[i] - 'a';
        if (!tr[p][u]) tr[p][u] = ++ idx;
        p = tr[p][u];
    }
    cnt[p] ++ ;  // 记录单词出现次数
}

void build()  // 创建AC自动机
{
    int hh = 0, tt = 0;
    for (int i = 0; i < 26; i ++ )
        if (tr[0][i]) {
            q[ tt ++] = tr[0][i];
        }
            
    
    while (hh != tt)
    {
        int t = q[hh ++ ];
        for (int i = 0; i < 26; i ++ )
        {
            int p = tr[t][i];
            if (!p) continue;
            int j = ne[t];
            while(j && !tr[j][i]) j = ne[j];
            if(tr[j][i]) j = tr[j][i];
            ne[p] = j;
            q[tt ++] = p;
        }
    }
}


void solve() {
    memset(tr, 0, sizeof tr);
    memset(cnt, 0, sizeof cnt);
    memset(ne, 0, sizeof ne);
    idx = 0;
    
    
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        scanf("%s", str);
        insert();
    }
    
    build();
    
    scanf("%s", str);
    int res = 0;
    for(int i = 0, j = 0; str[i]; i++) {
        int t = str[i] - 'a';
        while(j && !tr[j][t]) j = ne[j];
        if(tr[j][t]) j = tr[j][t];
        int p = j;
        while (p)
        {
            res += cnt[p];
            cnt[p] = 0;
            p = ne[p];
        }
    }
    printf("%d \n", res);
}

int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        solve();
    }
    return 0;
}



/*fast

#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 10010, S = 55, M = 1000010;

int n;
int tr[N * S][26], cnt[N * S], idx;
char str[M];
int q[N * S], ne[N * S];

void insert()
{
    int p = 0;
    for (int i = 0; str[i]; i ++ )
    {
        int t = str[i] - 'a';
        if (!tr[p][t]) tr[p][t] = ++ idx;
        p = tr[p][t];
    }
    cnt[p] ++ ;
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
            }
        }
    }
}

int main()
{
    int T;
    scanf("%d", &T);
    while (T -- )
    {
        memset(tr, 0, sizeof tr);
        memset(cnt, 0, sizeof cnt);
        memset(ne, 0, sizeof ne);
        idx = 0;

        scanf("%d", &n);
        for (int i = 0; i < n; i ++ )
        {
            scanf("%s", str);
            insert();
        }

        build();

        scanf("%s", str);

        int res = 0;
        for (int i = 0, j = 0; str[i]; i ++ )
        {
            int t = str[i] - 'a';
            j = tr[j][t];

            int p = j;
            while (p)
            {
                res += cnt[p];
                cnt[p] = 0;
                p = ne[p];
            }
        }

        printf("%d\n", res);
    }

    return 0;
}


*/
