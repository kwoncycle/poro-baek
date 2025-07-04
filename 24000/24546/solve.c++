#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
#define pii pair<int,int>
#define pll pair<ll,ll>
#define X first
#define Y second
#define CNT_LOWER(v,n) (int)(lower_bound((v).begin(),(v).end(),(n))-(v).begin())
#define CNT_UPPER(v,n) (int)(upper_bound((v).begin(),(v).end(),(n))-(v).begin())
#define all(x) (x).begin(), (x).end()

// CNT_LOWER: number of element in v smaller than n
// CNT_UPPER: number of element in v smaller or same than n

#define LINE array<pii, 2>
// LINE: l[0] + kl[1]

pii operator + (pii l, pii r){return {l.X+r.X, l.Y+r.Y};};
pii operator - (pii l, pii r){return {l.X-r.X, l.Y-r.Y};};
ll operator * (pii l, pii r){return (ll)l.X*r.X + (ll)l.Y*r.Y;};
ll operator / (pii l, pii r){return (ll)l.X*r.Y - (ll)l.Y*r.X;};

const int D = 350;

int n, k, h, w, d;
vector<array<int, 4>> task;
int cnt0[110000], cnt1[D][110000], cnt2[D];
ll ttl;

struct solve{
    solve(){
        cin >> n >> k >> h >> w >> d;
        int h1 = max(1, h-d), h2 = min(101000, h+d);
        int w1 = max(1, w-d), w2 = min(101000, w+d);
        for(int i=0; i<n; i++){
            int hl, hr, wl, wr;
            cin >> hl >> hr >> wl >> wr;
            if(w2 < wl or wr < w1) continue;
            if(h2 < hl or hr < h1) continue;
            wl = max(wl, w1); wr = min(wr, w2);
            wl -= w1; wr -= w1;
            task.push_back({hl, wl, wr, 1});
            task.push_back({hr+1, wl, wr, -1});
        }
        for(int i=0; i<D; i++) cnt1[i][0] = D;
        w2 -= w1;
        w1 = 0;
        sort(all(task));
        n = task.size();
        ll ans = 0;
        int id = 0;
        for(int i=1; i<=h2+100; i++){
            while(id < n and task[id][0] == i){
                if(task[id][3] == 1){
                    add(task[id][1], task[id][2]);
                }
                else{
                    dda(task[id][1], task[id][2]);
                }
                id++;
            }
            if(h1 <= i and i <= h2){
                ans += ttl;
            }
        }
        cout << ans << "\n";
    }

    void add(int l, int r){
        if(l/D == r/D){
            add1(l, r); return;
        }
        if(l%D){
            add1(l, (l/D+1)*D - 1); l = (l/D+1)*D;
        }
        while(l/D < r/D){
            add0(l/D); l += D;
        }
        add1(l, r);
    }
    void add0(int l){
        if(k-cnt2[l]-1 >= 0) ttl += cnt1[l][k-cnt2[l]-1];
        cnt2[l]++;
    }
    void add1(int l, int r){
        int o = l/D;
        for(int i=l; i<=r; i++){
            cnt1[o][cnt0[i]]--;
            cnt0[i]++;
            cnt1[o][cnt0[i]]++;
            if(cnt0[i] + cnt2[o] == k) ttl++;
        }
    }

    void dda(int l, int r){
        if(l/D == r/D){
            dda1(l, r); return;
        }
        if(l%D){
            dda1(l, (l/D+1)*D - 1); l = (l/D+1)*D;
        }
        while(l/D < r/D){
            dda0(l/D); l += D;
        }
        dda1(l, r);
    }
    void dda0(int l){
        if(k-cnt2[l] >= 0) ttl -= cnt1[l][k-cnt2[l]];
        cnt2[l]--;
    }
    void dda1(int l, int r){
        int o = l/D;
        for(int i=l; i<=r; i++){
            cnt1[o][cnt0[i]]--;
            cnt0[i]--;
            cnt1[o][cnt0[i]]++;
            if(cnt0[i] + 1 + cnt2[o] == k) ttl--;
        }
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    
    solve S;
    
    return 0;
}