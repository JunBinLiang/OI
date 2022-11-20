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

const int N = 2e5 + 10;
int b[N];
int n;
void solve() {
    scanf("%d", &n);
    int m = n / 2;
    set<int> se;
    vector<int> res;
    for(int i = 1; i <= n; i++) se.insert(i);
    for(int i = 0; i < m; i++) {
        scanf("%d", &b[i]);
        se.erase(b[i]);
    }
    if(se.size() != m) {
        printf("-1\n");
        return;
    }

    for(int i = m - 1; i >= 0; i--) {
        res.push_back(b[i]);
        auto it = se.upper_bound(b[i]);
        if(it == se.begin()) {
            printf("-1\n");
            return;
        }
        it--;
        res.push_back(*it);
        se.erase(*it);
    }

    reverse(res.begin(), res.end());
    for(int i : res) {
        printf("%d ", i);
    }
    printf("\n");

}

int main() {
    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
