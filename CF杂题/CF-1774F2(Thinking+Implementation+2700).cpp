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


const int N = 8e5 + 10, mod = 998244353;
const ll INF = 2e9;
pair<int, int> a[N];
ll l[N];
int n;
void solve() {
    scanf("%d", &n);
    vector<ll> b;

    for(int i = 0; i < n; i++) {
        int ty,x;
        scanf("%d", &ty);
        if(ty == 1) { //create
            scanf("%d", &x);
            a[i] = {ty, x};
        } else if(ty == 2) { //delete
            scanf("%d", &x);
            a[i] = {ty, x};
        } else { //reapeat
            a[i] = {ty, ty};
        }
    }

    ll sum = 0;
    for(int i = 0; i < n; i++) {
        if(a[i].first == 2) {
            sum += a[i].second;
            sum = min(sum, INF);
        } else if(a[i].first == 3) {
            l[i] = sum;
            sum *= 2;
            sum = min(sum, INF);
        }
    }
    
    
    /*for(int i = 0; i < n; i++) {
        cout << l[i] << "  ";
    } cout << endl << endl;*/
    

    ll res = 0;
    ll tot = 0, coe = 1;
    for(int i = n -  1; i >= 0; i--) {
        int ty = a[i].first;
        if(ty == 1) {
            ll v = a[i].second;
            v -= tot;
            if(v <= 0) continue;
            ll take = 0;
            
            /*cout << "gg  " << "  " << v << endl;
            for(ll x : b) {
                cout << x << " ";
            } cout << endl;*/
            
            for(int j = 0; j < b.size(); j++) {
                if(v > b[j]) {
                    v -= b[j];
                    take += (1ll << (b.size() - (j + 1)));
                }
            }
        
            take++;
            take %= mod;
            res += (take * (coe));
            res %= mod;
        } else if(ty == 2) {
            tot += a[i].second;
        } else if(ty == 3){
            if(l[i] == 0) {
                coe *= 2;
                coe %= mod;
                continue;
            }
            if(l[i] >= INF) continue;
            b.push_back(l[i]);
        }
    }
    printf("%lld\n", res);
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
