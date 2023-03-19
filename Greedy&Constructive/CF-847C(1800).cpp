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
#include <iostream>
   
using namespace std;  

using ll = long long;
#define pb push_back
#define ve vector
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define RFOR(i, a, b) for (int i = a; i >= b; i--)
#define f first
#define se second
#define W while
#define um unordered_map
#define us unordered_set
#define be begin
#define en end

int n;
const int N = 1e5 + 10, M = N * 2;
int e[M], ne[M], h[N], idx;
int dfn[N], low[N], timestamp;
bool is_bridge[M];

vector<pair<int, int>> ans;

void add(int a, int b)  // 添加一条边a->b
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}

void tarjan(int u, int from)
{
    dfn[u] = low[u] = ++ timestamp;
    //stk[ ++ top] = u;
    for (int i = h[u]; ~i; i = ne[i])
    {
        int j = e[i];
        if (!dfn[j])
        {
            tarjan(j, i);
            low[u] = min(low[u], low[j]);
            if (dfn[u] < low[j]) {
                //is_bridge[i] = is_bridge[i ^ 1] = true;
                ans.push_back({min(u, j), max(u, j)});
            }    
        }
        else if (i != (from ^ 1)) { //非反向边
            low[u] = min(low[u], dfn[j]);
        }
    }

    /*if (dfn[u] == low[u])
    {
        ++ dcc_cnt;
        int y;
        do {
            y = stk[top -- ];
            id[y] = dcc_cnt;
        } while (y != u);
    }*/
}


void solve() {
    int n; ll k;
    cin >> n >> k;
    ll tot = 0;
    for(int i = 0; i < n; i++) {
        tot += i;
    }

    if(tot < k) {
        cout << "Impossible" << endl;
        return;
    }

    string s = "";
    int cnt = 0;
    ll sum = 0;
    for(int i = 0; i < n; i++) {
        if(sum + cnt > k) {
            i--;
            s += ")";
            cnt--;
        } else {
            sum += cnt;
            cnt++;
            s += "(";
        }
    }

    while(s.size() != 2 * n) s += ")";
    cout << s << endl;
}

int main() {
    int t = 1;
    while(t--) {
        solve();    
    }
    return 0;
}
