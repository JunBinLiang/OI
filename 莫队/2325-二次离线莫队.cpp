#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <cmath>
#include <vector>

using namespace std;

typedef long long LL;

const int N = 100010;

int n,m,k,len;
int w[N];
LL ans[N];
struct Query{
    int id,l,r;
    LL res;//每个询问的结果
}q[N];
struct Range{//前缀的询问区间
    int id,l,r,t;
};
vector<Range> range[N];//对于每一个前缀的询问区间  
//由于利用前缀和思想 S[R]-S[L-1] 但是在莫队移动区间的时候S[l-1]在变化难求
int f[N],g[N];
//f[i]:表示w[1]到w[i]中有多少个数与w[i+1]配对
//g[x]:表示前i个数中有多少个与x配对

int get_count(int x){
    int res=0;
    while(x) res+=x&1,x>>=1;
    return res;
}

int get(int x){
    return x/len;
}

bool cmp(const Query&a ,const Query& b){
    int i=get(a.l),j=get(b.l);
    if(i!=j) return i<j;
    return a.r<b.r;
}

int main()
{
    cin>>n>>m>>k;
    for(int i=1;i<=n;i++) cin>>w[i];
    vector<int> nums;//满足要求的数 恰好有k个1的数
    for(int i=0;i<1<<14;i++){
        if(get_count(i)==k)
            nums.push_back(i);
    }
    for(int i=1;i<=n;i++){
        for(auto y:nums) ++g[w[i]^y];//表示w[i]能和w[i]^y匹配
        f[i]=g[w[i+1]];//由于是一层一层遍历上来的 所以可以直接查询
    }
    for(int i=0;i<m;i++){
        int l,r;
        cin>>l>>r;
        q[i]={i,l,r};
    }
    len=sqrt(n);
    sort(q,q+m,cmp);

    //莫队
    for(int i=0,L=1,R=0;i<m;i++){
        int l=q[i].l,r=q[i].r;
        //[1]右端点要右移
        if(R<r) range[L-1].push_back({i,R+1,r,-1});//存一下要查询的范围 对于第i次查询 L-1 要算R+1到r S[r]-S[L-1]
        //每次区间的移动都要用到新的f[L-1];
        //个数要加上和新加入的f[R]匹配的S[R]-S[L-1] 所以此时t=-1
        while(R<r) q[i].res+=f[R++];//到R匹配的个数
        //[2]右端点要左移
        if(R>r) range[L-1].push_back({i,r+1,R,1});
        //由于要删掉 w[R] 所以是要-(S[R-1]-S[L-1])
        while(R>r) q[i].res-=f[--R];
        //[3]左端点要右移
        //要-(S[R]-S[L])
        if(L<l) range[R].push_back({i,L,l-1,-1});//对于L到l 求一下有多少个数与w[R]配对
        while(L<l) q[i].res+=f[L-1]+!k,L++;//*由于要减去S[L]表示1到L与w[L]匹配的数 而f[L-1]表示1到L-1与w[L]匹配的数 所以要加特判判断k是否等于0
        //[4]左端点要左移
        //+S[R]-S[L-1]
        if(L>l) range[R].push_back({i,l,L-1,1});
        while(L>l) q[i].res-=f[L-2]+!k,L--;
    }

    //求range
    memset(g,0,sizeof g);
    for(int i=1;i<=n;i++){
        for(auto x:nums) ++g[w[i]^x];
        for(auto& rg:range[i]){//对于每个固定位置i 有一个区间需要遍历
            int id=rg.id,l=rg.l,r=rg.r,t=rg.t;
            for(int x=l;x<=r;x++){
                q[id].res+=g[w[x]]*t;//每个询问都重新求一遍
            }
        }
    }

    for(int i=1;i<m;i++) q[i].res+=q[i-1].res;
    for(int i=0;i<m;i++) ans[q[i].id]=q[i].res;
    for(int i=0;i<m;i++) printf("%lld\n",ans[i]);

    return 0;

}
