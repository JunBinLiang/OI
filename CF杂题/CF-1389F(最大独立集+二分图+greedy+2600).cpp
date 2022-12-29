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


//最大独立集:选出最多的点，每两点之间没有边
//最大匹配 = 点总数 - 最大独立集

int n;
struct Seg {
    int l, r, w;
};

bool COMP(Seg& s1, Seg& s2) {
    if(s1.r == s2.r) {
        return s1.l < s2.l;
    }
    return s1.r < s2.r;
}

void solve() {
    scanf("%d", &n);
    vector<Seg> a;
    for(int i = 0; i < n; i++) {
        int l, r, w;
        scanf("%d%d%d", &l, &r, &w);
        a.push_back({l, r, w});
    }

    //overlaping : must be same color

    sort(a.begin(), a.end(), COMP);
    int cnt = 0;
    multiset<int> ms1, ms2;
    for(int i = 0; i < n; i++) {
        if(a[i].w == 2) {
            int l = a[i].l;
            auto it = ms1.upper_bound(l - 1);
            if(it != ms1.end()) {
                cnt++;
                ms1.erase(it);
            } else {
                ms2.insert(a[i].r);
            }
        } else {
            int l = a[i].l;
            auto it = ms2.upper_bound(l - 1);
            if(it != ms2.end()) {
                cnt++;
                ms2.erase(it);
            } else {
                ms1.insert(a[i].r);
            }
        }
    }
    
    cout << n - cnt << endl;
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

