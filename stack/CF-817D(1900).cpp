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



const int N = 1e6 + 10;
int a[N];
ll res = 0;
ll mx[N], mn[N];
void solve() {
    int n;
    scanf("%d", &n);
    memset(mx, 0, sizeof mx);
    memset(mn, 0, sizeof mn);

    a[0] = 2e9;
    for(int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }

    
    vector<int> stk;
    stk.push_back(0);
    for(int i = 1; i <= n; i++) {
        while(stk.size() && a[i] >= a[stk.back()]) {
            int idx = stk.back();
            stk.pop_back();
        }

        int last = stk.back();
        mx[i] += ((a[i] + 0ll) * (i - last));
        mx[i] += mx[last];
        res += mx[i];
        stk.push_back(i);
    } 
    

    stk.clear();
    a[0] = 0;
    stk.push_back(0);

    for(int i = 1; i <= n; i++) {
        while(stk.size() && a[i] <= a[stk.back()]) {
            int idx = stk.back();
            stk.pop_back();
        }

        int last = stk.back();
        mn[i] += ((a[i] + 0ll) * (i - last));
        mn[i] += mn[last];
        res -= mn[i];
        stk.push_back(i);
    }

    cout << res << endl;
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
