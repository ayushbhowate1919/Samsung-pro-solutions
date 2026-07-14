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
void solve()
{
    int n ; 
    cin>>n ; 
    
    vector<string> vst ; 

    for(int i = 0 ; i <n ; i++){
         string s ; 
         cin>>s ; 

         vst.push_back(s);
    }

    vector<vector<int>> dp(10 , vector<int>(10 , -1e8)) ; 

    for(auto& s : vst){
         int len = s.size();
         int x = s.[0] - '0';
         int y = s.back() - '0';
         
         vector<vector<int>> ndp = dp ; 
         
         // starting new chain here ; 
         ndp[x][y] = max(ndp[x][y] , len);

         // else extend the older chain ; 

         for(int i = 0 ; i <10 ; i++){
            if(dp[i][x]!=-1e8)  
            ndp[i][y] = max(ndp[i][y] , dp[i][x] + len);
         }

         dp = ndp ; 
    }

   
    int ans = 0 ; 

    for(int i = 0 ; i <10 ; i++){
       ans = max(ans , dp[i][i]);
    }

    cout<<ans<<"\n";
    
}
 
int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    solve();
    return 0;
}