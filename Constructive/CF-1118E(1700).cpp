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

//5: 47
void solve() {
    int n, k;
    cin >> n >> k;
    
    if((k + 0ll) * (k - 1) < n) {
        cout << "NO" << endl;
        return;
    }

    vector<pair<int, int>> res;
    for(int i = 1; i <= k && res.size() <= n; i++) {
        for(int j = i + 1; j <= k && res.size() <= n ; j++) {
            res.push_back({i, j});
            res.push_back({j, i});
        }
    }

    cout << "YES" << endl;
    for(int i = 0; i < n; i++) {
        cout << res[i].first << " " << res[i].second << endl;
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
