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
ll n, m;
string s;
void solve() {
    cin >> n >> m >> s;
    ll res = (m - 1) * n;
    for(int i = 1; i < n; i++) {
        if(s[i] != s[i - 1]) {
            res += (m - 1) * n;
        }
    }
    

    ll len = 1;
    for(int i = 1; i < n; i++) {
        if(s[i] != s[i - 1]) {
            if(len == 1) {
                len++;
            } else {
                if(s[i] == s[i - 2]) {
                    len++;
                } else {
                    res = res - (len * (len - 1) / 2);
                    if(len >= 2) len = 2;
                    else len = 1;
                }
            }
        } else {
            res = res - (len * (len - 1) / 2); 
            len = 1;
        }
    }
    res = res - (len * (len - 1) / 2);

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

