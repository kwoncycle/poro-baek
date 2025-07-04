#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define Fi first
#define Se second
#define rep(i, n) for(int (i)=0;(i)<(n);(i)++)
#define szz(x) (int)((x).size())
#define pb push_back
#define all(x) (x).begin(), (x).end()

int Trie[300030][26], tz;
int leaf[300030], fail[300030];
char A[300030];
int T[1<<20], D[300030];
const int ADD = 1<<19, INF = 1e9;
void upd(int x, int v) {
    x += ADD; T[x] = v; x >>= 1;
    while(x) T[x] = min(T[x*2], T[x*2+1]), x >>= 1;
}
int read(int l, int r) {
    int res = INF;
    l += ADD, r += ADD;
    while(l <= r) {
        if(l & 1) res = min(res, T[l++]);
        if(!(r & 1)) res = min(res, T[r--]);
        l >>= 1, r >>= 1;
    }
    return res;
}

void solve() {
    int N;
    cin >> N >> (A+1);
    for(int i=1;i<=N;i++) {
        string s;
        cin >> s;
        int now = 0;
        for(char c : s) {
            int v = c - 'a';
            if(!Trie[now][v]) Trie[now][v] = ++tz;
            now = Trie[now][v];
        }
        leaf[now] = szz(s);
    }
    vector <int> q;
    rep(i, 26) if(Trie[0][i]) q.pb(Trie[0][i]);
    rep(i, szz(q)) {
        int t = q[i];
        rep(j, 26) {
            int &val = Trie[t][j];
            if(!val) val = Trie[fail[t]][j];
            else {
                fail[val] = Trie[fail[t]][j];
                leaf[val] = max(leaf[val], leaf[fail[val]]);
                q.pb(val);
            }
        }
    }
    int now = 0;
    int L = (int)strlen(A+1);
    for(int i=1;i<=L;i++) {
        now = Trie[now][A[i] - 'a'];
        D[i] = INF;
        if(leaf[now]) D[i] = min(D[i], read(i - leaf[now], i - 1) + 1);
        upd(i, D[i]);
    }
    if(D[L] == INF) cout << "-1\n";
    else cout << D[L] << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1; // cin >> T;
    for(int tc=1;tc<=T;tc++) {
        // cerr << "! " << tc << "\n";
        // cout << "Case #" << tc << ": ";
        solve();
    }
    return 0;
}
