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
 
ifstream fcin("test/input.txt");
//ofstream fcout("test/output.txt");

const int N = 50000 + 10;
const int INF = 2e9;
int n, m;
struct Node {
    int a[10][2]; //min, max
    int sz = 1;
    int idx;
    bool operator < (const Node& other) const {
        for(int i = 0; i < m; i++) {
            if(a[i][1] > other.a[i][0]) {
                return false;
            }
        }
        return true;
    }
    void operator+= (Node other) {
        sz += other.sz;
        for(int i = 0; i < m; i++) {
            a[i][0] = min(a[i][0], other.a[i][0]);
            a[i][1] = max(a[i][1], other.a[i][1]);
        }
    }
    
    void print() {
        cout << "i : " << idx << endl;
        cout << "sz : " << sz << endl;
        for(int i = 0; i < m; i++) {
            cout << a[i][0] << "   " << a[i][1] << endl;
        }
        cout << endl << endl;
    }
    
} nodes[N];



set<Node> s;
void solve() {
    scanf("%d%d", &n, &m);

    for(int i = 0; i < n; i++) {
        nodes[i].idx = i;
        for(int j = 0; j < m; j++) {
            int v;
            scanf("%d", &v);
            nodes[i].a[j][0] = nodes[i].a[j][1] = v;
        }

        while(s.size() > 0) {
            auto it = s.upper_bound(nodes[i]);
            if(it != s.end()) {
                if(it != s.begin()) {
                    it--;
                    if((*it) < nodes[i]) {
                        break;
                    } else {
                        nodes[i] += (*it);
                        s.erase(it);
                    }
                } else {
                    break;
                }
            } else {
                while(s.size()) {
                    auto it1 = s.end();
                    it1--;
                    if((*it1) < nodes[i]) {
                        break;
                    } else {
                        nodes[i] += (*it1);
                        s.erase(it1);
                    }
                }
                break;
            }
        }
        
        s.insert(nodes[i]);
        
        cout << s.rbegin() -> sz << endl;
    }
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
