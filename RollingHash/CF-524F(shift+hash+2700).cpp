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

string s;
const int N = 1e6 + 10;
ll hash1[N], p[2 * N];
ll hash2[2 * N];
int pe[N], mn[N];
bool is[N];
bool is1[N];
int base = 101, mod = 1e9 + 7;

ll get1(int l, int r) {
    if(l == 0) return hash1[r];
    return (hash1[r] - (hash1[l - 1] * p[r - l + 1] % mod) + mod) % mod;
}

ll get2(int l, int r) {
    if(l == 0) return hash2[r];
    return (hash2[r] - (hash2[l - 1] * p[r - l + 1] % mod) + mod) % mod;
}

int isp(int l1, int l2) {
    if(l1 > l2) swap(l1, l2);
    int n = s.size();
    int l = l2, r = n - 1;
    int po = -1;
    while(l <= r) {
        int mid = l + (r - l) / 2;
        if(get1(l2, mid) == get1(l1, l1 + (mid - l2))) {
            po = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    
    //cout << "isp :" << l1 << " " << l2 << endl;
    //cout << po << endl;
   // cout << endl;

    if(po == -1) { //differ at first place
        if(s[l1] == '(') return l1;
        else return l2;
    } else {
        if(po == n - 1) {
            int ll1 = l1 +  (n - l2);
            l = 0;
            r = l2 - 1;
            int po2 = -1;
            while(l <= r) {
                int mid = l + (r - l) / 2;
                if(get2(0, mid) == get2(ll1, ll1 + (mid))) {
                    po2 = mid;
                    l = mid + 1;
                } else {
                    r = mid - 1;
                }
            } 

            if(po2 == -1) {
                if(s[0] == '(') return l2;
                else return l1;
            } else {
                if(po2 == l2 - 1) { //all same
                    return l1;
                } else {
                    if(s[po2 + 1] == '(') return l2;
                    else return l1;
                }
            }
        } else {
            if(s[po + 1] == '(') return l2;
            else return l1; 
        }
    }
}

void add(string& t, int o) {
    if(o < 0) {
        o = -o;
        string p = "";
        while(o--) p += "(";
        t = p + t;
    } else {
        while(o--) t += ")";
    }
}

void solve() {
    cin >> s;
    int n = s.size();
    int o = 0;
    int c = 0, po = -1;
    
    memset(is, false, sizeof is);
    memset(is1, false, sizeof is1);
    
    ll h = 0;
    for(int i = 0; i < s.size(); i++) {
        int d = (s[i] == '(' ? 0 : 1);
        h = h * base + d;
        h %= mod;
        hash1[i] = h;
    }
    h = 0;
    for(int i = 0; i < 2 * s.size(); i++) {
        int d = (s[(i % s.size())] == '(' ? 0 : 1);
        h = h * base + d;
        h %= mod;
        hash2[i] = h;
    }
    p[0] = 1;
    for(int i = 1; i < N * 2; i++) p[i] = (p[i - 1] * base) % mod;
    
    for(int i = 0; i < s.size(); i++) {
        if(s[i] == '(') {
            o++;
        } else {
            if(o == 0) {
                c++;
                po = i;
                is[i] = is1[i] = true;
            } else {
                o--;
                if(o == 0) is[i] = true;
            }
        }
    }


    int shift = po + 1;
    int cnt = 0;
    for(int i = po + 1; i < n; i++) {
        if(s[i] == '(') {
            cnt++;
        } else {
            cnt--;
        }
        if(cnt == 0) { //can shift
            shift = isp(shift, i + 1);
        }
        pe[i] = cnt;
    }
    
    for(int i = n - 1; i >= 0; i--) {
        mn[i] = pe[i];
        if(i + 1 < n) mn[i] = min(mn[i], mn[i + 1]);
    }
    
    cnt = 0;
    for(int i = po + 1; i < n; i++) {
        if(s[i] == '(') {
            cnt++;
        } else {
            cnt--;
        }
        if(i + 1 < n && mn[i + 1] >= pe[i] && cnt <= o - c) {
            shift = isp(shift, i + 1);
        }
    }
    
    
    if(cnt == 0) {
        shift = isp(shift, 0);
    }
    
    
    int x = 0;
    for(int i = 0; i < po; i++) {
        if(is1[i]) {
            x++;
        }
        if(is[i] && i + 1 < n && x >= o) {
            shift = isp(shift, i + 1);
        }
    }
    
   
    string res = "";
    for(int i = shift; i < n; i++) res += s[i];
    for(int i = 0; i < shift; i++) res += s[i];
 
    add(res, o - c);
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
