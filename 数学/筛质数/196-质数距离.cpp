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

const int N = 1000010;
int primes[N], cnt;
bool st[N];
bool is[N];

void init(int n)
{
    for (int i = 2; i <= n; i ++ )
    {
        if (!st[i]) primes[cnt ++ ] = i;
        for (int j = 0; primes[j] * i <= n; j ++ )
        {
            st[primes[j] * i] = true;
            if (i % primes[j] == 0) break;
        }
    }
}

ll get(ll x, ll p) {
    ll res = x / p * p;
    if(res < x) res += p;
    return res;
}

int main() {
    init(50000);
    int l, r;
    while(cin >> l >> r) {
        //[l : r]

        memset(is, false, sizeof(is));
        for(int i = 0; i < cnt; i++) {
            ll p = primes[i];
            for(ll j = max(2 * p, get(l, p)); j <= r; j += p) {
                is[j - l] = true;
            }
        }
        
        
        
        int pcnt = 0;
        int last = -1;
        int mn = 1e9, mx = -1e9;
        int x1, y1, x2, y2;
        for(ll i = max(l, 2); i <= r; i++) {
            int idx = (int)(i - l);
            if(!is[idx]) {
                pcnt++;
                if(last == -1) {

                } else {
                    int dif = i - last;
                    if(dif > mx) {
                        mx = dif;
                        x1 = last, y1 = i;
                    }
                    if(dif < mn) {
                        mn = dif;
                        x2 = last, y2 = i;
                    }
                }
                last = i;
            }
        }
        
        if(pcnt < 2) {
            printf("There are no adjacent primes. \n");
        } else {
            printf("%d,%d are closest, %d,%d are most distant. \n", x2, y2, x1, y1);
        }
    }
    
}
