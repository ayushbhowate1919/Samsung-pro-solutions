#include <bits/stdc++.h>
using namespace std;

bool ispos(int mid , int k , vector<pair<int,int>>& vpr){
    int n = vpr.size();
    
    for(int i = 0 ; i <n ; i++){
        int curr = vpr[i].first ;
        pair<int,int> pr = {curr + mid , INT_MAX} ; 
        auto it = upper_bound(vpr.begin() , vpr.end() , pr);
        
        
        int ind = it - vpr.begin();
        
        // cout<<i<<" "<<ind<<" "<<curr+mid<<"\n";
        
        if(ind - i < k)
        continue ; 
        
         vector<int> v ;
        
        for(int j = i ; j <ind ; j++){
             v.push_back(vpr[j].second);
        }
        
        sort(v.begin() , v.end());
        
        // for(auto val : v){
        //      cout<<val<<" ";
        // }
        // cout<<"\n";
        
        for(int j = 0; j<v.size() ; j++){
            auto itb = upper_bound(v.begin() , v.end() , v[j] + mid);
            
            
            int indb = itb - v.begin();
            
            if(indb - j >=k)
            return true;
        }
    }
    
    return false ; 
}

void solve(){
//assuming O(n^2) solution is valid ; 

int n ,k ; 
cin>>n>>k;

vector<pair<int,int>> vpr ;

for(int i = 0 ; i <n ; i++){
  int w , h ; 
  cin>>w>>h ; 
  
  vpr.push_back({w , h});
}

sort(vpr.begin() , vpr.end());

// for(auto pr : vpr){
//      cout<<pr.first<<" "<<pr.second<<"\n";
// }

// cout<<"*************"<<"\n";

int ans = INT_MAX ; 
// BS on answers ;
int lo = 0 , hi = 1e9 ; 

while(lo<=hi){
    int mid = (lo) + (hi - lo)/2 ; 
    
    if(ispos(mid , k , vpr)){
        hi = mid - 1 ; 
        ans = mid ; 
    }
    else{
        lo = mid + 1 ; 
    }
}
 

cout<<ans<<"\n";

}
int main() {
	// your code goes here
    solve();
}
