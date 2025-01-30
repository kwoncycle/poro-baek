#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pll;

ll ar[100005];
int main()
{
    ios::sync_with_stdio(0); cin.tie(0);
    ll T,n;
    cin>>T;
    while(T--)
    {
        pll ans={1,0};
        cin>>n;
        for(ll i=1;i<=n;i++) cin>>ar[i];
        for(ll i=30;i>=1;i--)
        {
            ll x=(1LL<<i)-1;
            set<ll>st;
            for(ll j=1;j<=n;j++) st.insert(ar[j]&x);
            ll mex=0;
            while(st.count(mex)>0) mex++;
            ans=max(ans,pll(mex,x));
        }
        cout<<ans.se<<'\n';
    }
    return 0;
}