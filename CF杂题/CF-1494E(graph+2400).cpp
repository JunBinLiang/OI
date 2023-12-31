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
#include<fstream>
#include <bitset>

using namespace std;  
using ll = long long;
using ull = unsigned long long;
#define pb push_back


map<pair<int, int>, char> f;
int o[2];
void solve() {
    int n, m;
    cin >> n >> m;

    memset(o, 0, sizeof o);

    for(int i = 0; i < m; i++) {
        char op;
        cin >> op;
        if(op == '+') {
            int u, v; char c;
            cin >> u >> v >> c;
            f[{u, v}] = c;
            if(f.find({v, u}) != f.end()) {
                o[1]++;
                if(f[{v, u}] == c) o[0]++;
            }
        } else if(op == '-') {
            int u, v;
            cin >> u >> v;
            char c = f[{u, v}];
            f.erase({u, v});
            if(f.find({v, u}) != f.end()) {
                o[1]--;
                if(c == f[{v, u}]) o[0]--;
            }
        } else {
            int k;
            cin >> k;
            if(o[k % 2] > 0) {
                cout << "YES" << endl;
            } else {
                cout << "NO" << endl;
            }
        }

    }
}

int main()
{
    int t = 1;
    //cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
