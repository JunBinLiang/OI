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

const int N = 1e5 + 10;
ll a[N];
int main() {
    int n; 
    scanf("%d", &n);
    for(int i = 0; i < n; i++) scanf("%lld", &a[i]);
    
    int k = 0;
    for(int i = 62; i >= 0; i--) {
        for(int j = k; j < n; j++) {
            if(a[j] & (1ll << i)) {
                swap(a[k], a[j]);
                break;
            }
        }
        //not found
        if((a[k] & (1ll << i)) == 0) {
            continue;
        }
        
        for(int j = 0; j < n; j++) {
            if(j != k && (a[j] & (1ll << i))) {
                a[j] ^= a[k]; 
            }
        }
        k++;
        if(k == n) break;
    }
    
    ll res = 0;
    for(int i = 0; i < k; i++) {
        res ^= a[i];
    }
    cout << res << endl;
    
    return 0;
}
