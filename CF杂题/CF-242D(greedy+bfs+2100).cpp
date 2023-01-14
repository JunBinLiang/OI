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


const int N = 1e5 + 10;
int n, m;
int a[N];
int b[N];
int cnt[N];
vector<int> g[N];
vector<int> res;
void solve() {
    memset(b, 0, sizeof b);
    memset(cnt, 0, sizeof cnt);
    cin >> n >> m;

    for(int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        g[u].pb(v); g[v].pb(u);
    }
    
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }

    for(int i = 0; i < n; i++) {
        if(b[i] == a[i]) {
            queue<int> q;
            q.push(i);
            res.push_back(i);
            cnt[i]++;
            //cout << "i   " << i + 1 << endl;
            while(q.size()) {
                int t = q.front(); q.pop();
                b[t]++;
                for(int nxt : g[t]) {
                    b[nxt]++;
                    //cout << t + 1 << "  " << nxt + 1 << endl;
                    if(b[nxt] == a[nxt]) {
                        res.push_back(nxt);
                        q.push(nxt);
                        cnt[nxt]++;
                        b[nxt]++;
                        //cout <<"add  " <<  nxt + 1 << "  " << b[nxt] << endl;
                    }
                }
            }
            
            //for(int i = 0; i < n; i++) cout << b[i] << " ";
            //cout << endl << endl;

        }
    }
    
    //for(int i = 0; i < n; i++) cout << cnt[i] << " ";
    //cout << endl << endl;

    sort(res.begin(), res.end());
    cout << res.size() << endl;
    for(int x : res) cout << x + 1 << " ";
    cout << endl;

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
