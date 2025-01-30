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


#define segtreetype int
class SegTree
{
    int n;
    vector<segtreetype> segtree, arr;
 
public:
    SegTree(int n_input, vector<segtreetype>& arr_input){
        n = n_input;
        segtree = vector<segtreetype>(4*n+10, 0);
        arr = vector<segtreetype>(n);
        for(int i=0; i<n; i++) arr[i] = arr_input[i];
        init(1, 0, n-1);
    }

    void init(int node, int start, int end){
        if(start == end){
            segtree[node] = arr[start];
            return;
        }
        init(node*2, start, (start + end)/2);
        init(node*2 + 1, (start + end)/2 + 1, end);

        // CHANGE THIS AS WELL
        segtree[node] = segtree[node*2] + segtree[node*2 + 1];
    }
    void update(int target, segtreetype val){
        arr[target] += val;
        update_segtree(1, 0, n-1, target, val);
    }
    void update_segtree(int node, int start, int end, int target, segtreetype val) {
        if(target < start or end < target) return;
        if(start == end){
            segtree[node] += val;
            return;
        }

        update_segtree(2*node, start, (start + end)/2, target, val);
        update_segtree(2*node + 1, (start + end)/2 + 1, end, target, val);
        
        // CHANGE AS NEEDED
        segtree[node] = segtree[node*2] + segtree[node*2 + 1];
        return;
    }
 
    segtreetype query(int node, int start, int end, int left, int right) {
        if(right < start or end < left) return 0;
        if(left <= start and end <= right) return segtree[node];

        segtreetype q1 = query(node*2, start, (start + end)/2, left, right);
        segtreetype q2 = query(node*2 + 1, (start + end)/2 + 1, end, left, right);

        // CHANGE AS NEEDED
        return q1 + q2;
    }
};
// USAGE: SegTree segtree(n, arr);

long long summ(vector<long long>& tree, int index)
{
    // 합 구하기
    // index를 이진수로 나타낸 뒤 비트 내 1이 없어질 때까지 더한다.
    // index = 13일 때, A[1] + ... + A[13] = tree[1101] + tree[1100] + tree[1000]

    long long ans = 0;
    while (index > 0) {
        ans += tree[index];
        index -= (index & -index); // 최하위 비트(1) 지우기
    }
    return ans;
}

void update(vector<long long>& tree, int index, long long value)
{
    // 변경
    // sum과 반대로 최하위 비트에 1을 더한다.

    while (index < tree.size()) {
        tree[index] += value;
        index += (index & -index);
    }
}



int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n; cin >> n;
    vector<int> v(n);
    for(int i=0; i<n; i++) cin >> v[i];
    map<int,int> mp;
    int id = 0;
    for(int i=0; i<n; i++){
        if(mp.find(v[i]) == mp.end()){
            mp[v[i]] = id; id++;
        }
        v[i] = mp[v[i]];
    }

    vector<vector<int>> cnt(id);
    for(int i=0; i<n; i++) cnt[v[i]].push_back(i);
    ll ans = 0;
    for(int i=0; i<id; i++){
        ll sz = cnt[i].size();
        if(sz * sz <= 2*n){
            vector<int> c;
            c.push_back(-1);
            for(int j:cnt[i]) c.push_back(j);
            c.push_back(n);
            for(int i1=1; i1<=sz; i1++){
                for(int i2=i1; i2<=sz; i2++){
                    // c[i1-1]+1 ~ c[i1]   // c[i2] ~ c[i2+1] - 1
                    int u = i2 - i1 + 1;
                    // smaller than 2*u
                    ll v1 = 0;
                    ll ed = c[i1] + 2*u - 2;
                    if(c[i2] <= ed){
                        if(ed <= c[i2+1] - 1){
                            v1 = ed - c[i2] + 1;
                        }
                        else{
                            v1 = c[i2+1] - c[i2];
                        }
                    }

                    ll v2 = 0;
                    ed = c[i1-1] + 1 + 2*u - 2;
                    if(c[i2] <= ed){
                        if(ed <= c[i2+1] - 1){
                            v2 = ed - c[i2] + 1;
                        }
                        else{
                            v2 = c[i2+1] - c[i2];
                        }
                    }
                    if(v2 > 0){
                        ans += (v2 + v1) * (c[i1] - c[i1-1]) / 2;
                    }
                    else{
                        ans += v1 * (v1 + 1) / 2;
                    }
                }
            }
        }
        else{
            vector<int> arr(n, -1);
            for(int j:cnt[i]) arr[j] = 1;
            //vector<int> sgarr(2*n+10, 0); // o +n+5
            vector<ll> arrr(2*n+11), tree(2*n+11);
            //SegTree sgtree(2*n+10, sgarr);
            int cur = 0;
            //sgtree.update(cur + n+5, 1);
            update(tree, cur+n+5, 1);
            for(int j=0; j<n; j++){
                cur += arr[j];
                //if(arr[j] == 1) ans++;
                ans += summ(tree, cur-1+n+5);
                //ans += sgtree.query(1,0,2*n+9,0,cur-1+n+5);
                update(tree, cur+n+5, 1);
            }
        }
    }

    cout << ans << "\n";
    return 0;
}