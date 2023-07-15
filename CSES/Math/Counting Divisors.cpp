#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>


using namespace std;

const int N = 1000010;
int cnt[N];


int main()
{
    
    for(int i = 0; i < N; i++) cnt[i] = 1;
    for(int i = 1; i < N; i++) {
        for(int j = i + i; j < N; j += i) {
            cnt[j] ++;
        }
    }
    
    int t;
    cin >> t;
    while(t--) {
        int x;
        scanf("%d", &x);
        printf("%d\n", cnt[x]);
    }
    return 0;
}
