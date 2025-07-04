#include <bits/stdc++.h>
using namespace std;
#define MAXN 10
struct MaxFlow {
    struct edge { int x,z,c; };
    vector<edge> v[MAXN];
    int lv[MAXN],last[MAXN];
    void add_edge(int x,int y,int c){
        v[x].push_back({y,v[y].size(),c});
        v[y].push_back({x,v[x].size()-1,0});// << 이거
    }
};

int main()
{
    cout << "HI\n";
    return 0;
}