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
using ull = unsigned long long;
#define pb push_back

//ifstream fcin("test/input.txt");
//ofstream fcout("test/output.txt");

unsigned long long seed = 131;
unsigned long long rands(){ return seed = (seed << 15) + (seed << 8)+( seed >> 3);}
const int MOD = 998244353;

int cal(vector<int>& arr) {
    int n = arr.size();
    map<int, ull> hmp;
    for(int i = 0; i < n; i++) {
        if(hmp.find(arr[i]) == hmp.end()) {
            ull rd = rands();
            hmp[arr[i]] = rd;
        }
    }

    ull xo = 0;
    map<ull, int> f;
    vector<int> line(arr.size() + 1);
    for(int i = 0; i < arr.size(); i++) {
        xo ^= hmp[arr[i]];
        if(f.find(xo) != f.end()) {
            line[i + 1] -= 1;
            line[f[xo] + 1] += 1;
        }
        f[xo] = i;
    }
    
    int sum = 0;
    int count = 0;
    for(int i = 0; i < arr.size(); i++) {
        sum += line[i];
        if(sum == 0) {
            count++;
        }
    }

    return count;
}

void solve() {
    int n;
    scanf("%d", &n);
    vector<int> p(n), a(n * 2);
    for(int i = 0; i < 2 * n; i++) {
        scanf("%d", &a[i]);
        a[i]--;
        p[a[i]] = i;
    }

    vector<pair<int, int>> blocks;
    int last = 0, to = p[a[0]];
    for(int i = 0; i < a.size(); i++) {
        if(i > to) {
            blocks.push_back({last, to});
            last = i;
        }
        to = max(to, p[a[i]]);
    }
    blocks.push_back({last, to});
    
    ll res = 1;
    for(auto& p : blocks) {
        int l = p.first, r = p.second;
        vector<int> arr;
        for(int i = l; i <= r; i++) {
            arr.push_back(a[i]);
        }
        res *= (cal(arr));
        res %= MOD;
    }

    cout << blocks.size() << " " << res << endl;

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

