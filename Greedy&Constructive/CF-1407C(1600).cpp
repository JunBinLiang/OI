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
   
using namespace std;  

using ll = long long;
#define pb push_back
#define ve vector
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define RFOR(i, a, b) for (int i = a; i >= b; i--)
#define f first
#define se second
#define W while
#define um unordered_map
#define us unordered_set
#define be begin
#define en end

int ask(int l, int r) {
    cout << "? " << l << " " << r << endl;
    cout.flush();
    int x;
    cin >> x;
    return x;
}

const int N = 1e4 + 10;
int a[N];
bool is[N];

int main() {
    int n;
    cin >> n;
    memset(is, false, sizeof is);
    
    queue<int> q;
    for(int i = 1; i <= n; i++) {
        q.push(i);
    }
    
    
    while(q.size() > 1) {
        int i = q.front(); q.pop();
        int j = q.front(); q.pop();
        int x = ask(i, j), y = ask(j, i);
        if(x > y) {
            a[i] = x;
            q.push(j);
            is[x] = true;
        } else {
            a[j] = y;
            q.push(i);
            is[y] = true;
        }
    }
        
    if(q.size() > 0) {
        int top = q.front();
        for(int i = 1; i <= n; i++) {
            if(!is[i]) {
                a[top] = i;
                break;
            }
        }
    }
    
    
    
    cout << "! ";
    for(int i = 1; i <= n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");   
    
    return 0;
}

//x % y = m1 
//y % x = m2
