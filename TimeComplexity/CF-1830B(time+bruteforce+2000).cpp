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


const int N = 2e5 + 10;
unordered_map<int, int> maps[N];

void solve() {
    int n; ll res = 0;
    cin >> n;
    vector<int> a(n), b(n);
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    for(int i = 0; i < n; i++) {
        scanf("%d", &b[i]);
    }
    for(int i = 0; i <= n; i++) maps[i].clear();

    vector<pair<int, int>> c;
    for(int i = 0; i < n; i++) {
        c.push_back({a[i], b[i]});
    }

    sort(c.begin(), c.end());
    vector<int> d;
    for(int i = 0; i < c.size(); i++) {
        int j = i;
        int v = c[i].first;
        while(j < c.size() && c[i].first == c[j].first) {
            maps[v][c[j].second]++;
            j++;
        }
        d.push_back(v);
        i = j - 1;
    }

    int lim = (int)(sqrt(2 * n) + 1);
    
    for(int i = d.size() - 1; i >= 0; i--) {
        int v1 = d[i];
        if(v1 <= lim) break;
        for(auto it = maps[v1].begin(); it != maps[v1].end(); it++) {
            int bi = it -> first;
            for(int j = 0; j < i; j++) {
                int v2 = d[j];
                if((v1 + 0ll) * v2 > 2 * n) break;
                int bj = v1 * v2 - bi;
                if(maps[v2].find(bj) != maps[v2].end()) {
                    res += ((it -> second + 0ll) * maps[v2][bj]);
                }
            }
        }

    }

    for(int i = 0; i < d.size(); i++) {
        int v1 = d[i];
        if(v1 > lim) break;
        for(auto it = maps[v1].begin(); it != maps[v1].end(); it++) {
            int bi = it -> first;
            for(int j = i + 1; j < d.size(); j++) {
                int v2 = d[j];
                if(v2 > lim) break;
                if((v1 + 0ll) * v2 > 2 * n) break;
                int bj = v1 * v2 - bi;
                if(maps[v2].find(bj) != maps[v2].end()) {
                    res += ((it -> second + 0ll) * maps[v2][bj]);
                }
            }
        }
 
        if((v1 + 0ll) * v1 <= 2 * n) {
            int sum = v1 * v1;
            for(auto it = maps[v1].begin(); it != maps[v1].end(); it++) {
                int com = sum - it -> first;
                if(maps[v1].find(com) == maps[v1].end() || it -> first > com) continue;
                if(it -> first == com) {
                    ll cnt = it -> second;
                    res += (cnt * (cnt - 1) / 2);
                } else {
                    res += ((it -> second + 0ll) * maps[v1][com]);
                }
            }
        }
    }


    printf("%lld\n", res);
}
    

int main()
{

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
