#include <bits/stdc++.h>
using namespace std;

int dfs(int node ,vector<int>& vis , vector<int>& wt , vector<vector<int>>& adj){
    
    vis[node] = 1 ; 
    int cnt = 0 ; 
    int mini = INT_MAX;
    for(auto it : adj[node]){
        if(!vis[it]){
             cnt++;
             mini = min(mini , dfs(it , vis ,wt , adj) );
             
        }
    }

    // even for leaf node , cnt = 0 , would work fine ; 
    
    int curr = (mini * cnt) + wt[node] ; 
    
    return curr ; 
}
int main() {
	// your code goes here
   int n ; 
   cin>>n ; 
   
   vector<vector<int>> adj(n) ; 
   vector<int> wt(n) , vis(n);
   
   int root = 0 ;
   
   for(int i = 0 ; i <n ; i++){
       int p , s ; 
       cin>>p>>s; 
       
        wt[i] = s ;
       
       if(p == -1){
        root = i ;
        continue;
       }
       
       adj[i].push_back(p);
       adj[p].push_back(i);
       
    
   }
   
   int ans = dfs(root , vis ,wt , adj);
   cout<<ans<<"\n";
   
   return 0 ; 
}
