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


const int N = 5050;
bool dp[N][N];
int sum = 0, k = 0;

void solve() {
    string s;
    cin >> s;
    int n = s.size();
    memset(dp, false, sizeof dp);

    for(int i = 0; i < 20; i++) {
        if(sum + (1 << i) < n) {
            sum += (1 << i);
            k = i;
        }
    }

    string res = "";
    int len = n - sum;

    for(int i = 0; i <= sum; i++) {
        dp[0][i] = true;
    }

    for(int i = 1; i <= len; i++) {
        for(int state = 0; state <= sum; state++) {
            dp[i][state] = dp[i - 1][state];
        }

        char mn = 'z';
        for(int state = 0; state <= sum; state++)  {
            if(dp[i - 1][state]) {
                mn = min(mn, s[i + state - 1]);
            }
        }

        for(int state = 0; state <= sum; state++)  {
            if(dp[i][state] && s[i + state - 1] != mn) {
                dp[i][state] = false;
            }
        }

        //do ssp
        for(int state = 0; state <= sum; state++) {
            for(int j = 0; j <= k; j++) {
                if(state & (1 << j)) {
                    dp[i][state] |= dp[i][state ^ (1 << j)];
                }
            }
        }
        res += mn;
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

