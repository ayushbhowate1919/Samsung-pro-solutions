#include<bits/stdc++.h>
using namespace std;

int main() {
	// your code goes here
	
	 int n , m ; 
	 cin>>n>>m ; 
	 
	 vector<pair<int,int>> path , points; 
	 
	 map<int , vector<int>> mpx, mpy ; 
	 
	 for(int i = 0 ; i <n ; i++){
	      int x , y ; 
	      cin>>x>>y ;
	       
	     path.push_back({x , y});
	 }
	  
	  
	 for(int i = 0 ; i <m ; i++){
	     int x , y ; 
	     cin>>x>>y ; 
	     
	     points.push_back({x , y});
	     
	    
	      
	      mpx[x].push_back(y);
	      mpy[y].push_back(x);
	 }
	 
	 for(auto& it : mpx){
	      sort((it.second).begin() , (it.second).end());
	 }
	 
	 for(auto& it : mpy){
	      sort((it.second).begin() , (it.second).end());
	 }
	 
// 	 for(auto it : mpy){
// 	      cout<<it.first<<": ";
	      
// 	      for(auto itk : it.second){
// 	           cout<<itk<<" ";
// 	      }
	      
// 	      cout<<"\n";
// 	 }	 
	 
	 
	 //for every line we would check the number of points occuring on that line ; 
	 
	 int ans = 0 ; 
	 for(int i = 0 ; i <n-1 ; i++){
	      int xa = path[i].first ; 
	      int ya = path[i].second ; 
	      
	      int xb = path[i+1].first ; 
	      int yb = path[i+1].second ; 
	      
	   //   cout<<xa<<" "<<ya<<" "<<xb<<" "<<yb<<"\n";
	      
	      
	      
	      if(xa == xb){
	           // we would search in [xa ,xb] range ; 
	           
	          vector<int>& v = mpx[xa] ;
	          
	          if(v.size() == 0)
	          continue;
	          
	          if(ya > yb)
	          swap(ya , yb);
	          
	          
	          auto ita = lower_bound(v.begin() , v.end() , ya);
	          auto itb = upper_bound(v.begin() , v.end() , yb);
	          
	       //   cout<<i<<" "<<(itb - ita)<<"\n";
	          
	          ans+=(itb - ita) ; 
	          
	          // the last point of this line would be calculated twice so we would 
	          // remove its on occurence expect for the last line ; 
	          if(yb == v.back() && i!=n-2){
	              ans--;
	          }
	      }
	      
	      else{
	         // we would search in [xa ,xb] range ; 
	           
	          vector<int>& v = mpy[ya] ;
	          
	          if(v.size() == 0)
	          continue;
	          
	           if(xa > xb)
	          swap(xa , xb);
	          
	          auto ita = lower_bound(v.begin() , v.end() , xa);
	          auto itb = upper_bound(v.begin() , v.end() , xb);
	          
	        //  cout<<xa<<" "<<xb<<"\n";
	       //   cout<<i<<" "<<*itb<<" "<<*ita<<"\n";
	          
	          ans+=(itb - ita) ; 
	          
	          // the last point of this line (if exist) would be calculated twice
	          //as it would be starting point for the next line 
	          //so we would remove its on occurence expect for the last line ; 
	          if(xb == v.back() && i!=n-2){
	              ans--;
	          }          
	          
	      }
	     
	 }
	 
	 cout<<ans<<"\n";
	 
	return 0 ; 
}
