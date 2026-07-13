#include <bits/stdc++.h>
using namespace std;

void mergeIntervals(vector<pair<int,int>>& vpr){
    sort(vpr.begin() , vpr.end());
    
    int i = 0 ; 
    while(i<vpr.size()){
         int l = vpr[i].first ; 
         int r = vpr[i].second ; 
         
         
    }
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
         int xa = points[i].first ; 
         int ya = points[i].second ; 
         
         int xb = points[i+1].first ; 
         int yb = points[i+1].second ; 
         
         
          if(xa == xb){
               mpx[xa].push_back({min(ya , yb) , max(ya , yb)});
          }
          else{
              mpy[ya].push_back({min(xa , xb) , max(ya , yb)});
          }
          
    }
    
    
  
    return 0;
}
