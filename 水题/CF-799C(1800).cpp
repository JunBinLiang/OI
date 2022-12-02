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
int l1[N], l2[N];
vector<pair<int, int>> a, b;
int n, c, d;
int res = 0;
void cal() {
    int mx = -1;
    for(int i = 0; i < b.size(); i++) {
        if(b[i].first <= d) {
            mx = max(mx, l2[i]);
        }
    }

    for(int i = a.size() - 1; i >= 0; i--) {
        if(a[i].first > c) continue;
        int l = 0, r = i - 1;
        while(l <= r) {
            int mid = l + (r - l) / 2;
            if(a[i].first + a[mid].first <= c) {
                res = max(res, a[i].second + l1[mid]);
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }

        if(mx != -1) {
            res = max(res, mx + a[i].second);
        }
    }
}

void solve() {
    cin >> n >> c >> d;
    for(int i = 0; i < n; i++) {
        int earn, cost;
        string ty;
        cin >> earn >> cost >> ty;
        if(ty == "C") {
            a.push_back({cost, earn});
        } else {
            b.push_back({cost, earn});
        }
    }
    
    a.push_back({-1e9, -1e9});
    b.push_back({-1e9, -1e9});

    sort(a.begin(), a.end());
    sort(b.begin(), b.end()); 
    l1[0] = a[0].second;
    for(int i = 1; i < a.size(); i++) {
        l1[i] = max(l1[i - 1], a[i].second);
    }

    l2[0] = b[0].second;
    for(int i = 1; i < b.size(); i++) {
        l2[i] = max(l2[i - 1], b[i].second);
    }

    cal();
    swap(a, b);
    swap(l1, l2);
    swap(c, d);
    cal();

    cout << res << endl;

}

int main() {
    int t = 1;
    //cin >> t;  
    while(t --) {
        solve();
    }
    return 0;
}
