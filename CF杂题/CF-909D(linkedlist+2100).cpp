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
const int N = 1e6 + 10;
struct Node {
    int v, cnt;
} nodes[N];
int nxt[N], pre[N];

//1:40 - 2:15
void solve() {
    string s;
    cin >> s;
    int res = 0;
    int h = 0, t = 1, sz = 0;
    
    for(int i = 0; i < s.size(); i++) {
        int j = i, cnt = 0;
        while(j < s.size() && s[j] == s[i]) {
            cnt++;
            j++;
        }
        nodes[t++] = {s[i] - 'a', cnt};
        sz++;
        i = j - 1;
    }

    pre[0] = -1;
    nxt[t] = -1;
    for(int i = 0; i <= t ; i++) {
        if(i + 1 <= t) nxt[i] = i + 1;
        if(i - 1 >= 0) pre[i] = i - 1;
    }

    while(sz > 1) {
        res++;
        int cur = nxt[h];
        while(cur != t) {
            if(pre[cur] == h || nxt[cur] == t) {
                nodes[cur].cnt--;
            } else {
                nodes[cur].cnt -= 2;
            }
            cur = nxt[cur];
        }
        
        int p = h;
        cur = nxt[h];
        while(cur != t) {
            if(nodes[cur].cnt <= 0) { //delete
                nxt[p] = nxt[cur];
                pre[nxt[cur]] = p;
                sz--;
                //cout << "gg  " << cur <<"  " << nxt[cur] << endl;
                cur = nxt[cur];
            } else {
                p = cur;
                cur = nxt[cur];
            }
        }
        
        //merge
        p = h;
        cur = nxt[h];
        while(cur != t) {
            if(nxt[cur] != t && nodes[nxt[cur]].v == nodes[cur].v) {
                nodes[cur].cnt += nodes[nxt[cur]].cnt;
                nxt[cur] = nxt[nxt[cur]];
                pre[nxt[cur]] = cur;
                sz--;
            } else {
                p = cur;
                cur = nxt[cur];
            }
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
