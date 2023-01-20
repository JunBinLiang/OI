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

const int N = 5e5 + 10, M = 1e6 + 10;
set<int> s;
int n, m;
vector<vector<int>> res;
vector<int> ban[N];
void dfs(vector<int>& a, int root) {
    if(root < 0 || root >= N) cout << root << endl;
    a.push_back(root);
    s.erase(root);
    int last = 0;

    vector<int>& g = ban[root];
    int i = 0;
    while(s.size()) {
        auto it = s.upper_bound(last);
        if(it == s.end()) break;
        int v = *it;
        while(i < g.size() && g[i] < v) i++;

        if(i >= g.size()) {
            dfs(a, v);
            last = v;
        } else {
            if(g[i] != v) {
                dfs(a, v);
            } 
            last = v;
        }
    }
}

void solve() {
    scanf("%d%d", &n, &m);
    for(int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v); //no road between
        ban[u].push_back(v);
        ban[v].push_back(u);
    }

    for(int i = 1; i <= n; i++) {
        if(ban[i].size()) {
            sort(ban[i].begin(), ban[i].end());
        }
        s.insert(i);
    }

    for(int i = 1; i <= n; i++) {
        if(s.find(i) != s.end()) {
            vector<int> a;
            dfs(a, i);
            res.push_back(a);
        }
    }


    printf("%d\n", (int)(res.size()));
    for(vector<int>& a : res) {
        printf("%d ", (int)(a.size()));
        for(int x : a) {
            printf("%d ", x);
        }
        printf("\n");
    }
    
}

int main() {
	// your code goes here
	int t = 1;
	//cin >> t;
	while(t--) {
	    solve();
	}
	return 0;
}
