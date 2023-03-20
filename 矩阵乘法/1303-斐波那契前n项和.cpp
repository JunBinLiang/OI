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



int n, m;
ll a[3][3]; ll f1[3];

void mul1() {
    ll temp[3];
    for(int i = 0; i < 3; i++) temp[i] = f1[i];
    for(int c = 0; c < 3; c++) {
        ll sum = 0;
        for(int r = 0; r < 3; r++) {
            sum += (temp[r] * a[r][c]);
            sum %= m;
        }
        f1[c] = sum;
    }
}

void mul2() {
    
    ll temp[3][3];
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            temp[i][j] = a[i][j];
            
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            ll sum = 0;
            for(int k = 0; k < 3; k++) {
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
    a[0][1] = a[1][0] = a[1][1] = a[1][2] = a[2][2] = 1;
    f1[0] = f1[1] = 1; f1[2] = 1;
    n--;
    
    while(n) {
        if (n & 1) mul1();// res = res * a
        mul2();  // a = a * a
        n >>= 1;
    }
    
    cout << f1[2] << endl;
}

int main() {
    solve();
    return 0;
}
