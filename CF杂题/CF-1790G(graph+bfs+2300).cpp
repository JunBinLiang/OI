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

const int N = 2e5 + 10;
const int INF = 1e9;
int n, m;
int p, pp;
int a[N], b[N];
int dis[N], cnt[N];
bool is[N], visit[N];
vector<int> g[N];
void dfs(vector<int>& path, int root) {
    visit[root] = true;
    path.push_back(root);
    for(int& nxt : g[root]) {
        if(visit[nxt] || !is[nxt]) continue;
        dfs(path, nxt);
    }
}



bool one = false;
void solve() {
    
    scanf("%d%d", &n, &m);
    scanf("%d%d", &p, &pp);
    //clean
    one = false;
    for(int i = 0; i <= n; i++) {
        g[i].clear();
        dis[i] = INF;
        cnt[i] = 0;
        visit[i] = is[i] = false;
    }
    
    for(int i = 0; i < p; i++) {
        scanf("%d", &a[i]); //token
        if(a[i] == 1) one = true;
    }


    for(int i = 0; i < pp; i++) {
        scanf("%d", &b[i]); //bonus
        is[b[i]] = true;
    }
    
    
    for(int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }

    

    if(one) {
        printf("YES\n");
        return;
    }
    
    queue<int> q;
    q.push(1);
    dis[1] = 0;
    while(q.size() > 0) {
        int root = q.front(); q.pop();
        for(int& nxt : g[root]) {
            if(dis[root] + 1 < dis[nxt]) {
                dis[nxt] = dis[root] + 1;
                if(is[nxt]) {
                    q.push(nxt);
                }
            }
        }
    }

    vector<pair<int, int>> tokens;
    for(int i = 0; i < p; i++) {
        int token = a[i];
        if(dis[token] != INF) { //can reach
            tokens.push_back({dis[token], token});
            //cout << "token  " << token << "  " << dis[token] << endl;
        } 
    }

    if(tokens.size() == 0) {
        printf("NO\n");
        return;
    }

    for(int i = 0; i < pp; i++) {
        int bonus = b[i];
        if(!visit[bonus]) {
            vector<int> path;
            dfs(path, bonus);
            int sz = path.size();
            for(int v : path) {
                cnt[v] = sz;
            }
        }
    }

    int add = 0;

    for(int i = 0; i < p; i++) {
        int token = a[i];
        if(dis[token] != INF) { //can reach
            
        } else { // can not reach
            bool yes = false;
            for(int nxt : g[token]) {
                if(cnt[nxt] > 0) {
                    if(cnt[nxt] == 1) yes = true;
                    else {
                        printf("YES\n");
                        return;
                    }
                }
            }
            if(yes) add++;
        }
    }

    if(tokens.size() == 1) {
        int d = tokens[0].first;
        if(d <= add + 1) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
        return;
    }


    sort(tokens.begin(), tokens.end());
    for(int i = 0; i < tokens.size(); i++) {
        int d = tokens[i].first;
        if(d > 1) {
            printf("YES\n");
            return;
        }        
    }

    add += (tokens.size() - 1);
    if(tokens[0].first <= add + 1) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }
} 


int main() {
	// your code goes here
	int t = 1;
	cin >> t;
	while(t--) {
	    solve();
	}
	return 0;
}  
