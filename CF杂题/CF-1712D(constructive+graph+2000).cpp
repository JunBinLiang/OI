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
const int INF = 1e9;
int n, k;
int a[N], b[N];
int res = -1;
int l = INF, r = INF;

bool check(int mid) {
    //construct a path >= mid
    int cnt = 0;
    int mn = INF;
    for(int i = 0; i < n; i++) {
        if(a[i] * 2 < mid) {
            b[i] = INF;
            cnt++;
        } else {
            b[i] = a[i];
        }
        mn = min(mn, b[i]);
    }
    
    if(cnt > k) return false;
    if(mn >= mid) return true;
    
    for(int i = 1; i < n; i++) {
        if(min(b[i], b[i - 1]) >= mid) {
            return true;
        }
    }
    
    //for(int i = 0; i < n; i++) cout << b[i] << " ";
    //cout << endl;
    if(k - cnt >= 2) {
        return true;
    }
    
    if(k - cnt == 1) {
        for(int i = 1; i < n; i++) {
            if(max(b[i], b[i - 1]) >= mid) {
                return true;
            }
        }
    } 

    return false;
    
}

//use 2:13
void solve() {
    cin >> n >> k;
    r = INF;
    l = INF;
    res = -1;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        l = min(l, a[i]);
    }
    
    if(n == 2) {
        if(k == 0) {
            cout << min(a[0], a[1]) << endl;
        } else if(k == 1) {
            cout << max(a[0], a[1]) << endl;
        } else {
            cout << INF << endl;
        }
        return;
    }
    
    while(l <= r) {
        int mid = l + (r - l) / 2;
        if(check(mid)) {
            res = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }

    cout << res << endl;

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

