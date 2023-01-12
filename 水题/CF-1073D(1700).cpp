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
 
//5:48
const int N = 2e5 + 10;
int a[N];
ll res = 0;
void solve() {
    int n; ll t;
    cin >> n >> t;
    ll o = 0;
    int all = n;
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        o += a[i];
    }
    
    while(t > 0) {
        if(t >= o) {
            ll c = t / o;
            t -= o * c;
            res += c * all;
        } else {
            o = 0;
            all = 0;
            for(int i = 0; i < n; i++) {
                if(a[i] < 0) continue;
                if(t >= a[i]) {
                    res++;
                    all++;
                    t -= a[i];
                    o += a[i];
                } else {
                    a[i] = -1;
                }
            }
            if(!all) break;
        }
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
