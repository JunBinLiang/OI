#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long LL;
const int N = 1010, MOD = 1e9 + 7;

int n, m;
int f[N][N];

int main()
{
    cin >> n >> m;
    f[0][0] = 1;
    for (int i = 1; i <= n; i ++ )
        for (int j = 1; j <= m; j ++ )
            f[i][j] = (f[i - 1][j - 1] + (LL)j * f[i - 1][j]) % MOD;
    cout << f[n][m] << endl;
    return 0;
}

