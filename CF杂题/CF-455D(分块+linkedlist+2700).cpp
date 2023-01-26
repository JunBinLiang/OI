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

 
template <typename U, typename T, class Cmp>
ostream& operator <<(ostream& out, const unordered_map<U, T, Cmp>& a) {
  out << "{"; bool first = true;
  for (auto& p : a) { out << (first ? "" : ", "); out << p.first << ":" << p.second; first = 0;} out << "}";
  return out;
} 
 
//ifstream fcin("test/input.txt");
//ofstream fcout("test/output.txt");

//分块 + 链表
//思路：只要移动每个块内的head + tail

const int N = 1e5 + 10;
const int M = 1010;
int n, m;
int a[N], b[N], start[M], sizes[M], cnts[M];
int maps[320][N];
int idx = 0;
int bid = 0;

int head[M], tail[N];

struct Node {
    int pre = -1, nxt = -1, val;
} nodes[N * 4];

void add(int blo, int i, int j) { //i -> j
    int pre = nodes[j].pre;
    nodes[pre].nxt = i;
    nodes[i].pre = pre;

    nodes[i].nxt = j;
    nodes[j].pre = i;

    maps[blo][nodes[i].val]++;
}

void del(int blo, int i) {
    int pre = nodes[i].pre, nxt = nodes[i].nxt;
    nodes[nxt].pre = pre;
    nodes[pre].nxt = nxt;

    maps[blo][nodes[i].val]--; 
}

void solve() {
    memset(cnts, 0, sizeof cnts);
    memset(maps, 0, sizeof maps);
    
    cin >> n;
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    int blo = sqrt(n);
    int cnt = 0;
    for(int i = 0; i < n; i++) {
        cnt++;
        b[i] = bid;
        if(cnt >= blo || i == n - 1) {
            cnt = 0;
            bid++;
        }
    }

    int tot = 0;
    for(int i = 0; i < n; i++) {
        int j = i;
        int ith = b[i];
        start[ith] = i;
        vector<int> in;
        sizes[b[i]] = tot;
        while(j < n && b[j] == b[i]) {
            cnts[ith]++;
            maps[ith][a[j]]++;
            in.push_back(j);
            tot++;
            j++;
        }
        //creat a block of LinkedList
        nodes[idx] = {-1, -1, -1};
        head[ith] = idx;
        idx++;
        for(int x : in) {
            nodes[idx] = {-1, -1, a[x]};
            nodes[idx].pre = idx - 1;
            nodes[idx - 1].nxt = idx;
            idx++;
        }
        tail[ith] = idx;
        nodes[idx] = {-1, -1, -1};
        nodes[idx].pre = idx - 1;
        nodes[idx - 1].nxt = idx;
        idx++;
        i = j - 1;
    }

    /*cout << "block  " << blo << endl;
    for(int i = 0; i < n; i++) {
        cout << b[i] << "  ";
    }
    cout << endl;
    
    for(int i = 0; i < n; i++) {
        cout << cnts[i] << "  ";
    }
    cout << endl;
    
    for(int i = 0; i < n; i++) {
        cout << sizes[i] << "  ";
    }
    cout << endl << endl;*/
    



    cin >> m;
    int res = 0;
    for(int i = 0; i < m; i++) {
        int op, l, r;
        scanf("%d%d%d", &op, &l, &r);
        l = (n + l + res - 1) % n;
        r = (n + r + res - 1) % n;
        if(l > r) {
            swap(l, r);
        }
        if(op == 1) { //do shift
            if(l == r) continue;
            
            if(b[l] == b[r]) { //same block
                int cur = nodes[head[b[l]]].nxt;
                int cIdx = sizes[b[l]];
                int p1 = -1, p2 = -1;
                while(true) {
                    if(cIdx == l) {
                        p1 = cur;
                        break;
                    } else {
                        cIdx++;
                        cur = nodes[cur].nxt;
                    }
                }

                while(true) {
                    if(cIdx == r) {
                        p2 = cur;
                        break;
                    } else {
                        cIdx++;
                        cur = nodes[cur].nxt;
                    }
                }

                del(b[l], p2);
                add(b[r], p2, p1);
            } else {
                int cur = nodes[head[b[l]]].nxt;
                int cIdx = sizes[b[l]];
                int p1 = -1, p2 = -1;
                
                while(true) {
                    if(cIdx == l) {
                        p1 = cur;
                        break;
                    } else {
                        cIdx++;
                        cur = nodes[cur].nxt;
                    }
                }

                cIdx = sizes[b[r]];
                cur = nodes[head[b[r]]].nxt;

                while(true) {
                    if(cIdx == r) {
                        p2 = cur;
                        break;
                    } else {
                        cIdx++;
                        cur = nodes[cur].nxt;
                    }
                }
                
                del(b[r], p2);
                add(b[l], p2, p1);
                
                int b1 = b[l], b2 = b[r];
                while(b1 != b2) {
                    int t = nodes[tail[b1]].pre;
                    del(b1, t);
                    add(b1 + 1, t, nodes[head[b1 + 1]].nxt);
                    b1++;
                }
            }

        } else { //find ans
            int k;
            scanf("%d", &k);
            k = ((n + k + res - 1) % n) + 1;
            res = 0;
            
            int b1 = b[l];
            int cur = nodes[head[b1]].nxt;
            int cIdx = start[b1];
            

            //finish the first block
            while(cur != tail[b1]) {
                if(cIdx >= l && cIdx <= r && nodes[cur].val == k) {
                    res++;
                }
                cIdx++;
                cur = nodes[cur].nxt;
            }

            b1++;
            if(head[b1] >= 0) {
                cur = nodes[head[b1]].nxt;
            }
            while(cIdx <= r) {
                if(cIdx + cnts[b1] - 1 <= r) {
                    res += maps[b1][k];
                    cIdx += cnts[b1];
                    b1++;
                    cur = nodes[head[b1]].nxt;
                } else {
                    break;
                }
            }
            

            while(cIdx <= r) {
                if(nodes[cur].val == k) {
                    res++;
                }
                cIdx++;
                cur = nodes[cur].nxt;
            }
            printf("%d\n", res);
        }
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
