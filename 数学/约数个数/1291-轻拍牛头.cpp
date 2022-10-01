#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1000010;

int n;
int a[N], cnt[N], s[N];

int main()
{
    scanf("%d", &n);

    for (int i = 0; i < n; i ++ )
    {
        scanf("%d", &a[i]);
        cnt[a[i]] ++ ;
    }

    for (int i = 1; i < N; i ++ )
        for (int j = i; j < N; j += i)
            s[j] += cnt[i];

    for (int i = 0; i < n; i ++ ) printf("%d\n", s[a[i]] - 1);
    return 0;
}
