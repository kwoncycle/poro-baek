#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

#define X first
#define Y second
#define CNT_LOWER(v, n) (int)(lower_bound((v).begin(), (v).end(), (n)) - (v).begin())
#define CNT_UPPER(v, n) (int)(upper_bound((v).begin(), (v).end(), (n)) - (v).begin())
#define all(x) (x).begin(), (x).end()

// CNT_LOWER: number of element in v smaller than n
// CNT_UPPER: number of element in v smaller or same than n

#define LINE array<pii, 2>
// LINE: l[0] + kl[1]

pii operator+(pii l, pii r) { return {l.X + r.X, l.Y + r.Y}; };
pii operator-(pii l, pii r) { return {l.X - r.X, l.Y - r.Y}; };
ll operator*(pii l, pii r) { return (ll)l.X * r.X + (ll)l.Y * r.Y; };
ll operator/(pii l, pii r) { return (ll)l.X * r.Y - (ll)l.Y * r.X; };

const int MAXN = 260000; // 2 * Vars
struct TWOSAT
{ // 0-based, x*2 False / x*2+1 True / x^1 Flip
    vector<int> adj[MAXN];
    int n, T, col, top, st[MAXN];
    int in[MAXN], low[MAXN], vis[MAXN], res[MAXN];
    void init(int v)
    {
        n = v * 2;
        T = top = col = 0;
        for (int i = 0; i < n; i++)
            vis[i] = in[i] = res[i] = st[i] = 0, adj[i].clear();
    }
    inline void add(int a, int b)
    {
        adj[a].push_back(b);
    }
    inline void OR(int a, int b)
    { // a or b
        add(a << 1, b << 1 | 1), add(b << 1, a << 1 | 1);
    }
    inline void NOR(int a, int b)
    { // !a or b
        add(a << 1 | 1, b << 1 | 1), add(b << 1, a << 1);
    }
    inline void NAND(int a, int b)
    { // !a or !b
        add(a << 1 | 1, b << 1), add(b << 1 | 1, a << 1);
    }
    inline void XOR(int a, int b)
    { // a xor b
        OR(a, b);
        NAND(a, b); // note that (!a or b) form also ok
    }
    inline void NXOR(int a, int b)
    { // !a xor b
        NOR(a, b); // 
        NOR(b, a); // note that (!a or b) form also ok
    }
    inline void ON(int a)
    { // a always true
        add(a << 1, a << 1 | 1);
    }
    inline void OFF(int a)
    { // a always false
        add(a << 1 | 1, a << 1);
    }
    inline bool isON(int x) { return res[x << 1 | 1] < res[x << 1]; }
    void tarjan(int u)
    {
        in[u] = low[u] = ++T;
        st[++top] = u, vis[u] = 1;
        for (auto &v : adj[u])
        {
            if (!in[v])
                tarjan(v), low[u] = min(low[u], low[v]);
            else if (vis[v])
                low[u] = min(low[u], in[v]);
        }
        if (in[u] == low[u])
        {
            ++col;
            int v;
            do
            {
                v = st[top--];
                vis[v] = 0, res[v] = col;
            } while (v != u);
        }
    }
    bool solve()
    {
        for (int i = 0; i < n; i++)
            if (!in[i])
                tarjan(i);
        for (int i = 0; i < n; i += 2)
            if (res[i] == res[i ^ 1])
                return 0;
        return 1;
    }
} SAT;

int n, m, k;
int group[1005]; // 2i+1: Red i, 2i : Blue i
int v[505][505];

struct Solve
{
    bool ispossible(int O) 
    {
        SAT.init(505); // stay true move false
        for(int i=0; i<n; i++){
            for(int j=i+1; j<n; j++){
                if(v[i][j] < O and (group[i] - group[j]) % 2 == 0){
                    //cout << i << " " << j << "\n";
                    SAT.XOR(i, j);
                }
                else if(v[i][j] < O){
                    SAT.NXOR(i, j);
                }

                if(group[i] == group[j]){
                    SAT.OR(i, j);
                }
            }
        }
        bool b = SAT.solve();
        return SAT.solve();
    }
} S;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n >> m >> k;
    for (int i = 0; i < m; i++)
    {
        int b;
        cin >> b;
        for (int j = 0; j < b; j++)
        {
            int t;
            cin >> t;
            t--;
            group[t] = 2 * i;
        }
    }
    for (int i = 0; i < k; i++)
    {
        int b;
        cin >> b;
        for (int j = 0; j < b; j++)
        {
            int t;
            cin >> t;
            t--;
            group[t] = 2 * i + 1;
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> v[i][j];
            if(i == j) v[i][j] = 0x3f3f3f3f;
        }
    }

    if (n == 2)
    {
        cout << "INFINITY\n";
        return 0;
    }

    int st = 0, ed = 0x3f3f3f3f;
    while (st + 1 < ed)
    {
        int md = (st + ed) / 2;
        if (S.ispossible(md))
            st = md;
        else
            ed = md;
    }
    cout << st << "\n";

    return 0;
}