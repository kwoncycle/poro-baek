#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define X first
#define Y second
#define CNT_LOWER(v, n) (int)(lower_bound((v).begin(), (v).end(), (n)) - (v).begin())
#define CNT_UPPER(v, n) (int)(upper_bound((v).begin(), (v).end(), (n)) - (v).begin())

// CNT_LOWER: number of element in v smaller than n
// CNT_UPPER: number of element in v smaller or same than n

struct SuffixArray
{
    string s;
    int d, n;
    vector<int> gr, sa, lcp, tmp, cnt;
    SuffixArray(string &a)
    {
        init(a);
        isa();
        ilcp();
    }
    void init(string &a)
    {
        s = a;
        n = s.size();
        gr.resize(n + 1);
        sa.resize(n);
        lcp.resize(n);
        tmp.resize(n);
        cnt.resize(max(300, n));
    }
    bool cmp(int x, int y)
    {
        if (gr[x] != gr[y])
            return gr[x] < gr[y];
        x += d;
        y += d;
        if (x >= n || y >= n)
            return x > y;
        return gr[x] < gr[y];
    }
    void counting_sort()
    {
        int i, sz = max(300, n);
        fill(cnt.begin(), cnt.end(), 0);
        for (i = 0; i < n; i++)
            cnt[gr[min(i + d, n)] + 1]++;
        for (i = 1; i < sz; i++)
            cnt[i] += cnt[i - 1];
        for (i = n - 1; i >= 0; i--)
            tmp[--cnt[gr[min(i + d, n)] + 1]] = i;
        fill(cnt.begin(), cnt.end(), 0);
        for (i = 0; i < n; i++)
            cnt[gr[i]]++;
        for (i = 1; i < sz; i++)
            cnt[i] += cnt[i - 1];
        for (i = n - 1; i >= 0; i--)
            sa[--cnt[gr[tmp[i]]]] = tmp[i];
    }
    void isa()
    {
        int i;
        gr[n] = -1;
        for (i = 0; i < n; i++)
        {
            gr[i] = s[i] - 'a' + 1;
            sa[i] = i;
        }
        for (d = 1;; d <<= 1)
        {
            counting_sort();
            fill(tmp.begin(), tmp.end(), 0);
            for (i = 1; i < n; i++)
                tmp[i] = tmp[i - 1] + cmp(sa[i - 1], sa[i]);
            for (i = 0; i < n; i++)
                gr[sa[i]] = tmp[i];
            if (tmp[n - 1] == n - 1)
                break;
        }
    }
    void ilcp()
    {
        int i, j, k;
        for (i = 0, k = 0; i < n; i++, k = max(0, k - 1))
        {
            if (gr[i] == n - 1)
                continue;
            for (j = sa[gr[i] + 1]; s[i + k] == s[j + k]; k++)
                ;
            lcp[gr[i]] = k;
        }
    }
};

int main(){
    
}