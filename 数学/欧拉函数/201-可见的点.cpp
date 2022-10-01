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

const int N = 1050;
int primes[N], cnt;
bool st[N];
int phi[N];
void init(int n)
{
    phi[1] = 1;
    for (int i = 2; i <= n; i ++ )
    {
        if (!st[i])
        {
            primes[cnt ++ ] = i;
            phi[i] = i - 1;
        }
        for (int j = 0; primes[j] * i <= n; j ++ )
        {
            st[i * primes[j]] = true;
            if (i % primes[j] == 0)
            {
                phi[i * primes[j]] = phi[i] * primes[j];
                break;
            }
            phi[i * primes[j]] = phi[i] * (primes[j] - 1);
        }
    }
}

int n;
int ca = 1;
void solve() {
    scanf("%d", &n);
    int res = 0;
    for(int i = 2; i <= n; i++) res += phi[i];
    cout << ca << " " << n << " " << res * 2 + 3 << endl;
}

int main() {
    int t;
    cin >> t;
    init(1010);
    while(t --) {
        solve();
        ca++;
    }
    return 0;
}
