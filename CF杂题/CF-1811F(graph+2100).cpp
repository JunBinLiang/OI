
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
#include <map>

using namespace std;

using ll = long long;
#define pb push_back
#define ve vector


const int N = 2e5 + 10;
int n, m;
int deg[N], p[N];
vector<pair<int, int>> g[N];
bool vis[N], vis1[N];
int k = -1;

int find(int x)
{
    if (p[x] != x) p[x] = find(p[x]);
    return p[x];
}

void dfs1(int pa, int u, vector<pair<int, int>>& path) {
    vis[u] = true;
    
    for(auto & p: g[u]) {
        int v = p.first; int ith = p.second;
        if(deg[v] != 4 || v == pa) continue;
        if(!vis1[ith]) {
            path.push_back({u, v});
            vis1[ith] = true;
        }
        if(vis[v]) {
            

        } else {
            dfs1(u, v, path);
        }
    }
}

void dfs2(int pa, int u, vector<pair<int, int>>& path) {
    vis[u] = true;
    
    for(auto & p: g[u]) {
        int v = p.first; int ith = p.second;
        if(deg[v] != 2 || v == pa) continue;
        if(!vis1[ith]) {
            path.push_back({u, v});
            vis1[ith] = true;
        }
        if(vis[v]) {
            
        } else {
            dfs2(u, v, path);
        }
    }
}

void solve() {
    cin >> n >> m;
    k = -1;
    for(int i = 1; i <= n; i++) {
        deg[i] = 0; g[i].clear();
        vis[i] = false;
        p[i] = i;
    }    

    for(int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        deg[u]++; deg[v]++;
        g[u].push_back({v, i});
        g[v].push_back({u, i});
        vis1[i] = false;
    }

    for(int i = 3; i <= n; i++) {
        if(i * i == n) {
            k = i;
        } else if(i * i > n) {
            break;
        }
    }
    if(k == -1) {
        cout << "NO" << endl;
        return;
    }

    int cnt1 = 0, cnt2 = 0;
    for(int i = 1; i <= n; i++) {
        if(deg[i] != 2 && deg[i] != 4) {
            cout << "NO" << endl;
            return;
        }
        if(deg[i] == 2) {
            cnt1++;
        } else if(deg[i] == 4){
            cnt2++;
        }
    }

    if(cnt2 != k) {
        cout << "NO" << endl;
        return;
    }

    for(int i = 1; i <= n; i++) {
        if(deg[i] == 4) {
            vector<pair<int, int>> path;
            dfs1(-1, i, path);
            if(path.size() != k) {
                cout << "NO" << endl;
                return;
            }

            for(int j = 0; j < k; j++) {
                int u = path[j].first, v = path[j].second;
                int r1 = find(u); int r2 = find(v);
                if(j == k - 1) {
                    if(r1 != r2) {
                        cout << "NO" << endl;
                        return;
                    }
                } else {
                    if(r1 == r2) {
                        cout << "NO" << endl;
                        return;
                    }
                    p[r1] = r2;
                }
            }

            break;
        }
    }

    for(int i = 1; i <= n; i++) vis[i] = false, p[i] = i;
    for(int i = 0; i < m; i++) vis1[i] = false;


    for(int i = 1; i <= n; i++) {
        if(deg[i] == 4) {
            vector<pair<int, int>> path;
            dfs2(-1, i, path);
            if(path.size() != k) {
                cout << "NO" << endl;
                return;
            }

            for(int j = 0; j < k; j++) {
                int u = path[j].first, v = path[j].second;
                int r1 = find(u); int r2 = find(v);
                if(j == k - 1) {
                    if(r1 != r2) {
                        cout << "NO" << endl;
                        return;
                    }
                } else {
                    if(r1 == r2) {
                        cout << "NO" << endl;
                        return;
                    }
                    p[r1] = r2;
                }
            }
        }
    }
    cout << "YES" << endl;
}   


int main()
{   

    int t = 1;
    cin >> t;
    while(t --) {
        solve();
    }
    return 0;
}
