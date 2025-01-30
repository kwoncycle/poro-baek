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

int cmp(pair<pii, int> v1, pair<pii, int> v2){
    int o1 = v2.Y * (v1.X.X - v1.X.Y);
    int o2 = v1.Y * (v2.X.X - v2.X.Y);
    return o1 > o2;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n; cin >> n;
    string s; cin >> s;
    for(int i=0; i<n; i++) s[i] -= 'a';
    vector<pair<pii, int>> vp;
    for(int target = 1; target <= 26; target++){
        vector<int> cnt(26, 0);
        int i0 = 0, i1 = 0;
        int ttl = 0;
        pii mx = {0, 0};
        int hited = 0;
        for(i0=0; i0<n; i0++){
            while(ttl <= target){
                if(i1 >= n) break;
                if(cnt[s[i1]] != 0){
                    cnt[s[i1]]++;
                    i1++;
                }
                else{
                    if(ttl == target) {
                        hited = 1;
                        break;
                    }
                    else{
                        cnt[s[i1]]++;
                        i1++;
                        ttl++;
                    }
                }
            }
            if(mx.X - mx.Y < i1 - i0){
                mx = {i1, i0};
            }
            cnt[s[i0]]--;
            if(cnt[s[i0]] == 0) ttl--;
        }
        vp.push_back({mx, target});
    }
    sort(vp.begin(), vp.end(), cmp);
    cout << vp[0].X.Y+1 << " " << vp[0].X.X << "\n";
    return 0;
}