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
#include <sstream>

using namespace std;

const int N = 1010;
int a[N];
int main() {
    int n = 0;  
    string line;
    getline(cin, line);
    stringstream ssin(line);
    while (ssin >> a[n]) n ++ ;
    
    int res1 = 0, res2 = 0;
    int dp[N];
    int top[N];
    memset(top, -1, sizeof(top));
    for(int i = 0; i < n; i++) {
        dp[i] = 1;
        for(int j = i - 1; j >= 0; j--) {
            if(a[j] >= a[i]) {
                dp[i] = max(dp[i], 1 + dp[j]);
            }
        }
        res1 = max(res1, dp[i]);
        int k = 0;
        while(k < res2 && top[k] < a[i]) k++;
        if(k >= res2) {
            top[res2++] = a[i];
        } else {
            top[k] = a[i];
        } 
        
    }
    
    cout << res1 << endl << res2 << endl;
    
    return 0;
}
