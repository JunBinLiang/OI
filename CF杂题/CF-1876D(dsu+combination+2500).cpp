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

const int MOD = 998244353;
const int N = 2e5 + 10;
int po[N], p[N], cnt[N];

int find(int u) {
    return p[u] == u ? u : p[u] = find(p[u]);
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }

    //init
    po[0] = 1;
    for(int i = 1; i < N; i++) po[i] = (po[i - 1] * 2) % MOD, p[i] = i, cnt[i] = 0;
    

    queue<int> q;
    bool ok = true;
    for(int i = 0; i < n; i++) {
        cnt[a[i]]++;
        if(!ok) {
            continue;
        }

        if(cnt[a[i]] % 2 == 1) {
            if(q.size() > 0) {
                int r1 = find(a[i]), r2 = find(q.front());
                if(r1 != r2) p[r1] = r2;
            }
            q.push(a[i]);
        } else {
            if(q.front() != a[i]) {
                ok = false;
            } else {
                q.pop();
            }
        }
    }
    if(q.size() != 0) ok = false;

    int count1 = 0, count2 = 0;
    set<int> s;
    for(int i = 1; i < N; i++) {
        if(cnt[i]) {
            count1++;
            if(cnt[i] % 2 == 1) {
                ok = false;
            }
            s.insert(find(i));
            count2 = s.size();
        }
    }
    
    //cout << count1 << " " << count2 <<"  " << ok << endl;

    if(!ok) {
        cout << (po[count1 - 1] + MOD) % MOD << endl; 
    } else {
        int x = (po[count1 - 1] + MOD) % MOD;
        int y = (po[count2 - 1] + MOD) % MOD;
        cout << (x - y + MOD) % MOD << endl;
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
