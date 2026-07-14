#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define vi vector<int>
#define vll vector<long long>
#define pb push_back
#define vvi vector<vector<int>>
#define all(x) x.begin(),x.end()
#define print(a) for(auto it : a) {  cout<<it<<" "; }  cout<<endl; 
#define yes()  cout << "YES" <<endl;
#define no() std::cout << "NO" <<endl;
/* Let's Win */
vector<ll> a ; 
vector<vector<int>> adj;
vector<ll> subsum , dp ; 

void dfs1(int node , int p , int dep){
   subsum[node] = a[node];

  dp[1]+=(1LL * dep * a[node]) ; 

  for(auto it : adj[node]){
      if(it == p)
      continue;
          
      dfs1(it , node , dep+1);
      subsum[node]+=subsum[it];
  }
}

void dfs2(int node , int p ,ll total){
  // assume we are going from u to it : 
  for(auto it : adj[node]){
     if(it == p)
     continue;
    
     dp[it] = dp[node] - subsum[it] + (total - subsum[it]) ;
     
     dfs2(it , node , total);
  }
}


void solve()
{
   int n ; 
   cin>>n ; 
    

   a.resize(n+1);
   adj.resize(n+1);
   subsum.resize(n+1);
   dp.resize(n+1);

    ll total = 0 ; 
   for(int i=1;i<=n;i++){
    cin>>a[i];
    total+=a[i];
   }
  
   for(int i=0;i<n-1;i++){
       int u , v ; 
       cin>>u>>v ; 

       adj[u].push_back(v);
       adj[v].push_back(u);
   }
  
   // dfs1 would help to compute all the subsum values from node , 
   // and also the value of dp[1] , for node 1 ; 
   dfs1(1 , -1 , 0);

   //dfs2 would find the remaining dp values with the help
   // rerooting dp ; 
   dfs2(1 , -1 , total);

    ll ans = 0 ; 
    
    for(int i = 1 ; i <=n ; i++){
       ans = max(ans , dp[i]);
    }

    cout<<ans<<"\n";
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
     solve();
    return 0;
}