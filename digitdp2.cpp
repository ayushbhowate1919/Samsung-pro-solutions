#include <bits/stdc++.h>
#define ll long long 
using namespace std;

ll f(ll indx , ll tight , ll sum , string& s , ll finsum , vector<vector<vector<ll>>>& dp){
    int n = s.size();
    
    if(indx == n){
         if(sum == finsum)
         return 1 ; 
         
         return 0 ; 
    }
    
    if(dp[indx][tight][sum]!=-1)
    return dp[indx][tight][sum];
    
    
    int bound = 9 ; 
    
    if(tight)
    bound = (s[indx] - '0') ; 
    
    ll cnt = 0 ; 
    
    for(int i = 0 ; i <=bound ; i++){
        
        ll ntight = tight ; 
        
        if(ntight && (s[indx] - '0')!=i){
            ntight = 0 ; 
        }
        
        if(sum + i > finsum)
        continue ; 
        
        cnt+=(f(indx+1 , ntight , sum + i , s , finsum , dp));
    }
    
    return dp[indx][tight][sum] = cnt ; 
    
}
int main() {
	// your code goes here
  string s ; 
  cin>>s ; 
  
  ll finsum  ; 
  cin>>finsum;
  
  ll n  = s.size();
  
  // dp[i][tight][sum]
  // count of numbers from index i with tightness tight and current sum ; 
  
  vector<vector<vector<ll>>> dp(n , vector<vector<ll>>(2 , vector<ll>(finsum+1 , -1)));
  ll sum = 0 ; 
  ll ans = f(0 , 1 , sum , s , finsum , dp);
  
  cout<<ans<<"\n";  
  return 0 ; 
}
