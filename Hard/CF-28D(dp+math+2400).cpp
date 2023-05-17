
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <queue>
#include <deque>

using namespace std;





const int N = 1e5 + 10;
struct Node {
    int v, c, l, r, idx;
} a[N];
int nxt[N];
int n;
void solve() {
    cin >> n;
    for(int i = 0; i < n; i++) {
        //v : value
        //c : people
        //l : before
        //r : after
        int v, c, l, r;
        cin >> v >> c >> l >> r; 
        a[i] = {v, c, l, r, i};
    }

    map<pair<int, int>, int> f;
    map<pair<int, int>, int> g;
    
    
    for(int i = n - 1; i >= 0; i--) {
        if(a[i].r == 0) {
            int L = a[i].l, R = a[i].r + a[i].c;
            nxt[i] = i;
            pair<int, int> cur = {L, R};
            if(f.find(cur) == f.end()) {
                f[cur] = a[i].v;
                g[cur] = i;
            } else if(a[i].v > f[cur]) {
                f[cur] = a[i].v;
                g[cur] = i;
            }
        } else {
            pair<int, int> nxtp = {a[i].l + a[i].c, a[i].r};
            if(f.find(nxtp) != f.end()) {
                int L = a[i].l, R = a[i].r + a[i].c;
                pair<int, int> cur = {L, R};
                if(f.find(cur) == f.end()) {
                    f[cur] = a[i].v + f[nxtp];
                    g[cur] = i;
                    nxt[i] = g[nxtp];
                } else if(f[nxtp] + a[i].v > f[cur]) {
                    f[cur] = f[nxtp] + a[i].v;
                    g[cur] = i;
                    nxt[i] = g[nxtp];
                }
            }
        }
    }

    int res = 0;
    pair<int, int> cur = {-1, -1};
    for(auto it = f.begin(); it != f.end(); it++) {
        pair<int, int> p = it -> first;
        if(p.first == 0 && it -> second > res) {
            res = it -> second;
            cur = {p.first, p.second};
        }
    }
    
    if(cur.first == -1) {
        cout << 0 << endl;
        return;
    }
    
   // for(int i = 0; i < n; i++) cout << nxt[i] << " ";
    //cout << endl;
    
    
    vector<int> ans;
    int j = g[cur];
    while(true) {
        ans.push_back(j + 1);
        if(j == nxt[j]) break;
        j = nxt[j];
        cur = {a[j].l, a[j].r + a[j].c};
    }
    
    cout << ans.size() << endl;
    for(int i : ans) cout << i << " ";
    cout << endl;
    
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
