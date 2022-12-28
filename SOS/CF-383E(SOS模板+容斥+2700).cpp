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

const int N = 1e4 + 10;
string a[N];
int res = 0;
const int M = 24;
int dp[(1 << M) + 5];

void sos() {
    for(int i = 0; i <= M; i++) {
        for(int st = 0; st < (1 << M); st++) {
            if(st & (1 << i)) {
                dp[st] += dp[st ^ (1 << i)];
            }
        }
    }
}

void solve() {
    int n;
    cin >> n;
    memset(dp, 0, sizeof dp);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        int st = 0;
        for(int j = 0; j < 3; j++) {
            int d = a[i][j] - 'a';
            st |= (1 << d);
        }
        

        int cnt = 0;
        for(int j = 0; j <= M; j++) {
            if(st & (1 << j)) {
                cnt++;
                dp[1 << j]++;
            }
        }

        if(cnt > 1) {
            if(cnt == 2) {
                dp[st]--;
            } else {
                dp[(1 << (a[i][0] - 'a')) | (1 << (a[i][1] - 'a'))]--;
                dp[(1 << (a[i][0] - 'a')) | (1 << (a[i][2] - 'a'))]--;
                dp[(1 << (a[i][1] - 'a')) | (1 << (a[i][2] - 'a'))]--;
            }

            if(cnt == 3) {
                dp[st] ++;
            }
        }
    }
    
    sos();
    
    for(int i = 0; i < (1 << M); i++) {
        res = res ^ ((dp[i]) * (dp[i]));
    }
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

