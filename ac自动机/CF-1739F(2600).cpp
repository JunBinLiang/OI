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

template <typename T>
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} 
  out << "]";
  return out;
}


const int N = 2010;
int a[N], in[13];
bool visit[13];
bool bad = false;
string s[N];
bool is[13][13];
vector<int> g[13];
int n;

int dp[1 << 12][ N * 2];
int f[1 << 12][N * 2];
int tr[N * 2][26];

int add[N * 2], ne[N * 2];
int q[N * 2 + 100];
int idx = 0;
void insert(string& str, int score) {
    int p = 0;
    for (int i = 0; i < str.size(); i ++ )
    {
        int t = str[i] - 'a';
        if (!tr[p][t]) tr[p][t] = ++ idx;
        p = tr[p][t];
    }
    add[p] += score;
}


void build() {
    int hh = 0, tt = -1;
    for (int i = 0; i < 26; i ++ )
        if (tr[0][i])
            q[ ++ tt] = tr[0][i];
    while (hh <= tt)
    {
        int t = q[hh ++ ];
        for (int i = 0; i < 26; i ++ )
        {
            int p = tr[t][i];
            if (!p) tr[t][i] = tr[ne[t]][i];
            else
            {
                ne[p] = tr[ne[t]][i];
                q[ ++ tt] = p;
            }
        }
    }
}


int dfs(int state, int pIdx) {
    if(state == 0) {
        return 0;
    }
    if(dp[state][pIdx] != -1) {
        return dp[state][pIdx];
    }
    
    int mx = -1, nxt = -1;
    for(int i = 0; i < 12; i++) {
        if(state & (1 << i)) {
            int news = state ^ (1 << i);
            int j = tr[pIdx][i];
            int p = j;
            int sum = 0;
            while (p)
            {
                sum += add[p];
                p = ne[p];
            }
            sum += dfs(news, j);
            if(sum > mx) {
                mx = sum;
                nxt = i;
            }
        }
    }
    //cout << state << " " << pIdx << "  " << nxt << "  " << mx << endl;
    f[state][pIdx] = nxt;
    return dp[state][pIdx] = mx;
}

void dfs1(string& t, int pa, int root) {
    if(bad) return;
    char c = (char)(root + 'a');
    t += c;
    for(int nxt : g[root]) {
        if(nxt == pa) continue;
        if(visit[nxt]) {
            bad = true;
        }
        dfs1(t, root, nxt);
    }
}

void solve() {
    scanf("%d", &n);
    //memset(add, 0, sizeof add);
    //memset(tr, 0, sizeof tr);
    memset(dp, -1, sizeof dp);
    for(int i = 0; i < n; i++) {
        cin >> a[i] >> s[i];
        memset(in, 0, sizeof in);
        memset(is, false, sizeof is);
        memset(visit, false, sizeof visit);
        for(int j = 0; j < 13; j++) g[j].clear();

        for(int j = 1; j < s[i].size(); j++) {
            int u = s[i][j - 1] - 'a';
            int v = s[i][j] - 'a';
            if(!is[u][v]) {
                is[u][v] = true;
                is[v][u] = true;
                g[u].pb(v);
                g[v].pb(u);
                in[u]++, in[v]++;
            }
        }
        
        bad = false;
        string t = "";
        int root = -1;
        for(int j = 0; j < 13; j++) {
            if(in[j] == 1) {
                root = j; 
                break;
            }
        }
        for(int j = 0; j < 13; j++) {
            if(in[j] > 2) bad = true;
        }
        
        if(root == -1) continue;
        dfs1(t, -1, root);
        if(t.size() == 0 || bad) continue;
        insert(t, a[i]);
        reverse(t.begin(), t.end());
        insert(t, a[i]);     
    }

    build();

    int s = (1 << 12) - 1;
    int pIdx = 0;
    int all = dfs(s, pIdx);
    string res = "";
    while(s > 0) {
        int nxt = f[s][pIdx];
        char c = (char)(nxt + 'a');
        res += c;
        s ^= (1 << nxt);
        pIdx = tr[pIdx][nxt];
    }
    cout << res << endl;

} 

int main() {
    int t = 1;
    //cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
