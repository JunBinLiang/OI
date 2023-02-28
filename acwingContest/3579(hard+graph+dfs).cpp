#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <cstring>
#include <algorithm>

using namespace std;  
using ll = long long;
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define pb push_back
#define ve vector





//6:33 - 6:42
const int N = 2e5 + 10;
int n;
int p[N];
bool is[N];
int res[N];

vector<int> pa;

void dfs(int idx) {
    if(is[idx]) {
        return;
    }
    pa.push_back(idx);
    is[idx] = true;
    dfs(p[idx]);
}

void solve() {
    cin >> n;
    for(int i = 0; i < n; i++) {
        scanf("%d", &p[i]);
        p[i]--;
        is[i] = false;
    }

    for(int i = 0; i < n; i++) {
        if(is[i]) continue;
        pa.clear();
        dfs(i);
        for(int j : pa) {
            res[j] = pa.size();
        }
    }

    for(int i = 0; i < n; i++) {
        printf("%d ", res[i]);
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
