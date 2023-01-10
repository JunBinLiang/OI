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

//1:57  2:10
const int N = 2e5 + 10;
int a[N];
bool take[N];
int n, m;

struct Q{
    int ty, idx, x;
};

void solve() {
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    memset(take, false, sizeof take);


    vector<Q> b;    
    scanf("%d", &m);
    for(int i = 0; i < m; i++) {
        int ty;
        scanf("%d", &ty);
        if(ty == 1) {
            int idx, x;
            scanf("%d%d", &idx, &x);
            b.push_back({ty, idx - 1, x});
        } else {
            int x;
            scanf("%d", &x);
            b.push_back({ty, -1, x});
        }
    }

    int mx = -1;
    for(int i = m - 1; i >= 0; i--) {
        if(b[i].ty == 2) {
            mx = max(mx, b[i].x);
        } else { //update pos -> x
            if(!take[b[i].idx]) {
                a[b[i].idx] = max(mx, b[i].x);
                take[b[i].idx] = true;
            }
        }
    }

    for(int i = 0; i < n; i++) {
        if(!take[i] && a[i] < mx) {
            a[i] = mx;
        }
    }

    for(int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    cout << endl;

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

