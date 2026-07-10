#include <bits/stdc++.h>
#define ll long long 
using namespace std;

ll f(ll indx , ll tight , ll sum , ll finsum , vector<vector<vector<ll>>>& dp , string& s){
    ll n = s.size();
    
    if(indx == n){
         if(sum == finsum)
         return 1 ; 
         
         return 0 ; 
    }
    
    if(sum > finsum){
        return 0 ; 
    }
    
    if(dp[indx][tight][sum]!=-1)
    return dp[indx][tight][sum] ;


    int bound = 9 ; 
    
    if(tight){
         bound = s[indx] - '0';
    }
    
    
    ll cnt = 0 ; 
    for(int i = 0 ; i <=bound ; i++){
        ll ntight = tight ; 
        
        if(ntight && i!=(s[indx]-'0')){
            ntight = 0 ;  
        }
        
        cnt+=(f(indx+1 , ntight , sum+i ,finsum , dp , s));
    }
    
    return dp[indx][tight][sum] = cnt ; 
}
void solve(){
    
    string s ;
    cin>>s ; 
    
    ll n = s.size();
    ll finsum ; 
    cin>>finsum ; 
    
  // dp[indx][tight][sum]
  // number of digits from indx to n , with tightness tight , and sum == finsum ;
  // 1 == tight ,
  // 0 is free ; 
  
  
  vector<vector<vector<ll>>> dp(n , vector<vector<ll>>(2 , vector<ll>(finsum+1 , -1)));
   
  ll sum = 0 ;  
  ll ans = f(0 , 1 ,  sum , finsum , dp , s );
  
  cout<<ans<<"\n";
}
int main() {
	// your code goes here
   
   int t ; 
   cin>>t ; 
   
   while(t--){
       solve();
   }
  return 0 ; 
}
