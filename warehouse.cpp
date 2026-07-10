#include <bits/stdc++.h>
using namespace std;

void solve(){
     int n , m , cost ; 
     cin>>n>>m>>cost ;
     
     vector<vector<int>> grid(n , vector<int>(m)) ; 
      
     //location of garage and airport ;  
     int gr = 0 , gc = 0 , ar = 0 , ac = 0 ;
     // for warehouse ; //max 13 only ; 
     vector<pair<int,int>> wr ;
     
     
     for(int i = 0 ; i <n ; i++){
          for(int j = 0 ; j < m ; j++){
               cin>>grid[i][j];
               
               if(grid[i][j] == 2){
                    gr = i ; 
                    gc = j;
               }
               
               if(grid[i][j] == 4){
                   ar = i ; 
                   ac = j;
               }
               
               if(grid[i][j] == 3){
                  wr.push_back({i , j });    
                   
               }
          }
     }
     
     // now we have to maximise the goods to be taken at airport with cost C given ; 
     
     // C = p*(1 + G) .. 
     // G ---> W1--->A
     //    p1     p2 ; 
     
     // C = (p1 * (1 + 0)) + (p2 * (1 + G1)) ; 
     // C = (p1 + p2) + G1(p2) ; 
     
     // C = total path + G1(path len with G1 carried) + G2(path len with G2 carried)...
     //C = total path + G1(path from warehouse to Airport)
     
     // always optimal to move from garage warehouse and to airport , 
     // if multiple wwarehouse occurs in the path , always better to choose 
     // the nearest to the airport ; 
     
      vector<int> dr = {0,1,0,-1};
      vector<int> dc = {1,0,-1,0};
      int maxg = 0 ; 
     for(int i = 0 ;  i<wr.size() ; i++){
         int r = wr[i].first ; 
         int c = wr[i].second ; 
         
         vector<vector<int>> dis(n , vector<int>(m , 1e8));
         queue<vector<int>> q ;
         dis[r][c] = 0 ; 
         q.push({r , c , d});
         
         while(!q.empty()){
               vector<int> v = q.front();
                int cr = v[0] , cc = v[1] , d = v[2];
              
              q.pop();
              
              for(int j= 0 ; j<4 ; j++){
                   int nr = cr + dr[j];
                   int nc = cc + dc[j];
                   
                   
                   
                   if(nr>=0 && nr<n && nc>=0 && nc<m &&
                    && grid[nr][nc] !=1
                   dis[nr][nc] > (d + 1)){
                       dis[nr][nc] = 1 + d ;
                       q.push({nr , nc , 1+d});
                   }
              }
         }
         
         int pathgw = dis[gr][gc] ;
         int pathwa = dis[ar][ac] ; 
         
         if(pathgw == 1e8 || pathwa == 1e8)
         continue ; 
       
        // C = (pgw + pwa) + G(pwa) ; 
        
        int currg = (cost - (pathgw + pathwa))/pathwa ; 
        
        maxg = max(maxg , currg);
         
     }
     
     cout<<maxg<<"\n";
     
     
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
