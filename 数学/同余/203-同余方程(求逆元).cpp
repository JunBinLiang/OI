/*
化简整理原式。
原式等价于ax%b=1，即(ax-1)/b=y（y为整数）。由于已知b是正整数，消去得ax-by=1。
由于认为gcd(a, -b)=gcd(a, b)，因此该式等效于ax+by=1。
*/

#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;

int exgcd(int a, int b, int &x, int &y)
{
    if (!b)
    {
        x = 1, y = 0;
        return a;
    }

    int d = exgcd(b, a % b, y, x);
    y -= a / b * x;

    return d;
}

int main()
{
    int a, b;
    cin >> a >> b;

    int x, y;
    exgcd(a, b, x, y);

    cout << (x % b + b) % b << endl;

    return 0;
}
