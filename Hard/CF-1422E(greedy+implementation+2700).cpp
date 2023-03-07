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

vector<string> ans;
vector<pair<char, vector<int>>> stk;
string s;
int sz = 0;
void get() {
    string t = to_string(sz) + " ";
    if(sz <= 10) {
        for(int i = stk.size() - 1; i >= 0; i--) {
            pair<char, vector<int>> &p = stk[i];
            int x = p.second.size();
            while(x--) t += p.first;
        }
    } else {
        int cnt = 5;
        for(int i = stk.size() - 1; i >= 0 && cnt > 0; i--) {
            pair<char, vector<int>> &p = stk[i];
            int x = p.second.size();
            while(x-- && cnt > 0) {
                t += p.first;
                cnt--;
            }
        }
        t += "...";
        if(stk[0].second.size() >= 2) {
            t += stk[0].first;
            t += stk[0].first;
        } else {
            t += stk[1].first;
            t += stk[0].first;
        }
    }
    ans.push_back(t);
}

void solve() {
    cin >> s;

    int nxt = -1;
    for(int i = s.size() - 1; i >= 0; i--) {
        if(stk.size() == 0) {
            stk.push_back({s[i], {i}});
            sz++;
            get();
            continue;
        } 

        if(s[i] == stk.back().first) {
            if(stk.size() == 1 || s[i] > stk[stk.size() - 2].first) {
                if(i + 1 == stk.back().second.back()) { //can pop
                    sz--;
                    stk.back().second.pop_back();
                    if(stk.back().second.size() == 0) stk.pop_back();
                } else { //can not pop
                    stk.back().second.push_back(i);
                    sz++;
                }

            } else {
                stk.back().second.push_back(i);
                sz++;
            }
        } else {
            sz++;
            stk.push_back({s[i], {i}});
        }
        get();
    }

    reverse(ans.begin(), ans.end());
    for(string& t : ans) {
        cout << t << endl;
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

//aabba
