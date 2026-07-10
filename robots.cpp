#include <bits/stdc++.h>
#define ll long long 
using namespace std;

ll f(int indx , int prev , int m , vector<vector<ll>>& dp , vector<ll>& v){
    
    int n = v.size();
    
    if(indx >= n){
        return 0 ; 
    }
    
    if(dp[indx][prev]!=-1)
    return dp[indx][prev] ; 
    
    // at every index u can either put the robot or let the last robot clean it ; 
    
    ll place = m + f(indx+1 , indx , m ,dp , v);
    ll nplace = (1LL * v[indx] * (indx - prev))+ f(indx+1 , prev , m , dp , v);
    
    return dp[indx][prev] = min(place , nplace);
}
void solve(){
    ll n , m ; 
    cin>>n>>m ; 
    
    vector<ll> v(n);
    
    for(int i = 0 ; i <n ; i++){
         cin>>v[i];
    }
    
    vector<vector<ll>> dp(n, vector<ll>(n , -1));
 //  some of the initial garbage values could be 0 ,
  //thus put robot on first non zero value ; 
  
   int j = 0 ; 
   
   while(j<n){
       if(v[j]!=0){
           break;
       }
       j++;
   }
   
   if(j == n){
        cout<<"0"<<"\n";
        return;
   }
   
   ll ans = m ; 
   
  ans+=f(j+1 , j , m , dp , v );
    
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
