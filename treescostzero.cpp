#include <bits/stdc++.h>
using namespace std;

int cost = 0 ; 
void dfs(int node , int sub , vector<int>& wt , vector<int>& vis , vector<vector<int>>& adj){
    
    vis[node] = 1 ;
    int curr = wt[node] - sub ; 
    
    cost+=(abs(curr));
    
    for(auto it : adj[node]){
         if(!vis[it]){
             dfs(it , curr+sub , wt , vis , adj);
         }
    } 
}
int main() {
	// your code goes here
	int n ; 
	cin>>n ; 
	
	vector<vector<int>> adj(n);
    vector<int> vis(n);
    vector<int> wt(n);
	
	for(int i = 0 ; i <n-1 ; i++){
	    int u , v; 
	    cin>>u>>v ; 
	    
	    adj[u].push_back(v);
	    adj[v].push_back(u);
	    
	}
	
	for(int i = 0 ; i <n ; i++){
	     cin>>wt[i];
	}
	
	dfs(0,0,wt , vis , adj);
	
	cout<<cost<<"\n";
	
	return 0 ; 

}
