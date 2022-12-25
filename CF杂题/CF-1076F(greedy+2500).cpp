#include<bits/stdc++.h>
using namespace std;
const int N=3e5+5;
int n,dpx[N],dpy[N],x[N],y[N],k;
int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)scanf("%d",&x[i]);
	for(int i=1;i<=n;i++)scanf("%d",&y[i]);
	for(int i=1;i<=n;i++){
		dpx[i]=max(0ll,x[i]-(1ll*k*y[i]-dpx[i-1]));
		dpy[i]=max(0ll,y[i]-(1ll*k*x[i]-dpy[i-1]));
		if(dpx[i]>k||dpy[i]>k)return puts("NO"),0;
	}
	puts("YES");
}

