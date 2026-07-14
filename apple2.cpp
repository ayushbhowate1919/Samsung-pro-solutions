#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define vi vector<int>
#define vll vector<long long>
#define pb push_back
#define vvi vector<vector<int>>
#define all(x) x.begin(),x.end()
#define print(a) for(auto it : a) {  cout<<it<<" "; }  cout<<endl; 
#define yes()  cout << "YES" <<endl;
#define no() std::cout << "NO" <<endl;
/* Let's Win */

vector<int> dr = {0,1,0,-1};
vector<int> dc = {1,0,-1,0};
void solve()
{
    int n , m ; 
    cin>>n>>m ;
    
    vector<vector<int>> grid(n , vector<int>(m));
    
    int totapp = 0 ; 

    for(int i=0;i<n;i++){
       for(int j=0;j<m;j++){
          cin>>grid[i][j];

          if(grid[i][j] > 0)
          totapp++;
       }
    }

     int currcnt = 0 ; 

     if(grid[0][0] == 1)
     currcnt++;
   
      if(grid[0][0]==-1){
    cout<<-1<<"\n";
    return;
      } 

    // dp[r][c][cntapples][dir] ;

    vector<vector<vector<vector<int>>>> dp(n , vector<vector<vector<int>>>(m , 
      vector<vector<int>>(totapp+1 , vector<int>(4 , INT_MAX)))) ; 


    
    // min right turns to reach this state would be stored ; 
    
    //we would use deque ; 

    deque<vector<int>> dq ; 
    // {r , c , cntapples , dir}
    
    // 0 1 2 3 : for dir ; 
    dq.push_front({0 , 0 , currcnt , 0 });
    dp[0][0][currcnt][0] = 0;
    

    auto move = [&](int r , int c , int cntap , int dir , int dpold , int wt){

      int nr = r + dr[dir];
      int nc = c + dc[dir];

      if(nr>=0 && nr<n && nc>=0 && nc<m && grid[nr][nc]!=-1){
         int ncnt = cntap ;   
        if(grid[nr][nc] == cntap+1)
          ncnt++;

          if(dp[nr][nc][ncnt][dir]  > dpold + wt){
             dp[nr][nc][ncnt][dir] = dpold + wt ; 

             if(wt == 0){
              dq.push_front({nr , nc , ncnt , dir});
             }
             else{
               dq.push_back({nr , nc , ncnt , dir});
             }
          }


      }

    };


    while(!dq.empty()){
        vector<int> v = dq.front();
        int r = v[0] , c = v[1] , cntap = v[2] , dir = v[3];
        dq.pop_front();

        // now i have two move ; 

        // i)move in the same direction ; 
        move(r , c , cntap , dir ,dp[r][c][cntap][dir] , 0);

         // ii) take right turn and move in that direction ;
         
         move(r , c , cntap , (dir+1)%4 , dp[r][c][cntap][dir] , 1);
    }
    
    int ans = INT_MAX ; 

    for(int i=0;i<n;i++){
      for(int j=0;j<m;j++){
          for(int k = 0 ; k <4 ; k++){
             ans = min(ans , dp[i][j][totapp][k]) ; 
          }
      }
    }


   if(ans == INT_MAX)
   cout<<"-1"<<"\n";
   else
   cout<<ans<<"\n";
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int t;
    cin >> t;
    while(t--)
    {
        solve();
    }
    return 0;
}