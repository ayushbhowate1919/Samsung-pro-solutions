#include <bits/stdc++.h>
#define ll long long 
using namespace std;

void solve(){
    ll n ; 
    cin>>n ; 
    
    vector<pair<ll ,ll>> vpr ; 
    
    for(int i = 0 ; i <n ; i++){
        ll x , y ;
        cin>>x>>y ; 
        
        vpr.push_back({x , y});
    }
    
    ll p ,q ; 
    cin>>p>>q ; 
    
    vector<ll> dis ; 
    ll maxi = INT_MIN ; 
    ll odd = 0 , even = 0 ; 
    for(int i = 0 ; i <n ;i++){
          ll x = vpr[i].first;
          ll y = vpr[i].second;
          
         ll k = abs(p - x) + abs(q - y);
         dis.push_back(k);
         maxi = max(maxi , k);
         
         if(k&1)
         odd++;
         else
         even++;
    }
    
    if(odd!=0 && even!=0){
         cout<<"-1"<<"\n";
         return;
    }
    
    ll lo = 1 , hi = 1e9 ; 
    ll ans = 0 ; 
    while(lo<=hi){
        ll mid = lo + (hi-lo)/2 ; 
        
        ll num = (1LL * mid * (mid+1))/2 ;
        
        if(num>=maxi){
            hi = mid-1;
            
            ans = mid ; 
        }
        else{
             lo = mid + 1; 
        }
        
    }
    
    // now the the current sum of series could have different parities , 
    // the sum order pattern is ;
    // 1 2 3 4 5 6 
    // 1 3 6 10 15 21
    // o o e e o o e e 
     // thus 5 elements checking is enough to get the correct parity values ; 
     
     ll curr = (1LL * ans * (ans+1))/2 ; 
     
      if(curr&1 && odd>0){
        cout<<ans<<"\n";
        return;
      }
      
      if(!(curr&1) && even>0){
        cout<<ans<<"\n";
        return;
      }
      
      
      // curr is even , make it odd ; 
      if(odd>0){
          
           while(!(curr&1)){
               ans++;
              curr = (1LL * ans * (ans+1))/2 ;
           }
      }
      
      // curr is odd make it even ; 
      
      if(even>0){
          while(curr&1){
               ans++;
              curr = (1LL * ans * (ans+1))/2 ;
          }
      }
      
      cout<<ans<<"\n";
      return;
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
