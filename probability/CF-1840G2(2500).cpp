#include <bits/stdc++.h>
using namespace std;
int ans,n,now,mx;
map<int,int>mp;

mt19937 f(time(0));

void ask(int x){
    cout<<"+ "<<x<<endl;
    now+=x;cin>>x;
    if(mp.count(x))ans=min(ans,now-mp[x]);
    mp[x]=now;mx=max(mx,x);
}

int main(){
    cin>>mx;mp[mx]=0;ans=1e9;
    for(int i=1;i<333;i++)ask(f()%12345+1);
    for(int i=1;i<=333;i++)ask(1);
    ask(mx);
    for(int i=1;i<333;i++)ask(333);
    cout<<"! "<<ans<<endl;
}
