#include<bits/stdc++.h>
using namespace std ;

int main(){
   string s ; 
   cin>>s ; 

   // BRBRBBBRRR 

   // number of stones to be removed = 
   // n - length of longest substring with equal R and B ; 

   int n = s.size();
   // B 1 
   // R -1 ; 

   map<int,int> mpp ; 
   mpp[0] = -1 ; 
   
   int curr = 0 ;
   int maxi = 0 ;  
   for(int i = 0 ; i <n ; i++){
     if(s[i] == 'B')
     curr++;
    else 
     curr--;

     auto it = mpp.find(curr);
      if(it != mpp.end()){
         int ind = (*it).second ;
         
         maxi = max(maxi , i - ind);
      }
      else{
        mpp[curr] = i ; 
      }
   }

  //  cout<<maxi<<"\n";

  int ans = n - maxi ; 
  cout<<ans<<"\n";

}