#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pll;

ll ar[200005];
int main()
{
    ios::sync_with_stdio(0); cin.tie(0);
    ll n,ans=0;
    cin>>n;
    for(ll i=1;i<=n;i++) cin>>ar[i];
    for(ll i=1;i<=n;i++)
    {
        ans+=abs(ar[i]);
        for(ll j=i+i;j<=n;j+=i) ar[j]-=ar[i];
    }
    cout<<ans;
    return 0;
}