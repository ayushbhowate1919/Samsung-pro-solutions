#include <bits/stdc++.h>
using namespace std;

void solve(){
    string s ; 
    cin>>s ; 
    
    // brrbbbbrbbrrr ; 
    // denote b with 1 and r with -1 , 
    // longest subarry with sum 0 ; 
    // we would go with pfsum and map ; 
    
    int n = s.size();
    map<int,int> mpp ; 
    int curr = 0 ; 
    
    mpp[0] = -1 ; 
    
     int len = 1 ;
     
    for(int i = 0 ; i <n ;i++){
           if(s[i] == 'B'){
                curr++;      
           }
           else{
              curr--;    
           }
           
           if(mpp.find(curr) != mpp.end()){
                len = max(len , (i - mpp[curr]));
           }
           else{
                mpp[curr] = i ; 
           }
    }
    
    cout<<len<<"\n";
}
int main() {
	// your code goes here
    int t ; 
    cin>>t ; 
    while(t--){
         solve();
    }
}
