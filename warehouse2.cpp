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
  int h , w , c ; 
  cin>>h>>w>>c ; 
  
  vector<vector<int>> grid(n , vector<int>(m));

  for(int i=0;i<h;i++){
     for(int i=0;i<w;i++){
          cin>>grid[i][j]; 
     }
  }

  // this would be a dp question ; 

  // dp[r][c][bitmask][d]
  
    
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