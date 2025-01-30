#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
#define pii pair<int,int>
#define pll pair<ll,ll>
#define X first
#define Y second
#define CNT_LOWER(v,n) (int)(lower_bound((v).begin(),(v).end(),(n))-(v).begin())
#define CNT_UPPER(v,n) (int)(upper_bound((v).begin(),(v).end(),(n))-(v).begin())
 
// CNT_LOWER: number of element in v smaller than n
// CNT_UPPER: number of element in v smaller or same than n

#define LINE array<pii, 2>
// LINE: l[0] + kl[1]

pii operator + (pii l, pii r){return {l.X+r.X, l.Y+r.Y};};
pii operator - (pii l, pii r){return {l.X-r.X, l.Y-r.Y};};
ll operator * (pii l, pii r){return (ll)l.X*r.X + (ll)l.Y*r.Y;};
ll operator / (pii l, pii r){return (ll)l.X*r.Y - (ll)l.Y*r.X;};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n; cin >> n;
    multiset<ll> st;

    for(int i=0; i<n*(n-1)/2; i++){
        int a; cin >> a; 
        st.insert(a);
    }

    if(n == 2){
        cout << min(0ll, *st.begin()) << " " << max(0ll, *st.begin()) << "\n";
        return 0;
    }

    if(n == 3){
        auto i = st.begin();
        ll i1 = *i++, i2 = *i++, i3 = *i++;
        if((i1+i2+i3)%2 == 1) cout << "Impossible\n";
        else{
            ll o = (i1+i2+i3)/2;
            vector<ll> ans = {o-i1, o-i2, o-i3};
            sort(ans.begin(), ans.end());
            cout << ans[0] << " " << ans[1] << " " << ans[2] << "\n";
        }
        return 0;
    }
    set<int> si;
    for(int i:st) si.insert(i);
    auto t = st.rbegin();
    ll i1 = *t++, i2 = *t++, i3 = *t++, i4;
    while(*t == i3) t++;
    i4 = *t;
    for(auto i=si.rbegin(); i!=si.rend(); i++)
    {
        i3 = *i;
        ll mx;
        {
            if((i1+i2-i3)%2 == 0) mx = (i1+i2-i3)/2;
            else continue;
        }
        multiset<ll> st_keep; for(ll i:st) st_keep.insert(i);
        vector<ll> ans(n); ans[0] = mx;
        int truth = 1;
        for(int i=1; i<n; i++){
            ll t = *st.rbegin() - mx;
            if(abs(t) > 100000000){
                truth = 0; break;
            }
            for(int j=0; j<i; j++){
                if(st.find(ans[j] + t) == st.end()){
                    truth = 0; break;
                }
                st.erase(st.find(ans[j] + t));
            }
            if(!truth) break;
            ans[i] = t;
        }

        if(truth) {
            assert(st.empty());
            sort(ans.begin(), ans.end());
            for(int i=0; i<n; i++) cout << ans[i] << " "; cout << "\n";
            return 0;
        }

        st = st_keep;
    }

    cout << "Impossible\n";
    return 0;
}