#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 2e7 + 10;

int n;
char a[N], b[N];
int p[N];

void init()
{
    int k = 0;
    b[k ++ ] = '$', b[k ++ ] = '#';
    for (int i = 0; i < n; i ++ ) b[k ++ ] = a[i], b[k ++ ] = '#';
    b[k ++ ] = '^';
    n = k;
}

void manacher()
{
    int mr = 0, mid;
    for (int i = 1; i < n; i ++ )
    {
        if (i < mr) p[i] = min(p[mid * 2 - i], mr - i);
        else p[i] = 1;
        while (b[i - p[i]] == b[i + p[i]]) p[i] ++ ;
        if (i + p[i] > mr)
        {
            mr = i + p[i];
            mid = i;
        }
    }
}

int main()
{
    scanf("%s", a);
    n = strlen(a);

    init();
    manacher();
    int res = 0;
    int j = -1;
    for (int i = 0; i < n; i ++ ) {
        if(p[i] > res) {
            res = p[i];
            j = i;
        }
        //cout << b[i] << " ";
    }
    
    //cout << endl;
    
    /*for(int i = 0; i < n; i++) cout << p[i] << " ";
    cout << endl;*/
    
    string t = "";
    for(int i = p[j] - 1; i >= 1; i--) {
        if(b[j - i] != '#') t += b[j - i];
    }
    if(b[j] != '#') t += b[j];
    for(int i = 1; i <= p[j] - 1; i++) {
        if(b[j + i] != '#') t += b[j + i];
    }
    cout << t << endl;

    return 0;
}
