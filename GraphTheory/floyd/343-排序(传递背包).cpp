#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <cstring>
#include <algorithm>


using namespace std;  
using ll = long long;
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define pb push_back
#define ve vector
typedef pair<int, int> PII;
typedef pair<double, double> PDD;


const int N = 26, INF = 1e9;
int g[N][N], d[N][N];
bool st[N];
int n, m;

void floyd() {
    memcpy(d, g, sizeof d);
    
    for (int k = 0; k < n; k ++ )
        for (int i = 0; i < n; i ++ )
            for (int j = 0; j < n; j ++ )
                d[i][j] |= d[i][k] && d[k][j];
}


int check()
{
    for (int i = 0; i < n; i ++ )
        if (d[i][i])
            return 2;

    for (int i = 0; i < n; i ++ )
        for (int j = 0; j < i; j ++ )
            if (!d[i][j] && !d[j][i])
                return 0;

    return 1;
}

char get() {
    
    for(int i = 0; i < n; i++) {
        if(st[i]) continue;
        //none of can reach to i
        bool bad = false;
        for(int j = 0; j < n; j++) {
            if(!st[j] && d[j][i]) {
                bad = true;
            }
        }
        if(!bad) {
            st[i] = true;
            return 'A' + i;
        }
    }
    return ' ';
    
}

void solve() {
    while (cin >> n >> m, n || m) {
        int type = 0, ans = 0;
        memset(g, 0, sizeof g);
        for(int i = 1; i <= m; i++) {
            string s;
            cin >> s;
            int a = s[0] - 'A', b = s[2] - 'A';
            if(!type) { //not finish
                g[a][b] = 1;
                floyd();
                type = check();
                if(type) ans = i;
            }
        }
        
        if (!type) puts("Sorted sequence cannot be determined.");
        else if (type == 2) printf("Inconsistency found after %d relations.\n", ans);
        else {
            memset(st, false, sizeof st);
            string s = "";
            for(int i = 0; i < n; i++) s += get();
            cout << "Sorted sequence determined after " << ans << " relations: " << s << "." << endl;
        }
    }
}

int main() {
    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}



