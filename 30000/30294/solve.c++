#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pll;
ll nxt[2005][2005][4];
ll sr[2005][2005];
bool vis[2005][2005];
ll dx[4]={-1,1,0,0};
ll dy[4]={0,0,-1,1};
int main()
{
    ios::sync_with_stdio(0); cin.tie(0);
    ll n,m,k,ans=0;
    queue<pll>q;
    cin>>n>>m>>k;
    for(ll i=0;i<n;i++)
    {
        string s;
        cin>>s;
        for(ll j=0;j<m;j++)
        {
            if(s[j]=='U') sr[i][j]=0;
            if(s[j]=='D') sr[i][j]=1;
            if(s[j]=='L') sr[i][j]=2;
            if(s[j]=='R') sr[i][j]=3;
            if(i+dx[sr[i][j]]*k<0||i+dx[sr[i][j]]*k>=n||j+dy[sr[i][j]]*k<0||j+dy[sr[i][j]]*k>=m)
            {
                q.push({i,j});
                vis[i][j]=1;
            }
        }
    }
    for(ll i=0;i<n;i++)
    {
        ll last=-1;
        for(ll j=0;j<m;j++)
        {
            if(last+k<j) last=-1;
            nxt[i][j][3]=last;
            if(sr[i][j]==3) last=j;
        }
        last=m;
        for(ll j=m-1;j>=0;j--)
        {
            if(last-k>j) last=m;
            nxt[i][j][2]=last;
            if(sr[i][j]==2) last=j;
        }
    }
    for(ll j=0;j<m;j++)
    {
        ll last=-1;
        for(ll i=0;i<n;i++)
        {
            if(last+k<i) last=-1;
            nxt[i][j][1]=last;
            if(sr[i][j]==1) last=i;
        }
        last=n;
        for(ll i=n-1;i>=0;i--)
        {
            if(last-k>i) last=n;
            nxt[i][j][0]=last;
            if(sr[i][j]==0) last=i;
        }
    }
    while(!q.empty())
    {
        ans++;
        ll x,y;
        tie(x,y)=q.front(); q.pop();
        if(nxt[x][y][0]!=n&&vis[nxt[x][y][0]][y]==0)
        {
            q.push({nxt[x][y][0],y});
            vis[nxt[x][y][0]][y]=1;
        }
        if(nxt[x][y][1]!=-1&&vis[nxt[x][y][1]][y]==0)
        {
            q.push({nxt[x][y][1],y});
            vis[nxt[x][y][1]][y]=1;
        }
        if(nxt[x][y][2]!=m&&vis[x][nxt[x][y][2]]==0)
        {
            q.push({x,nxt[x][y][2]});
            vis[x][nxt[x][y][2]]=1;
        }
        if(nxt[x][y][3]!=-1&&vis[x][nxt[x][y][3]]==0)
        {
            q.push({x,nxt[x][y][3]});
            vis[x][nxt[x][y][3]]=1;
        }
    }
    cout<<ans;
    return 0;
}