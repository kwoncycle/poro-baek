#include <bits/stdc++.h>
using namespace std;
 
#define ll __int128
#define pii pair<ll,ll>
#define pll pair<ll,ll>
#define X first
#define Y second
#define CNT_LOWER(v,n) (ll)(lower_bound((v).begin(),(v).end(),(n))-(v).begin())
#define CNT_UPPER(v,n) (ll)(upper_bound((v).begin(),(v).end(),(n))-(v).begin())
 
// CNT_LOWER: number of element in v smaller than n
// CNT_UPPER: number of element in v smaller or same than n


ll ccw(pll p1, pll p2){
    ll o = p1.X * p2.Y - p1.Y * p2.X;
    if(o > 0) return -1;// 반시계
    if(o < 0) return 1; // 시계방향
    return 0;
}

vector<pll> poll;
bool y_first_cmp(pair<ll, ll> &a, pair<ll, ll> &b)
{
    if (a.second == b.second)
        return a.first < b.first;
    return a.second < b.second;
}

ll ccww(pair<ll, ll> &a, pair<ll, ll> &b, pair<ll, ll> &c)
{
    return a.first * b.second + b.first * c.second + c.first * a.second - b.first * a.second - c.first * b.second -
           a.first * c.second;
}

ll dist(pair<ll, ll> &a, pair<ll, ll> &b)
{
    return (a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second);
}

bool ccw_cmp(pair<ll, ll> &a, pair<ll, ll> &b)
{
    ll c = ccww(poll[0], a, b);
    if (c == 0)
        return dist(poll[0], a) < dist(poll[0], b);
    return c > 0;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    long long n, m; cin >> n >> m;
    vector<pair<long long, long long>> p(n), q(m);
    for(ll i=0; i<n; i++) {
        long long x, y;
        cin >> x >> y;
        p[i].X = x; p[i].Y = y;
        //cin >> p[i].X >> p[i].Y;
    }
    for(ll i=0; i<m; i++) {
        long long x, y;
        cin >> x >> y;
        q[i].X = x; q[i].Y = y;
    }

    for(ll i=1; i<m; i++) {
        q[i].X -= q[0].X;
        q[i].Y -= q[0].Y;
    }
    q[0] = {0,0};
    for(ll i=0; i<n; i++) p.push_back(p[i]);
    for(ll i=0; i<m; i++) q.push_back(q[i]);
    
    //cout << ccw({0,1}, {1,0});

    ll id = 0;
    for(ll i=0; i<m; i++){
        pll p1 = {q[(i+1)].X - q[i].X, q[(i+1)].Y - q[i].Y};
        pll p3 = {q[(i+2)].X - q[i+1].X, q[(i+2)].Y - q[i+1].Y};
        pll p2 = {p[1].X - p[0].X, p[1].Y - p[0].Y};

        if(ccw(p1, p2) >= 0 and ccw(p2, p3) >= 0){
            id = i; break;
        }   
    }
    vector<pll> vcts;
    for(ll i=0; i<n; i++){
        for(ll t=-1; t<=1; t++){
            vcts.push_back({p[i+1].X + q[(t+id+1+m)%m].X, p[i+1].Y + q[(t+id+1+m)%m].Y});
            vcts.push_back({p[i].X + q[(t+id+1+m)%m].X, p[i].Y + q[(t+id+1+m)%m].Y});
        }
        pll p2 = {p[1+i+1].X - p[i+1].X, p[1+i+1].Y - p[i+1].Y};
        while(true){
            pll p1 = {q[(id+1)].X - q[id].X, q[(id+1)].Y - q[id].Y};
            pll p3 = {q[(id+2)].X - q[id+1].X, q[(id+2)].Y - q[id+1].Y};
            if(ccw(p1, p2) >= 0 and ccw(p2, p3) >= 0){
                break;
            }
            vcts.push_back({p[i+1].X + q[(id+2+m)%m].X, p[i+1].Y + q[(id+2+m)%m].Y});
            id = (id + 1) % m;
        }
    }

    for(ll i=0; i<n; i++) vcts.push_back(p[i]);
    sort(vcts.begin(), vcts.end());
    
    for(ll i=0; i<(ll)vcts.size(); i++){
        if(i == 0) poll.push_back(vcts[i]);
        else{
            if(vcts[i] == vcts[i-1]) continue;
            poll.push_back(vcts[i]);
        }
    }
    vcts.clear();
    ll sz = poll.size();

    sort(poll.begin(), poll.end(), y_first_cmp);
    // 기준 점을 기준으로 반시계 방향으로 나머지 점을 정렬 (일직선상에 있다면 기준점에서 가까운 순서)
    sort(poll.begin() + 1, poll.end(), ccw_cmp);
    vector<pair<ll, ll>> st;
    // 첫 두점을 스택에 넣는다.
    st.push_back(poll[0]);
    st.push_back(poll[1]);
    pair<ll, ll> a, b;
    for (ll i = 2; i < sz; i++)
    {
        // 두 점을 꺼낼 수 있는 동안 반복한다.
        while (st.size() >= 2)
        {
            // 최상단의 두 점을 꺼낸다. 맨 위의 점은 pop한다.
            b = st.back();
            st.pop_back();
            a = st.back();
            // 최상단의 두 점을 이은 직선이 현재 확인하고 있는 점과 반시계 방향으로 연결되어 있다면 break한다.
            if (ccww(poll[i], a, b) > 0)
            {
                // 이 경우 맨위의 점을 pop하면 안되니까 다시 넣어주고 break한다.
                st.push_back(b);
                break;
            }
        }
        // 현재 확인하고 있는 점을 스택에 넣는다.
        st.push_back(poll[i]);
    }

    //for(auto [x,y]:st) cout << x << " " << y << "\n";
    //for(auto [x,y]:vcts) cout << x << " " << y << '\n';

    ll ans = 0;
    st.push_back(st[0]);
    for(ll i=0; i<(ll)st.size()-1; i++){
        ans += (st[i].X*st[i+1].Y - st[i].Y*st[i+1].X);
    }

    ans = abs(ans);

    long long o = ans / 1000000000000ll, o1 = ans % 1000000000000ll;
    if(o == 0){
        cout << o1 << "\n"; return 0;
    }
    
    string s1(12, '0');
    for(int i=11; i>=0; i--){
        s1[i] = '0' + o1 % 10;
        o1 /= 10;
    }
    cout << o;
    cout << s1 << "\n";
    return 0;
}