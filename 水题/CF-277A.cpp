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

int find(vector<int>& nums, int x){
  if(nums[x] == x) return x;
  int root = find(nums, nums[x]);
  nums[x] = root;
  return root;
}


int n, m;
const int N = 110;
vector<int> g[N];
int cnt = 0;
void solve() {
    cin >> n >> m;
    for(int i = 0; i < n; i++) {
        int t;
        cin >> t;
        if(!t) cnt++;
        while(t--) {
            int u;
            cin >> u;
            g[i].push_back(u);
        }
    }

    vector<int> nums(n);
    for(int i = 0; i < n; i++) {
        nums[i] = i;
    }

    for(int i = 0; i < n; i++) {
        set<int> s(g[i].begin(), g[i].end());
        for(int j = i + 1; j < n; j++) {
            for(int v : g[j]) {
                if(s.find(v) != s.end()) {
                    int r1 = find(nums, i); int r2 = find(nums, j);
                    if(r1 != r2) {
                        nums[r1] = r2;
                    }
                }
            }
        }
    }

    if(cnt == n) {
        cout << cnt << endl;
        return;
    }

    set<int> all;
    for(int i = 0; i < n; i++) {
        int r = find(nums, i);
        all.insert(r);
    }

    int tot = all.size();
    cout << tot - 1 << endl;



}

int main() {
    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
