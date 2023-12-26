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


using namespace std;  
using ll = long long;
#define pb push_back

//ifstream fcin("test/input.txt");
//ofstream fcout("test/output.txt");
const int N = 5e5 + 10;
ll a[N], line[N];
map<int, ll> f;
void solve() {
    int n, m;
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
    }

    for(int i = 0; i <= n; i++) line[i] = 0;
    f.clear();
    
    scanf("%d", &m);
    for(int i = 0; i < m; i++) {
        int l, r, w;
        scanf("%d%d%d", &l, &r, &w);
        l--; r--;
        f[l] += w; 
        f[r + 1] -= w;
        while(f.size() > 0 && (f.begin() -> second) == 0) {
            f.erase(f.begin() -> first);
        }

        if(f.size() > 0 && f.begin() -> second < 0) {
            //clear the map
            for(auto it = f.begin(); it != f.end(); it++) {
                line[it -> first] += it -> second;
            }
            f.clear();
        }
    }


    ll sum = 0;
    for(int i = 0; i < n; i++) {
        sum += line[i];
        printf("%lld ", a[i] + sum);
    }
    printf("\n");

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

