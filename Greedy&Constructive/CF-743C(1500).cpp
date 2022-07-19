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
    ve<int> res(3);
    res[0] = n;
    res[1] = n + 1;
    res[2] = n * (n + 1);
    
    if(res[1] == res[2] || res[1] == res[0] || res[0] == res[2]) {
        cout << -1 << endl;
        return 0;
    }
    
    for(int i : res) cout << i << " ";
    
    return 0;
}
