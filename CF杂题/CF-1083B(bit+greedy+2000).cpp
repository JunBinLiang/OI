
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
#include <map>

using namespace std;

using ll = long long;
#define pb push_back
#define ve vector

const int N = 5e5 + 50;
char s[N], t[N];
int a[N], b[N];
int n; ll k;
ll res = 0;
ll p[62];

//5:10
void solve() {
    cin >> n >> k;
    scanf("%s", s);
    scanf("%s", t);

    for(int i = 0; i < n; i++) {
        if(s[i] == 'a') a[i] = 0;
        else a[i] = 1;
        if(t[i] == 'a') b[i] = 0;
        else b[i] = 1;
    }
    

    int idx = -1;
    for(int i = 0; i < n; i++) {
        if(a[i] == b[i]) {
            idx = i;
        } else {
            break;
        }
    }

    idx++;
    res += (idx);
    
    if(idx == n) {
        cout << res << endl;
        return;
    }
    
    res += min(k, 2ll);
    
    //cout << res << endl;
    
    //different from index + 1
    ll split1 = 0, nonsplit1 = 1;
    ll split2 = 0, nonsplit2 = 1;
    
    for(int i = idx + 1; i < n; i++) {
        if(a[i] == 0) {
            split1 = split1 * 2 + 1;
        } else {
            split1 = split1 * 2;
        }
        
        if(b[i] == 0) {
            split2 *= 2;
        } else {
            split2 = split2 * 2 + 1;
        }
        
        
        res += min(k, split1 + split2 + nonsplit1 + nonsplit2);
        split1 = min(split1, k);
        split2 = min(split2, k);
        nonsplit1 = min(nonsplit1, k);
        nonsplit2 = min(nonsplit2, k);
        
       // cout <<i << "  |" << split1 << "  " << split2  <<"  " << nonsplit1 << "  " << nonsplit2 << endl; 
    }
    

    cout << res << endl;

}   


int main()
{   

    int t = 1;
    //cin >> t;
    while(t --) {
        solve();
    }
    return 0;
}
