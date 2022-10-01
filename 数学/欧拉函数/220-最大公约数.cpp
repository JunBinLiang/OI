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

const int N = 1e7 + 10;
int primes[N], cnt;
bool st[N];
int phi[N];
ll s[N];

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
    for(int i = 1; i <= n; i++) s[i] = s[i - 1] + phi[i];
}
 
int main() {
    int n;
    scanf("%d", &n);
    init(n + 1);
    ll res = 0;
    
    for(int i = 0; i < cnt; i++) {
        int p = primes[i];
        if(p > n) break;
        res += (s[n / p] * 2 - 1);
    }
    cout << res << endl;
    
    return 0;
}
