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



const ll INF = 10000000000000000ll;
const int N = 2e5 + 10;
string s;
ll t1[2], t2[2];
int l[N][2], r[N][2];
int cur[N];
ll res = INF;
void cal(ll h) {
    memset(l, 0, sizeof l);
    //memset(r, 0, sizeof r);
    for(int i = 0; i < s.size(); i++) {
        l[i][0] = min(l[i][0], cur[i]);
        //l[i][0] = cur[i];
        if(i) l[i][0] = min(l[i][0], l[i - 1][0]);
        l[i][1] = max(l[i][1], cur[i]);
        //l[i][1] = cur[i];
        if(i) l[i][1] = max(l[i][1], l[i - 1][1]);
    }

    for(int i = s.size() - 1; i >= 0; i--) {
        r[i][0] = cur[i];
        if(i + 1 < s.size()) r[i][0] = min(r[i][0], r[i + 1][0]);
        r[i][1] = cur[i];
        if(i + 1 < s.size()) r[i][1] = max(r[i][1], r[i + 1][1]);
    }

    for(int i = 0; i < s.size() - 1; i++) { // positive dir
        int lmn = l[i][0], lmx = l[i][1];
        lmn = min(lmn, cur[i] + 1);
        lmx = max(lmx, cur[i] + 1);
        int rmn = r[i + 1][0] + 1, rmx = r[i + 1][1] + 1;
        res = min(res, (max(lmx, rmx) - min(lmn, rmn) + 1ll) * h);
    }
    
    for(int i = 0; i < s.size() - 1; i++) { // neg dir
        int lmn = l[i][0], lmx = l[i][1];
        int rmn = r[i + 1][0] - 1, rmx = r[i + 1][1] - 1;
        lmn = min(lmn, cur[i] - 1);
        lmx = max(lmx, cur[i] - 1);
        res = min(res, (max(lmx, rmx) - min(lmn, rmn) + 1ll) * h);
    }
}

void solve() {
    cin >> s;
    res = INF;
    t1[0] = t1[1] = 0; //vertical
    t2[0] = t2[1] = 0; //horizontal
    
    ll x = 0, y = 0;
    for(int i = 0; i < s.size(); i++) {
        //W : up
        //S: down
        //A: left
        //D: right
        char c = s[i];
        if(c == 'W') {
            y++;
        } else if(c == 'S') {
            y--;
        } else if(c == 'D') {
            x++;
        } else {
            x--;
        }

        t1[0] = min(t1[0], y);
        t1[1] = max(t1[1], y);
        t2[0] = min(t2[0], x);
        t2[1] = max(t2[1], x);
    }

    res = min(res, (t1[1] - t1[0] + 1) * (t2[1] - t2[0] + 1));

    int o = 0;
    for(int i = 0; i < s.size(); i++) {
        if(s[i] == 'D') { //right
            o++;
        } else if(s[i] == 'A') { //left
            o--;
        }
        cur[i] = o;
    } 

    cal(t1[1] - t1[0] + 1); //horizontal
    
    o = 0;
    for(int i = 0; i < s.size(); i++) {
        if(s[i] == 'W') { //up
            o++;
        } else if(s[i] == 'S') { //down
            o--;
        }
        cur[i] = o;
    }

    cal(t2[1] - t2[0] + 1); //vertical

    cout << res << endl;
}

//DAA
//1 0 -1
 
int main() {
	//your code goes here
	int t = 1;
	cin >> t;
	while(t--) {
	    solve();
	}
	return 0;
}
