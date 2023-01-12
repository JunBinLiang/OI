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
 

//1: 56
int n, m;
const int N = 110;
int col[N];
vector<int> g[N];
int cnt[2];
int add = 0;
bool is = false;
void dfs(int p, int r, int c) {
    col[r] = c;
    cnt[c]++;
    for(int nxt : g[r]) {
        if(col[nxt] == -1) {
            dfs(r, nxt, c ^ 1);
        } else {
            if(col[nxt] == col[r] && p != nxt) {
                is = true;
            } 
        }
    }
}

void solve() {
    cin >> n >> m;
    memset(col, -1, sizeof col);
    for(int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    int dif = 0;
    for(int i = 0; i < n; i++) {
        if(col[i] != -1) continue;
        cnt[0] = cnt[1] = 0; 
        is = false;
        dfs(-1, i, 0);
        if(cnt[0] != cnt[1] && is == false) {
            dif++;
        }
        if(is) add++;
    }

    cout << add + dif % 2 << endl;
 
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
