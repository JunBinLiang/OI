#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>


using namespace std;

const int N = 1000010;

int primes[N], cnt;
bool st[N];
/*
欧拉筛法并不是用目前最小素数的所有倍数来筛合数，而是要筛去一个合数时，用这个合数的最小质因子来筛去它。

欧拉筛法建立了一个数组prime，然后它的下标从1开始依次存的是这个区间的从小到大的素数，然后在外层循环for中让i累加，这里的i其实就是“倍数”的含义，然后循环的时候，取出数组中所有数，然后从小到大地对于i * 这些合数得到的值筛掉（它们都是合数）然后呢，i一直在增加，每一次执行这个筛操作之前，我们都要先判断一下i是否为素数，若是的话就把i加入前面的数组prime之中。

在这个筛操作中，还有一个continue操作的条件需要注意：if (i % prime[j] == 0) break;

这里跳出本次循环直接进行下一次循环的意思是：当i是prime[ j ]的倍数时，i = k * prime[ j ] 如果进行下次循环，j 会加一指到prime数组中的下一个素数，下一次循环中 会出现 i * prime[ j+1 ] 而因为i是prime[ j ] 的倍数，所以上式变为 prime[j] * k * prime[j+1] ，这个表示的是一个合数，而这个合数的最小素因子其实是prime[ j ] ，而不是 prime[j+1] 。也就是说这个时候要筛掉的这个数在前面已经被筛掉了，因为它有一个更小的素因子，所以这已经是一次重复的筛运算了。然后接下来的j递增的内层循环中，i 一直是不变的，所以后面所有的i * prime[ j ] 都是会重复的，故至此跳出本次i的循环，直接进行下一次i的循环了。
-----------------------------------
素数筛（埃氏筛法与欧拉筛）
*/

void init(int n)
{
    for (int i = 2; i <= n; i ++ )
    {
        if (!st[i]) primes[cnt ++ ] = i;
        for (int j = 0; primes[j] * i <= n; j ++ )
        {
            st[primes[j] * i] = true;
            if (i % primes[j] == 0) break;
        }
    }
}

int main()
{
    init(N - 1);

    int n;
    while (cin >> n, n)
    {
        for (int i = 1; ; i ++ )
        {
            int a = primes[i];
            int b = n - a;
            if (!st[b])
            {
                printf("%d = %d + %d\n", n, a, b);
                break;
            }
        }
    }

    return 0;
}
