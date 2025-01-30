#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pll;

ll ar[100005];
vector<ll>ans;
int main()
{
    ios::sync_with_stdio(0); cin.tie(0);
    ll T,n;
    cin>>T;
    while(T--)
    {
        ans.clear();
        cin>>n;
        for(ll i=1;i<=n;i++) cin>>ar[i];
        ll mn=n+1,mx=0;
        for(ll i=1;i<n;i++)
        {
            mn=min(mn,ar[i]); mx=max(mx,ar[i]);
            if(mn==1&&mx==i) ans.push_back(i);
        }
        cout<<ans.size()<<'\n';
        for(auto x:ans) cout<<x<<' ';
        cout<<'\n';
    }
    return 0;
}