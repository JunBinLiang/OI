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


using namespace std;  
using ll = long long;
#define pb push_back


void solve() {
    int n;
    string s;
    cin >> n >>  s;
    int a = 0;
    int res = 0;
    for(int i = 0; i < s.size(); i++) {
        if(s[i] == '(') a++;
        else {
            if(a == 0) {
                res++;
                s += ')';
            } else {
                a--;
            }
        }
    }
    
    cout << res << endl;
}  

int main() {
    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
