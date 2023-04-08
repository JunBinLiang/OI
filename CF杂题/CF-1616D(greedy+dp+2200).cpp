
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



const int N = 1e5 + 10, INF = 1e9;
int a[N];
int dp[N][3];
int n, x;
void solve() {
    cin >> n;
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    cin >> x;
    for(int i = 0; i < n; i++) {
        a[i] -= x;
        //cout << a[i] << " ";
    }
    //cout << endl;
    

    for(int i = 0; i <= n; i++) {
        dp[i][0] = dp[i][1] = dp[i][2] = INF;
    }
    
    dp[0][0] = 1;
    dp[0][1] = 0;

    for(int i = 1; i < n; i++) {
        int v = a[i] + a[i - 1];
        
        dp[i][0] = min(dp[i - 1][0], min(dp[i - 1][1], dp[i - 1][2])) + 1;

        dp[i][1] = min(dp[i][1], dp[i - 1][0]);

        if(v >= 0) {
            dp[i][2] = dp[i - 1][1];
            
            if(i > 1 && v + a[i - 2] >= 0) {
                //dp[i][2] = min(dp[i][2], dp[i - 2][1]);
                dp[i][2] = min(dp[i][2], dp[i - 1][2]);
            }
        }
        
        
    }
    
    //cout <<

    int minDel = min(dp[n - 1][0], min(dp[n - 1][1], dp[n - 1][2]));
    cout << n - minDel << endl;
}   


int main()
{   

    int t = 1;
    cin >> t;
    while(t --) {
        solve();
    }
    return 0;
}
