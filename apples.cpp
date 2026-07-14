#include <bits/stdc++.h>
using namespace std;

void solve(){
     int n , m ; 
     cin>>n>>m ; 
     
      // revise this question ; 

      
     vector<vector<int>> grid(n , vector<int>(m)) ; 
     int total = 0 ; 
     for(int i = 0 ; i <n ; i++){
         for(int j = 0 ; j <m ;j++){
              cin>>grid[i][j];
              
              if(grid[i][j] > 0)
              total++;
         }
     }
     
     // dp[row][col][cntapple][dir] ; 
     
     // miniimum turns taken to get to this state ; 
     // this is 0-1 BFS thus deque could be used to get the solution faster ; 
     // if we assume this as graph , then onlw weight possible is 0 or 1 ; 
     
     vector<vector<vector<vector<int>>>> dp(n , vector<vector<vector<int>>>(m ,
     vector<vector<int>>(total+1 , vector<int>(4 , INT_MAX))))
     
     
     vector<int> dr = {0,1,0,-1};
     vector<int> dc = {1,0,-1,0};


     dequeu<vector<int>> dq ;
     // r c cnt dir
     
     int apcnt = 0 ; 
     
     if(grid[0][0] == 1){
       apcnt++;    
     }
     
     dq.push({0,0,apcnt,0});
     dp[0][0][apcnt][0] = 0 ; 
     
     
     // u can access deque directly ; 
     // this dir , is the direction we are facing now ; 
     auto move = [&](int r , int c , int cntap , int dir , int dpold , int wt){
         int nr = r + dr[dir];
         int nc = c + dc[dir];
         
         if(!(nr>=0 && nr<n && nc>=0 && nc<m && grid[nr][nc]!=-1))
         return; 
         
         int ncnt = cntap ; 
         
         if(grid[nr][nc] == cntap+1)
         ncnt++;
         
         if(dp[nr][nc][ncnt][dir] > dpold){
              dp[nr][nc][ncnt][dir] = dpold ; 
              
               // add into deqeue according to the wt ; 
               
               if(wt == 0){
                    dq.push_front({nr , nc , ncnt , dir});
               }
               else{
                    dq.push_back({nr , nc , ncnt , dir});
               }
              
         }
     };
     
     while(!dq.empty()){
          vector<int> v = dq.front();
          int r = v[0] , c = v[1] , cntap = v[2] , dir = v[3] ; 
          dq.pop_front();
          
          // now im on this state , 
          // i can either go forward if possible 
          // or i can change direction and go ahead ; 
          
          // we need a move function , use lambda function ; 
          move(r , c , cntap , dir , dp[r][c][cntap][dir] , 0 );
          move(r , c , cntap , (dir+1)%4 , dp[r][c][cntap][dir]+1 , 1) ;
     }     
     
     // to get ans ; 
     int ans = INT_MAX ; 
     
     for(int i = 0 ; i <n ; i++){
          for(int j = 0 ; j <m ; j++){
               for(int d = 0 ; d<4 ; d++){
                    ans = min(ans , dp[i][j][total][d]) ; 
               }
          }
     }
     
     if(ans == INT_MAX)
     cout<<"-1"<<"\n";
     else{
         cout<<ans<<"\n";
     }
     
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
