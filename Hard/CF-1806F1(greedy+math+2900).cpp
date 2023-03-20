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
#include <iostream>
   
using ll = long long;
using namespace std;  

int n, m, k;
const int N = 2e6 + 10;
int a[N];
bool is[N];
void solve() {
    cin >> n >> m >> k;
    
    for(int i = 0; i <= m; i++) {
        is[i] = false;
    }
    
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);   
    }
    
    sort(a, a + n);

    ll sum = 0, res = 0;
    vector<ll> rep;
    for(int i = 0; i < n; i++) {
        sum += a[i];
        if(i == 0 || a[i] != a[i - 1]) {
            is[a[i]] = true;
        } else {
            rep.push_back(a[i]);
        }
    }

    for(int i = 1; i < rep.size(); i++) rep[i] += rep[i - 1];

    if(rep.size() >= k) {
        res = max(res, sum - rep[k - 1]);      
    }

    int first = a[0];
    //remove k + 1 elemenst and add back g
    for(int i = 1; i <= m; i++) {
        if(first % i != 0) continue;
        ll t = -i;
        int cnt = k + 1;
        for(int j = i; j <= m && cnt; j += i) {
            if(!is[j]) continue;
            t += j;
            cnt--;
            if(cnt <= rep.size()) {
                if(cnt == 0) res = max(res, sum - t);
                else res = max(res, sum - t - rep[cnt - 1]);
            }
        }
        //cout << i << " " << res << endl;
    }
    cout << res << endl;
}

int main() {
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
