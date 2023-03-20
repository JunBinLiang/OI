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
#include <iostream>
   
using ll = long long;
using namespace std;  



ll n, m;
ll a[5][5]; ll f1[5];

void mul1() {
    ll temp[5];
    for(int i = 0; i < 5; i++) temp[i] = f1[i];
    for(int c = 0; c < 5; c++) {
        ll sum = 0;
        for(int r = 0; r < 5; r++) {
            sum += (temp[r] * a[r][c]);
            sum %= m;
        }
        f1[c] = sum;
    }
}

void mul2() {
    
    ll temp[5][5];
    for(int i = 0; i < 5; i++)
        for(int j = 0; j < 5; j++)
            temp[i][j] = a[i][j];
            
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++) {
            ll sum = 0;
            for(int k = 0; k < 5; k++) {
                sum += temp[i][k] * temp[k][j];
                sum %= m;
            }
            a[i][j] = sum;
        }
    }
    
}


void solve() {
    cin >> n >> m;
    if(n == 1) {
        cout << 1 << endl;
        return;
    }
    if(n == 2) {
        cout << 2 % m << endl;
        return;
    }
    
    memset(a, 0, sizeof a);
    
    a[1][0] = 1;
    a[0][1] = a[1][1] = 1;
    a[1][2] = a[3][2] = 1;
    a[0][3] = a[1][3] = a[2][3] = a[3][3] = 1;
    a[3][4] = a[4][4] = 1;
    
    
    f1[0] = 1; f1[1] = 1; f1[2] = 2; f1[3] = 2; f1[4] = 1;
    
    
    
    n -= 1;
    while(n) {
        if (n & 1) mul1();  // res = res * a
        mul2();  // a = a * a
        n >>= 1;
    }
    
    cout << f1[4] << endl;
}

int main() {
    solve();
    return 0;
}
