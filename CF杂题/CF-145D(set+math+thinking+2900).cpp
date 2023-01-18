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
using ll = unsigned long long;
#define pb push_back
 
//ifstream fcin("test/input.txt");
//ofstream fcout("test/output.txt");


bool isluck(int n) {
    while(n > 0) {
        int d = n % 10;
        if(d != 4 && d != 7) {
            return false;
        }
        n /= 10;
    }
    return true;
}


ll C(ll n,ll m)
{
	if(m==2)return (ll)n*(n-1)/2;
	if(m==3)return (ll)n*(n-1)*(n-2)/6;
	if(m==4)return (ll)n*(n-1ll)*(n-2ll)/6ll*(n-3ll)/4ll;
	return 0;
}
const int N = 1e5 + 10;
int a[N], nxt[N];
vector<int> b;
int n;
void solve() {
    memset(nxt, 0, sizeof nxt);

    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        if(isluck(a[i])) {
            b.push_back(i);
        }
    }
    
    for(int i = 0; i < b.size(); i++) {
        for(int j = i + 1; j < b.size(); j++) {
            if(a[b[i]] == a[b[j]]) {
                nxt[i] = j;
                break;
            }
        }
    }
    
   
    ll res = C(n,4) + 2ll*C(n,3) + C(n,2);
    
    for(int i = 0; i <(int)(b.size() - 1); i++) {
        int x = b[i + 1] - b[i]; //need to deal with unluck number
        set<int> s;
        s.insert(b[i]);
        s.insert(n + 1);
        ll del = 0;
        for(int j = i; j >= 0; j--) {
            if(nxt[j] > i) { //do the deletion
                for(int t = nxt[j]; t != 0; t = nxt[t]) {
                    set<int>::iterator lb, rb;
                    lb = rb = s.insert(b[t]).first; //left bound, right bound
                    lb--;
                    rb++;
                    int l = *lb; int r = *rb;
                    ll sz1 = b[t] - l;
                    ll sz2 = r - b[t];
                    if(l == b[i]) {
                        del += (sz2 * ((b[t] - b[i + 1] + 0ll) * x + ((x + 0ll) * (1 + x) / 2)));
                    } else {
                        del += (sz1 * sz2 * x);
                    }
                    
                }
            }
            if(j == 0) {
                res -= (del * (b[j]));
            } else {
                res -= (del * (b[j] - b[j - 1]));
            }
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
