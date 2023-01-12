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

const int N = 2e5 + 10;
int p[N], nxt[N];
ll res = 0;

int get(int x, int y) {
    return x / y;
}

void solve() {
    string s;
    cin >> s;
    int n = s.size();
    memset(nxt, -1, sizeof nxt);
    p[0] = 0;
    for(int i = 1; i <= s.size(); i++) {
        if(s[i - 1] == '1') {
            p[i] = 1;
        } else {
            p[i] = 0;
        }
        p[i] += p[i - 1];
    }

    int post = -1;
    for(int i = n; i >= 0; i--) {
        nxt[i] = post;
        if(s[i - 1] == '1') post = i;
    }

    //for(int i = 0; i <= n; i++) cout << p[i] << " ";
    //cout << endl << endl;
    //for(int i = 0; i <= n; i++) cout << nxt[i] << " ";
    //cout << endl << endl;

    int block = sqrt(n);
    for(int k = 1; k <= block; k++) {
        vector<int> b(n + 1);
        for(int i = 0; i <= n; i++) {
            b[i] = i - k * p[i];
        }
        
        sort(b.begin(), b.end());
        for(int j = 0; j < b.size(); j++) {
            int x = j; ll cnt = 0;
            while(x < b.size() && b[j] == b[x]) {
                x++;
                cnt++;
            }
            res += (cnt) * (cnt - 1) / 2;
            j = x - 1;
        }
    }
    

    for(int i = 1; i <= n; i++) {
        int cur = i;
        if(s[i - 1] == '0') cur = nxt[cur];
        int j = 1;
        
        
        while(j <= n && cur != -1 && j <= block + 2) {
            int nxtP = nxt[cur];
            if(nxtP == -1) nxtP = n;
            else nxtP--;
            
            int x = nxtP - i + 1;
            int to = max(cur - i, j * block);
            int add = max(0, get(x, j) - get(to, j)); 
        
            res += add;
            cur = nxt[cur];
            j++;
        }
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

