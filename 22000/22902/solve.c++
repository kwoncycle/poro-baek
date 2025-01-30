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
    //ios::sync_with_stdio(false);
    //cin.tie(nullptr); cout.tie(nullptr);
    int n; cin >> n;
    {
    if(n <= 5 or n == 7){
        if(n == 1) cout << "1\n";
        if(n == 2) cout << "1 2\n";
        if(n == 3) cout << "1 3 2 3\n";
        if(n == 4) cout << "1 2 3 4 3 4\n";
        if(n == 5) cout << "1 2 3 5 3 5 4 5 4 5\n";
        if(n == 7) cout << "1 7 2 7 3 7 5 7 3 7 4 7 5 6 5 4 5 6\n";
        return 0;
    }
    vector<int> v(n+2);
    vector<int> prime(n+2, 1);
    for(int i=2; i<=n; i++){
        if(prime[i] == 1){
            for(int j=i+i; j<=n; j+=i) prime[j] = 0;
        }
    }
    int cnt = 0;
    for(int i=2; i<=n; i++){
        for(int j=1; j<i; j++){
            if(__gcd(i,j) == 1) v[i]++, cnt++;
        }
    }
    v[1] = 1; cnt++;

    vector<int> ans;
    for(int i=n; i>=3; i--){
        if(!prime[i] and v[i] > 0){
            if(ans.empty()){
                int i1 = i-1;
                while(v[i]){
                    while(i1 > 1 and !( __gcd(i1, i) == 1 and v[i1] > 0)) i1--;
                    if(i1 == 1) goto out;
                    ans.push_back(i); v[i]--;
                    ans.push_back(i1); v[i1]--;
                }
            }
            else{
                if(__gcd(ans.back(), i) == 1){
                    int i1 = i-1;
                    while(v[i]){
                        while(i1 > 1 and !( __gcd(i1, i) == 1 and v[i1] > 0)) i1--;
                        if(i1 == 1) goto out;
                        ans.push_back(i); v[i]--;
                        ans.push_back(i1); v[i1]--;
                    }
                }
                else{
                    int id = n;
                    while(!(v[id] > 0 and __gcd(id, ans.back()) == 1 and __gcd(id, i) == 1)) id--;
                    if(id == 1) break;
                    ans.push_back(id); v[id]--;
                    int i1 = i-1;
                    while(v[i]){
                        while(i1 > 1 and !( __gcd(i1, i) == 1 and v[i1] > 0)) i1--;
                        if(i1 == 1) goto out;
                        ans.push_back(i); v[i]--;
                        ans.push_back(i1); v[i1]--;
                    }
                }
            }
        }
    }



    out:
    priority_queue<pii> pq;
    for(int i=1; i<=n; i++){
        if(v[i]){
            pq.push({v[i], i});
        }
    }
    while(!pq.empty()){
        if(pq.size() == 1){
            ans.push_back(pq.top().Y); pq.pop(); break;
        }
        pii o1 = pq.top(); pq.pop();
        pii o2 = pq.top(); pq.pop();
        ans.push_back(o1.Y); ans.push_back(o2.Y);
        o1.X--; o2.X--;
        if(o1.X > 0)
        pq.push(o1); 
        
        if(o2.X > 0) 
        pq.push(o2);
    }
    for(int i=0; i<(int)ans.size(); i++) cout << ans[i] << " "; cout << "\n";
    }
//    for(int i:ans) cout << i << " "; cout << "\n";

    //return 0;
}