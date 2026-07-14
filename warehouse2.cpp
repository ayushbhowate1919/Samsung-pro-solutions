#include <bits/stdc++.h>
using namespace std;

vector<int> dr = {0,1,0,-1};
vector<int> dc = {1,0,-1,0};
// map to turn the coordinates into id ; 
map<pair<int,int> , int> mpp;
int gr = 0 , gc = 0 , ar = 0 , ac = 0 ; 

void bfs(int sr , int sc , vector<vector<int>>& grid , vector<vector<int>>& impos){
    int n = grid.size();
    int m = grid[0].size();
    
    queue<vector<int>> q ; 
    vector<vector<int>> dis(n, vector<int>(m , INT_MAX));
    
    dis[sr][sc] = 0 ; 
    q.push({sr , sc , 0});
    
    while(!q.empty()){
         vector<int> v = q.front();
         int r = v[0] , c = v[1] , d = v[2];
         q.pop();
         
         for(int i = 0 ; i <4 ; i++){
             int nr = r + dr[i] ; 
             int nc = c + dc[i] ;
             
             if(nr>=0 && nr<n && nc>=0 && nc<m && grid[nr][nc]!=1){
                  if(d + 1 < dis[nr][nc]){
                       dis[nr][nc] = d+1 ; 
                       q.push({nr , nc , d+1});
                  }    
             }
         }
    }
    
    int id = mpp[{sr , sc}];
    
   for(int i = 0 ; i <n ; i++){
       for(int j = 0 ; j <m ; j++){
            if(grid[i][j] == 0 || grid[i][j] == 1)
            continue;
            
            int idn = mpp[{i , j}];
            
            impos[id][idn] = dis[i][j];
            impos[idn][id] = dis[i][j]; 
       }
   }
    
}

void solve(){
   // solving the version where , 
    // you have to start from Garage ----> warehouses--->Airport ; 
    // each warehouse contains one good : 
    // and the final aim is to reach airport and unload , (no more turns) ; 
    
    int h , w , c ; 
    cin>>h>>w>>c ; 
    
    vector<vector<int>> grid(h , vector<int>(w));
    
   
    vector<pair<int,int>> whouse;
    
 
    for(int i = 0 ; i <h ; i++){
         for(int j = 0 ; j < w ; j++){
             
              cin>>grid[i][j];
              
              if(grid[i][j] == 2){
                   gr = i ; 
                   gc = j ;
              }
              
              if(grid[i][j] == 3){
                  whouse.push_back({i , j}); 
              }
              
              if(grid[i][j] == 4){
                   ar = i ; 
                   ac = j ;
              }
         }
    }
   
   // find the shortest dist from every imp location to every imp location ; 
   vector<vector<int>> impos(whouse.size()+2 , vector<int>(whouse.size()+2 , INT_MAX));
   int k = whouse.size();
   // w1 w2 w3......g a ; 
      int id = 0 ; 
   for(auto it : whouse){
      int r = it.first ; 
      int c = it.second ; 
      
      mpp[{r , c}] = id ; 
      id++;
   }
   
   mpp[{gr , gc}] = id ; 
   id++;
   mpp[{ar , ac}] = id ; 
   
   
   for(auto it : whouse){
       int r = it.first ; 
       int c = it.second ; 
       
       bfs(r , c , grid , impos);
   }
   
   bfs(gr , gc , grid , impos);
   bfs(ar , ac , grid , impos);
   
   
   //dp[mask][i] , 
   // min cost to choose mask chosen warehouse and be at ith warehouse ; 
   int INF = INT_MAX ; 
   vector<vector<int>> dp(1<<k , vector<int>(k , INF));
   
   //base case , go from garage to any warehouse ; 
   
   for(int i = 0 ; i <whouse.size() ; i++){
       int d = impos[k][i] ; 
       
       dp[1<<i][i] = d ;
   }
   
   
   // transitions ; 
   
   // say we have 100101 as mask , 
   // first iterate for u , i.e on which warehouse you are ;
   // must be set bit from mask ; 
   // then we are going to v , must be unset bit from mask ; 
   
   for(int mask = 1 ; mask < (1<<k) ; mask++){
         for(int u = 0 ; u<k ; u++){
             
             if(!(mask & (1<<u)))
             continue;
             
             for(int v = 0 ; v<k ; v++){
                 if(mask & (1<<v))
                 continue;
                 
                 int nmask = mask | (1<<v) ; 
                 int goods = __builtin_popcount(mask);
                 
                 if(impos[u][v] == INT_MAX)
                 continue;
                 
                 
                 int ncost = (impos[u][v] * (1 + goods)) ; 
                 
                 if(dp[mask][u]!=INF)
                 dp[nmask][v] = min(dp[nmask][v] , dp[mask][u] + ncost) ; 
             }
             
         }
   }
   
   
   int maxgoods = 0 ; 
   
   for(int mask = 0 ; mask<(1<<k) ; mask++){
       // and we are on uth warehouse ; 
       for(int u = 0 ; u <k ; u++){
           if(!(mask & (1<<u)))
           continue;
           
           int goods = __builtin_popcount(mask);
           
            if(dp[mask][u] == INT_MAX || impos[u][k+1] == INT_MAX)
            continue;
            
            
            int fincost = dp[mask][u] + (impos[u][k+1] * (1 + goods));
           
           if(fincost<=c){
               maxgoods = max(maxgoods , goods);
           }    
               
           
            
       }
   }
   
   cout<<maxgoods<<"\n";
}
int main() {
	// your code goes here
    
    solve();
   return 0 ; 
}
