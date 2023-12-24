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

queue<int> qs[26];
void solve() {
    int n, m;
    string s, t;
    cin >> n >> m >> s >> t;
    if(n < m) {
        cout << "NO" << endl;
        return;
    }

    for(int i = 0; i < 26; i++) {
        while(qs[i].size()) qs[i].pop();
    }

    for(int i = 0; i < s.size(); i++) {
        qs[s[i] - 'a'].push(i);
    }

    for(int i = 0; i < t.size(); i++) {
        int d = t[i] - 'a';
        if(qs[d].size() == 0) {
            cout << "NO" << endl;
            return;
        }
        int index = qs[d].front();
        qs[d].pop();

        for(int j = 0; j < d; j++) {
            while(qs[j].size() > 0 && qs[j].front() < index) qs[j].pop(); 
        }
    }

    cout << "YES" << endl;
}

int main()
{
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }

    return 0;
}

