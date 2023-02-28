#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
using namespace std;  
using ll = long long;
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define pb push_back
#define ve vector



const int N = 2e5 + 10;
int a[N];
int p[20];
ll res = 0;

map<int, int> f[11];

int getL(int x) {
    int cnt = 0;
    while(x) cnt++, x /= 10;
    return cnt;
}

//4:40
void solve() {
    int n, k;
    cin >> n >> k;
    for(int i = 0; i < n; i++) {
        int x;
        scanf("%d", &a[i]);
    }
    
    p[0] = 1;
    for(int i = 1; i < 15; i++) {
        p[i] = ((p[i - 1] + 0ll) * 10 % k);
        p[i] %= k;
    }


    for(int i = 0; i < n; i++) {
        int x = a[i], l = getL(x);
        f[l][x % k]++;
        if(((x + 0ll) * p[l] + x) % k == 0) res--;
    }
    

    for(int i = 0; i < n; i++) {
        ll x = a[i];
        for(int j = 1; j <= 10; j++) {
            int o = (x * p[j]) % k;
            int need = (k - o) % k;
            if(f[j].find(need) != f[j].end()) {
                res += f[j][need];
            }
        }
    }

    cout << res << endl;

}

int main() {
    solve();
    return 0;
}
