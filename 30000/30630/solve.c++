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


int R, C;

struct Node1
{
    ll val; int lc, rc, pos;
    Node1() : val(0), lc(-1), rc(-1), pos(-1) {}
};
vector<Node1> nodes1;
int newNode1()
{
    nodes1.push_back(Node1());
    return (int)nodes1.size()-1;
}

struct Node2
{
    int val; int lc, rc;
    Node2() : val(-1), lc(-1), rc(-1) {}
};
vector<Node2> nodes2;
int newNode2()
{
    nodes2.push_back(Node2());
    return (int)nodes2.size()-1;
}

void update1(int node, int tl, int tr, int x, ll val)
{
    //printf("%d %d %d %d %lld\n", node, tl, tr, x, val);
    if(tl==tr)
    {
        nodes1[node].val=val;
        return;
    }

    int mid=tl+tr>>1;
    if(nodes1[node].pos!=-1)
    {
        if(nodes1[node].pos<=mid)
        {
            int t=newNode1(); nodes1[node].lc=t;
            nodes1[nodes1[node].lc].pos=nodes1[node].pos;
            nodes1[nodes1[node].lc].val=nodes1[node].val;
        }
        else
        {
            int t=newNode1(); nodes1[node].rc=t;
            nodes1[nodes1[node].rc].pos=nodes1[node].pos;
            nodes1[nodes1[node].rc].val=nodes1[node].val;
        }
        nodes1[node].pos=-1;
    }

    if(x<=mid)
    {
        if(nodes1[node].lc==-1)
        {
            int t=newNode1(); nodes1[node].lc=t;
            nodes1[nodes1[node].lc].pos=x;
            nodes1[nodes1[node].lc].val=val;
        }
        else update1(nodes1[node].lc, tl, mid, x, val);
    }
    else
    {
        if(nodes1[node].rc==-1)
        {
            int t=newNode1(); nodes1[node].rc=t;
            nodes1[nodes1[node].rc].pos=x;
            nodes1[nodes1[node].rc].val=val;
        }
        else update1(nodes1[node].rc, mid+1, tr, x, val);
    }
    ll t=0;
    if(nodes1[node].lc!=-1) t += (nodes1[nodes1[node].lc].val);
    if(nodes1[node].rc!=-1) t += (nodes1[nodes1[node].rc].val);
    nodes1[node].val=t;
}

ll query1(int node, int tl, int tr, int xl, int xr)
{
    //printf("%d %d %d %d %d\n", node, tl, tr, xl, xr);
    if(xr<tl || tr<xl) return 0;
    if(xl<=tl && tr<=xr) return nodes1[node].val;
    if(nodes1[node].pos!=-1)
    {
        if(xl<=nodes1[node].pos && nodes1[node].pos<=xr) return nodes1[node].val;
        else return 0;
    }
    int mid=tl+tr>>1;
    ll ret=0;
    if(nodes1[node].lc!=-1) ret += (query1(nodes1[node].lc, tl, mid, xl, xr));
    if(nodes1[node].rc!=-1) ret += (query1(nodes1[node].rc, mid+1, tr, xl, xr));
    return ret;
}

void update2(int node, int tl, int tr, int y, int x, ll val)
{
    //printf("%d %d %d %d %d %lld\n", node, tl, tr, y, x, val);
    if(nodes2[node].val==-1) { int t=newNode1(); nodes2[node].val=t; }
    if(tl==tr)
    {
        update1(nodes2[node].val, 1, C, x, val);
        return;
    }
    int mid=tl+tr>>1;
    if(y<=mid)
    {
        if(nodes2[node].lc==-1) { int t=newNode2(); nodes2[node].lc=t; }
        update2(nodes2[node].lc, tl, mid, y, x, val);
    }
    else
    {
        if(nodes2[node].rc==-1) { int t=newNode2(); nodes2[node].rc=t; }
        update2(nodes2[node].rc, mid+1, tr, y, x, val);
    }
    ll t=0;
    if(nodes2[node].lc!=-1) t += (query1(nodes2[nodes2[node].lc].val, 1, C, x, x));
    if(nodes2[node].rc!=-1) t += (query1(nodes2[nodes2[node].rc].val, 1, C, x, x));
    update1(nodes2[node].val, 1, C, x, t);
}

ll query2(int node, int tl, int tr, int yl, int yr, int xl, int xr)
{
    //printf("%d %d %d %d %d %d %d\n", node, tl, tr, yl, yr, xl, xr);
    if(yr<tl || tr<yl) return 0;
    if(yl<=tl && tr<=yr)
    {
        if(nodes2[node].val!=-1) return query1(nodes2[node].val, 1, C, xl, xr);
        else return 0;
    }
    int mid=tl+tr>>1;
    ll ret=0;
    if(nodes2[node].lc!=-1) ret += (query2(nodes2[node].lc, tl, mid, yl, yr, xl, xr));
    if(nodes2[node].rc!=-1) ret += (query2(nodes2[node].rc, mid+1, tr, yl, yr, xl, xr));
    return ret;
}

int root;

void init(int _R, int _C)
{
    int i, j;
    R=_R; C=_C;
    root=newNode2();
}

void update(int P, int Q, ll K)
{
    int i, j;
    P++; Q++;
    update2(root, 1, R, P, Q, K);
}

ll calculate(int P, int Q, int U, int V)
{
    int i, j;
    P++; Q++; U++; V++;
    return query2(root, 1, R, P, U, Q, V);
}



int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    init(400050, 400050);
    //update(4, 2, 2);
    //cout << calculate(0, 0, 4, 2) << "a\n";
    int n; cin >> n;
    vector<pll> v(n);
    for(int i=0; i<n; i++) cin >> v[i].X >> v[i].Y;

    sort(all(v), [&](pll l, pll r){
        return r.X * l.Y < l.X * r.Y;
    });

    int m; cin >> m;
    vector<pll> q(m);
    for(auto &[i, j]:q) cin >> i >> j;

    set<ll> st;
    for(int i=0; i<n; i++) st.insert(v[i].X), st.insert(v[i].Y);
    for(int i=0; i<m; i++) st.insert(q[i].X), st.insert(q[i].Y);
    int id1 = 1;
    map<ll, int> mp;
    for(auto i:st) mp[i] = id1, id1++;
    

    vector<int> qidx(m);
    for(int i=0; i<m; i++) qidx[i] = i;

    sort(all(qidx), [&](int l, int r){
        return q[r].X * q[l].Y < q[l].X * q[r].Y;
    });

    int id = 0;
    vector<int> ans(m);
    for(int i:qidx){
        auto [a, b] = q[i];
        while(id < n){
            if(a * v[id].Y <= v[id].X * b){
                //cout << mp[v[id].X] << mp[v[id].Y] << " update\n";
                update(mp[v[id].X], mp[v[id].Y], 1);
                id++;
            }
            else break;
        }
        //cout << mp[a] << " " << mp[b] << " query\n";
        ans[i] = calculate(0, 0, mp[a], mp[b]);
    }

    for(int i:ans) cout << i << "\n";


    
    return 0;
}