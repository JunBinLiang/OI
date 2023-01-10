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

const int N = 1e5 + 10;
int n, k;
int a[N];
int cnt[N];
ll res = 0;
void solve() {
    cin >> n >> k;
    memset(cnt, 0, sizeof cnt);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        cnt[a[i]]++;
    }
    
    if(k == 0) {
        for(int i = 0; i < N; i++) {
            if(cnt[i]) {
                res += ((cnt[i] + 0ll) * (cnt[i] - 1) / 2);
            }
        }
        cout << res << endl;
        return;
    }

    for(int i = 0; i <= 10000; i++) {
        if(cnt[i] == 0) continue;
        vector<int> g1[9], g2[9];
        for(int b = 0; b < (1 << 8); b++) {
            int dif1 = 0, dif2 = 0;
            for(int j = 0; j < 8; j++) {
                int b1 = 0, b2 = 0, b3 = 0;
                if(b & (1 << j)) {
                    
                    b1 = 1;
                }

                if(i & (1 << j)) {
                    b2 = 1;
                }

                if(i & (1 << (j + 8))) {
                    b3 = 1;
                }

                if(b1 != b2) {
                    dif1++;
                }
                if(b1 != b3) {
                    dif2++;
                }
                /*if(i == 0 && b == 0) {
                    cout << "gg   " << j << " " << b1 << " " << b2 << " " << b3 << endl;
                    cout << i << "  " << b << endl;
                    cout << (b & (1 << j)) <<"  " << (i & (1 << j)) << endl << endl;
                } */
            }
            g1[dif1].push_back(b);
            g2[dif2].push_back(b << 8);
        }

        for(int x = 0; x <= 8; x++) {
            for(int y = 0; y <= 8; y++) {
                if(x + y == k) {
                    vector<int>& v1 = g1[x];
                    vector<int>& v2 = g2[y];
                    for(int& o: v1) {
                        for(int & p : v2) {
                            res += (cnt[i] + 0ll) * cnt[o + p];
                        }
                    }
                }
            }
        }
    }
    
    cout << res / 2 << endl;
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

