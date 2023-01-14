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
template <typename T>
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} 
  out << "]";
  return out;
}



const int N = 2005;
int a[N][N];
int v[N][N];
int sums[26];
int mins[26], cnts[26];
char s[N];
int n, m;
ll res = 0;
void solve() {
    scanf("%d%d", &n, &m);
    for(int i = 0; i < n; i++) {
        scanf("%s", &s);
        for(int j = 0; j < m; j++) {
            a[i][j] = s[j] - 'a';
        }
    }
    
    for(int j = 0; j < m; j++) {
        memset(sums, 0, sizeof sums);
        for(int i = 0; i < n; i++) {
            int c = a[i][j];
            if(i == 0) {
                sums[c] = 1;
            } else {
                if(i) {
                    if(a[i][j] == a[i - 1][j]) sums[c]++;
                    else sums[c] = 1;
                } else {
                    sums[c] = 1;
                }
            }
            v[i][j] = sums[c];
        }
    }
    
    /*for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) cout << v[i][j] << " ";
        cout << endl;
    }
    cout << endl << endl;*/

    
    for(int j = 0; j < m; j++) {
        memset(sums, 0, sizeof sums);
        for(int i = n - 1; i >= 0; i--) {
            int c = a[i][j];
            if(i == n - 1) {
                sums[c] = 1;
            } else {
                if(i + 1 < n) {
                    if(a[i][j] == a[i + 1][j]) sums[c]++;
                    else sums[c] = 1;
                } else {
                    sums[c] = 1;
                }
            }
            v[i][j] = min(v[i][j], sums[c]);
        }
    }
    
    /*for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) cout << v[i][j] << " ";
        cout << endl;
    }*/
    
    for(int i = 0; i < n; i++) {
        vector<int> dp(m, m + 10);
        memset(mins, -1, sizeof mins);
        memset(cnts, 0, sizeof cnts);
        for(int j = 0; j < m; j++) {
            int c = a[i][j];
            if(j > 0) {
                if(a[i][j] == a[i][j - 1]) {
                    cnts[c]++;
                    mins[c] = min(mins[c] + 1, v[i][j]);
                } else {
                    cnts[c] = 1;
                    mins[c] = v[i][j];
                }
            } else {
                mins[c] = v[i][j];
                cnts[c] = 1;
            }
            dp[j] = min(mins[c], cnts[c]);
        }

        memset(mins, -1, sizeof mins);
        memset(cnts, 0, sizeof cnts);

        for(int j = m; j >= 0; j--) {
            int c = a[i][j];
            if(j + 1 < m) { 
                if(a[i][j] == a[i][j + 1]) {
                    cnts[c]++;
                    mins[c] = min(mins[c] + 1, v[i][j]);
                } else {
                    cnts[c] = 1;
                    mins[c] = v[i][j];
                }
            } else {
                mins[c] = v[i][j];
                cnts[c] = 1;
            }
            dp[j] = min(dp[j], min(mins[c], cnts[c]));
        }
        
        //cout << dp << endl;
        for(int& x : dp) {
            res += x;
        }
    }

    
    printf("%lld", res);

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
