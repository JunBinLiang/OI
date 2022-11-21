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





void solve() {
    string s;
    cin >> s;
    map<char, int> f;
    f['Y'] = 0;
    f['e'] = 1;
    f['s'] = 2;

    if(f.find(s[0]) == f.end()) {
        cout << "NO" << endl;
        return;
    }

    int j = f[s[0]];
    for(int i = 1; i < s.size(); i++) {
        if(f.find(s[i]) == f.end()) {
            cout << "NO" << endl;
            return;
        }
        int nxt = (j + 1) % 3;
        if(f[s[i]] != nxt) {
            cout << "NO" << endl;
            return;
        }
        j = nxt;
    }
    cout << "YES" << endl;
}

int main() {
    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
