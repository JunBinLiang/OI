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

const int N = 110;
int n, k;
int a[N];

vector<int> add() {
    int c = 1;
    vector<int> b;
    for(int i = n - 1; i >= 0; i--) {
        int v = -1;
        if(i == n - 1) {
            v = k - 1 + c;
        } else {
            v = a[i] + c;
        }
        c = (v >= k);
        v %= k;
        b.push_back(v);
    }
    if(c) b.push_back(c);
    reverse(b.begin(), b.end());
    return b;
}

void solve() {
    scanf("%d%d", &n, &k);
    set<int> se;
    int res = 0;
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        se.insert(a[i]);
    }

    if(se.size() == k) {
        printf("0\n");
        return;
    }

    int cnt = se.size();
    int x = a[n - 1];
    while(true) {
        auto it = se.upper_bound(x);
        if(it == se.end()) {
            res += (k - 1 - x);
            cnt += (k - 1 - x);
            x = k - 1;
            break;
        } else {
            if(*it == x) {
                se.erase(*it);
                continue;
            }
            cnt += ((*it) - x - 1);
            res += (*it) - x - 1;
            if(cnt == k) break;
            x = *it;
            res++;
            se.erase(*it);
        }
    }

    if(cnt == k) {
        printf("%d\n", res);
        return;
    }
    
    res++;
    vector<int> b = add();
    se.clear();
    for(int i = 0; i < n; i++) {
        if(a[i] <= a[n - 1] - 1)se.insert(a[i]);
    }
    for(int i = 0; i < b.size(); i++) {
        if(b[i] <= a[n - 1] - 1) se.insert(b[i]);
    }

    cnt = se.size();
    k = a[n - 1];
    x = 0;
    while(true) {
        auto it = se.upper_bound(x);
        if(it == se.end()) {
            res += (k - 1 - x);
            break;
        } else {
            if(*it == x) {
                se.erase(*it);
                continue;
            }
            cnt += ((*it) - x - 1);
            res += (*it) - x - 1;
            if(cnt == k) break;
            x = *it;
            res++;
            se.erase(*it);
        }
    }
    printf("%d\n", res);
}

int main() {
    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
