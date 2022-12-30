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


const int N = 15;
string a[N];
int n;
int pos[N][52][2];
int dp[53 * 2][(1 << 10) + 5];
int nxt[53 * 2][(1 << 10) + 5][2];

int toc(char& c) {
    if(c - 'a' >= 0 && c - 'a' < 26) {
        return c - 'a';
    } else {
        return c - 'A' + 26;
    }
}

int dfs(int i, int state) {
    if(i >= a[0].size()) {
        return 0;
    }

    if(dp[i][state] != -1) {
        return dp[i][state];
    }

    string& s = a[0];
    int res = 1;
    int mx = 0;
    int c = toc(s[i]);
    for(int j = i + 1; j < s.size(); j++) {
        int d = toc(s[j]);
        bool valid = true;
        int newstate = 0;
        for(int k = 1; k < n; k++) {
            string& t = a[k];
            int pre = -1;
            if(state & (1 << k)) { // 0
                pre = pos[k][c][1]; 
            } else {
                pre = pos[k][c][0]; 
            }

            if(pos[k][d][0] > pre) {

            } else if(pos[k][d][1] > pre) {
                newstate |= (1 << k);
            } else {
                valid = false;
                break;
            }
            
            //if(i == 0) {
                //cout << "gg1      " << pre << " " << c << endl;
            //}
            
            
        }
        
        //if(i == 0) {
            //cout << "gg      " << valid << " " << newstate << endl;
        //}
        
        if(!valid) continue;
        int v = dfs(j, newstate);
        if(v > mx) {
            mx = v;
            nxt[i][state][0] = j;
            nxt[i][state][1] = newstate;
        }
    }
    return dp[i][state] = res + mx;    
}

void solve() {
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }

    memset(pos, -1, sizeof pos);
    memset(dp, -1, sizeof dp);
    memset(nxt, -1, sizeof nxt);

    for(int i = 0; i < n; i++) {
        string& s = a[i];
        for(int j = 0; j < s.size(); j++) {
            int d = toc(s[j]);
            if(pos[i][d][0] == -1) {
                pos[i][d][0] = j;    
            } else {
                pos[i][d][1] = j;    
            }
        }
    }
    
    //cout << "pos      " << pos[0][26][0] << endl;
    //cout << "pos      " << pos[0][26][1] << endl;
    //cout << "pos      " << pos[0][27][0] << endl;
    //cout << "pos      " << pos[0][27][1] << endl;

    string& s = a[0];
    int mx = -1, idx = -1, state = -1;
    for(int i = 0; i < s.size(); i++) {
        int d = toc(s[i]);
        bool valid = true;
        for(int j = 0; j < n; j++) {
            if(pos[j][d][0] == -1) {
                valid = false;
            }
        }
        if(!valid) continue;
        int v = dfs(i, 0);
        if(v > mx) {
            mx = v;
            idx = i;
            state = 0;
        }
    }

    string res = "";
    while(idx != -1 && state != -1) {
        res += s[idx];
        int t1 = idx, t2 = state;
        idx = nxt[t1][t2][0];
        state = nxt[t1][t2][1];
    }
    cout << res.size() << endl;
    cout << res << endl;
}



int main() {
	// your code goes here
	int t = 1;
	cin >> t;
	while(t--) {
	    solve();
	}
	return 0;
}

