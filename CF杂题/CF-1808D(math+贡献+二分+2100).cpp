#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
#include <unordered_map>

using namespace std;

using ll = long long;
#define pb push_back
#define ve vector



//12:50
const int N = 2e5 + 10;
int a[N];
vector<pair<int, int>> o[N], e[N];
int n, k;

int bin(vector<pair<int, int>>& a, int left, int right) {
    int p1 = -1, p2 = -1;
    int l = 0, r = a.size() - 1;
    while(l <= r) {
        int mid = l + (r - l) / 2;
        if(a[mid].first >= left) {
            p1 = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }

    l = 0; r = a.size() - 1;
    while(l <= r) {
        int mid = l + (r - l) / 2;
        if(a[mid].first <= right) {
            p2 = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    
   // cout << p1 << "  " << p2 << endl;

    if(p1 == -1 || p2 == -1) return 0;
    return a[p2].second - a[p1].second + 1;

}

void solve() {
    scanf("%d%d", &n, &k);
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        if(i % 2 == 0) {
            if(e[a[i]].size() == 0) e[a[i]].push_back({i, 1});
            else {
                e[a[i]].push_back({i, 1 + e[a[i]].back().second});
            }
        } else {
            if(o[a[i]].size() == 0) o[a[i]].push_back({i, 1});
            else {
                o[a[i]].push_back({i, 1 + o[a[i]].back().second});
            }
        }
    }
    
    //for(auto p: o[2]) {
        //cout << p.first << " " << p.second << endl;
   // }
    //cout << bin(o[2], 3, 5) << endl;
    


    ll res = 0;
    int half = k / 2;
    for(int i = 0; i < n; i++) {
        int v = a[i];
        
        int l = max(0, i - half);
        int ith = i - l;
        int left = (k - ith - 1) + l;
        if(left >= n) continue;
        if(l + k - 1 >= n) continue;
        int move = (n - (l + k - 1 + 1));
        move = min(move, half);
        move = min(move, i);
        
        int right = min(n - 1, left + 2 * move);
        int cnt = (right - left) / 2 + 1;
        
        //cout << move <<"  "  << (n - (l + k - 1  +1)) << endl;
        //if(i % 2 == 0)
            //cout << v << "  :" << left << " " << right << " " << cnt <<"   |" << bin(e[v], left, right) << endl;
        //else cout << v << "  :" << left << " " << right << " " << cnt <<"   |" << bin(o[v], left, right) << endl;

        //cout << endl;

        if(i % 2 == 0) {
            res += (cnt - bin(e[v], left, right));
        } else {
            res += (cnt - bin(o[v], left, right));
        }
    }

    cout << res << endl;
}

int main()
{   

    int t = 1;
    //cin >> t;
    while(t --) {
        solve();
    }
    return 0;
}
