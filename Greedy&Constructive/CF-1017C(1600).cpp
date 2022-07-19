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
#define ve vector
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define RFOR(i, a, b) for (int i = a; i >= b; i--)
#define f first
#define se second
#define W while
#define um unordered_map
#define us unordered_set
#define be begin
#define en end


int main() {
    int n;
    cin >> n;
    int sz = ceil(sqrt(n));
    
    ve<int> res;
    int x = sz;
    set<int> s;
    s.insert(0);

    while(res.size() != n) {
        res.pb(x);
        s.insert(x);
        x--;
        if(s.find(x) != s.end()) {
            x = min(n, x + sz * 2);
        }
    }
    
    for(int i : res) cout << i << " ";
    
    return 0;
}
