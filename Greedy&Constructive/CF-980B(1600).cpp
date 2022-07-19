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

const int N = 105;
char a[N][N];
int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < n; j++) {
            a[i][j] = '.';
        }
    }
    
    if(k % 2 == 0) {
        k /= 2;
        for(int i = 1; i <= 2; i++) {
            for(int j = 1; j <= k; j++) {
                a[i][j] = '#';
            }
        }
    } else {
        int l = 1, r = n - 2;
        while(k > 0 && l <= r) {
            if(l == r) {
                a[1][l] = a[1][r] = '#';
                k--;
                break;
            }
            
            if(k == 1) {
               a[1][n / 2] = '#';
               k = 0;
               break;
            } else {
                a[1][l++] = a[1][r--] = '#';
                k -= 2;
            }
        }
        
        if(k > 0) {
            int l = 1, r = n - 2;
            while(k > 0) {
                a[2][l] = a[2][r] = '#';
                l++;
                r--;
                k -= 2;
            }
        }
        
    }

    
    cout << "YES" << endl;
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < n; j++) {
            cout << a[i][j];
        } cout << endl;
    }
    
    
    return 0;
}
