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
const int N = 300000 + 50;
int s[N];
pair<int, int> mono[N];
int l = 0, r = -1;


void solve() {
    int n, k;
    int res = -1000000000;
    scanf("%d%d", &n, &k);
    for(int i = 0; i < n; i++) {
        scanf("%d", &s[i]);
        if(i) s[i] += s[i - 1];
    }
    
    for(int i = 0; i < n; i++) {
        while(r - l + 1 > 0 && i - mono[l].first > k) l++;
        if(i + 1 <= k) res = max(res, s[i]);
        if(r - l + 1 > 0) {
            res = max(res, s[i] - mono[l].second);
        }
        //add
        while(r - l + 1 > 0 && s[i] < mono[r].second) r--;
        mono[++r] = {i, s[i]};
    }
    
    printf("%d \n", res);
}

int main() {
    int t = 1;
    while(t--) {
        solve();
    }
}
