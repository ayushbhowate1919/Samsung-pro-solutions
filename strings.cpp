#include <bits/stdc++.h>
using namespace std;

int f(int indx , int dig , int fdig , vector<vector<vector<int>>>& dp , 
       vector<string>& vst){
    int n = vst.size();
    
    // function shoudl not reach here , as it means , 
    // it hasnt choose the last pick yet ; 
    if(indx == n){
         if(fdig == dig)
         return 0 ;
         
         return -1e8;
    }
    
    if(dp[indx][dig][fdig]!=-1)
    return dp[indx][dig][fdig];
    
    
    int digstart = vst[indx][0] - '0' ;
    int digend = vst[indx].back() - '0' ; 
    int len = vst[indx].size();
    
    int pick = 0 ; 
    
    if(dig == 10){
         pick = len + f(indx+1 , digend , digstart , dp , vst);
    }
    
    
    if(dig == digstart) 
    pick = len + f(indx+1 , digend , fdig , dp , vst);
    

    int npick = 0 + f(indx+1 , dig , fdig , dp , vst);
    
    return dp[indx][dig][fdig] = max({pick , npick});
    
    
}
void solve(){
    int n ; 
    cin>>n ; 
    
    vector<string> vst(n) ;
    
    for(int i = 0 ; i <n ; i++){
         cin>>vst[i];
    }
    
    // we'll solve this using recursive dp ; 
    
    // dp[i][dig] , length of longest valid string from index i to n-1 with last chosen 
    // digit as dig ; 
    
    // update : we would need other state , telling the first letter of the 
    //partially built string 
    //
     
     
    // vector<vector<int>> dp(n , vector<int>(11 , -1));
    
    vector<vector<vector<int>>> dp(n , vector<vector<int>>(11 , vector<int>(11 , -1)));
    
    // using 10 , as we haven't choose anything before ; 
    int temp =  f(0 , 10 , 10 , dp , vst );
   
    cout<<temp<<"\n";
   cout<<"******************"<<"\n";
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
