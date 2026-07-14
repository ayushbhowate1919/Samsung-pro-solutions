#include <bits/stdc++.h>
using namespace std;

void solve(){
    int n ; 
    cin>>n ; 
    
    vector<int> a(n) , b(n) , c(n);
    
      for(int i = 0 ; i <n ; i++)
      cin>>a[i];
      
      for(int i = 0 ; i <n ; i++)
      cin>>b[i];
      
      for(int i = 0 ; i <n ; i++)
      cin>>c[i];
      
      
      
      vector<vector<int>> dp(n , vector<int>(2 , 0));
   
   //dp[i][0] : min cost to feed rabbits [0....i] and i+1 rabbit is fed before i ; 
   // dp[i][1] : min cost to feed rabbits [0....i] and i is fed before i+1 ; 
   
   dp[0][0] = b[0];
   dp[0][1] = a[0];
   
   for(int i = 1 ; i <n ; i++){
       dp[i][0] = max(dp[i-1][0] + b[i] , dp[i-1][1] + c[i]);
       
       dp[i][1] = max(dp[i-1][0] + a[i] , dp[i-1][1] + b[i]);
   }
   
   cout<<dp[n-1][1]<<"\n";
    
}
int main() {
	// your code goes here
   solve();
   return 0 ; 
}
