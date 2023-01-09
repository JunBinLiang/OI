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
ll b[N];
bool check(vector<ll>& a, ll x) {
    ll rate = x;
    for(ll i : a) {
        if(rate >= i) rate++;
        else rate--;
    }
    return rate > x;
}


void solve() {
    int n;
    ll x, y;
    cin >> n >> x >> y;
    vector<ll> a(n);
    for(int i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
    } 
   
    
    sort(a.begin(), a.end());
    
    ll o = x;
    int p = -1;
    for(int i = 0; i < n; i++) {
        if(o >= a[i]) {
            o++;
            if(o == y) {
                cout << i + 1 << endl;
                return;
            }
            p = i;
        } else {
            o--;
        }
    }
    
    if(!check(a, x)) {
        printf("-1\n");
        return;
    }

    for(int i = 0; i < n; i++) {
        b[i] = a[i] - (i);
        if(i) b[i] = max(b[i], b[i - 1]);
    }

    
    ll res = n;
    for(int i = p + 1; i < n; i++) {
        //how many round need to beat p
        if(a[i] <= o) continue;
        ll l = 0, r = a[i];
        ll rou = -1;
        while(l <= r) {
            ll mid = l + (r - l) / 2;
            ll s = (mid) * (i - (n - i)) + i;
            if(o + s >= a[i] || o + s >= y) {
                rou = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }

        res += (rou * (n));
        o += (rou * (i - (n - i)));
        int le = 0, ri = n - 1;
        int to = -1;
        while(le <= ri) {
            int mid = le + (ri - le) / 2;
            if(o >= b[mid]) {
                to = mid;
                le = mid + 1;
            } else {
                ri = mid -  1;
            }
        }
        
        
        
        if(o + to + 1 >= y) {
            for(int x = 0; x < n; x++) {
                res++;
                if(o >= a[x]) {
                    o++;
                } else {
                    o--;
                }
                if(o == y) {
                    cout << res << endl;
                    return;
                }
            }
        }
        to++;
        o += (to - (n - to));
        res += n;
    }
    
    if(o < y) {
        res += (y - o);
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
