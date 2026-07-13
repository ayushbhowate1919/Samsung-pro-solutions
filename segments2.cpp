#include <bits/stdc++.h>
using namespace std;

 bool isonline(int p , vector<pair<int,int>>& vpr){
   
    if(vpr.size() == 0)
    return false ; 

    int lo = 0 ; 
    int hi = vpr.size()-1 ; 

    while(lo<=hi){
      int mid = (lo+hi)/2 ; 

      if(p>=vpr[mid].first && p<=vpr[mid].second){
         return true ; 
      }

      else if(p > vpr[mid].second){
         lo = mid+1;
      }
      else{
        hi = mid-1;
      }
    }

    return false ; 
 }


vector<pair<int,int>> mergeIntervals(vector<pair<int,int>>& vpr){
    sort(vpr.begin() , vpr.end());

    // vpr.push_back({INT_MAX , INT_MAX});
    
    vector<pair<int,int>> vprnew ; 
    int tot = vpr.size();
    int i = 0 ; 

    while(i<tot){
         int cura = vpr[i].first , curb = vpr[i].second ; 
         while(i<tot-1 && curb >= vpr[i+1].first){
             
            curb = max(curb , vpr[i+1].second ) ; 
            i++;
         }

         vprnew.push_back({cura , curb});
         i++;
    }
    

    return vprnew ; 
}


int main() {
	// your code goes here
    
    int n , m ; 
    cin>>n>>m ; 
    
    vector<pair<int,int>> path , points;
    
   
    map<int , vector<pair<int,int>>> mpx , mpy ; 
    
    for(int i = 0 ; i <n ;i++){
        int x , y ; 
        cin>>x>>y ;
        
        path.push_back({x , y});
    }
    
    for(int i = 0 ; i <m ; i++){
        int x , y ; 
        cin>>x>>y ; 
        
        points.push_back({x ,y});
    }
    
     // mpx[x] would give the segments with x as common point ; 
    for(int i = 0 ; i <n-1 ; i++){
         int xa = path[i].first ; 
         int ya = path[i].second ; 
         
         int xb = path[i+1].first ; 
         int yb = path[i+1].second ; 
         
         
          if(xa == xb){
               mpx[xa].push_back({min(ya , yb) , max(ya , yb)});
          }
          else{
              mpy[ya].push_back({min(xa , xb) , max(xa , xb)});
          }
          
    }
    
    
    for(auto& it : mpx){
        vector<pair<int,int>>& curr = it.second ;
         curr = mergeIntervals(curr);
    }
     
   for(auto& it : mpy){
        vector<pair<int,int>>& curr = it.second ;
         curr = mergeIntervals(curr);
    } 
    

    // traverse on points ; 
     int cnt = 0 ; 

    for(int i=0;i<m;i++){
         int x = points[i].first ; 
         int y = points[i].second ; 
         
         bool flag = false ; 

         auto itx = mpx.find(x);
         auto ity = mpy.find(y);
         // on vertical line ; 
         if(itx!=mpx.end() && isonline(y , itx->second))
         flag = true ; 

         if(!flag && ity!=mpy.end() && isonline(x , ity->second))
         flag = true ;
        
         if(flag)
         cnt++;

    }

    cout<<cnt<<"\n";

    return 0;
}
