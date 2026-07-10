/*
================================================================================
PROBLEM: Count Points on Path Segments
================================================================================

DESCRIPTION:
------------
You are given a path on an infinite 2D lattice. The path consists of line 
segments parallel to either the X-axis or Y-axis. The path is defined by a 
sequence of turning points (vertices), where consecutive points are connected 
by straight line segments.

Additionally, you are given a set of N points. Your task is to find how many 
of these N points lie on the given path.

Note: A point is considered to be on the path if it lies on any of the line 
segments connecting consecutive turning points (including the endpoints).

INPUT FORMAT:
-------------
Line 1: Two space-separated integers N and M
  - N: Number of points to check
  - M: Number of turning points that define the path

Line 2: N space-separated integers representing X-coordinates of the N points
Line 3: N space-separated integers representing Y-coordinates of the N points
  - The i-th point has coordinates (X[i], Y[i])

Line 4: M space-separated integers representing X-coordinates of turning points
Line 5: M space-separated integers representing Y-coordinates of turning points
  - The path goes from turning point 0 → 1 → 2 → ... → (M-1)

OUTPUT FORMAT:
--------------
A single integer representing the count of points that lie on the path.

CONSTRAINTS:
------------
- All coordinates are integers
- Consecutive turning points share either the same X or same Y coordinate
  (ensuring segments are axis-parallel)

================================================================================
EXAMPLE 1:
================================================================================

Input:
3 3
1 2 5
3 5 5
1 1 2
1 5 5

Explanation:
- N = 3 points to check: (1,3), (2,5), (5,5)
- M = 3 turning points: (1,1), (1,5), (2,5)
- Path segments:
  * Segment 1: (1,1) to (1,5) - vertical line at x=1, y from 1 to 5
  * Segment 2: (1,5) to (2,5) - horizontal line at y=5, x from 1 to 2

Checking points:
- (1,3): Lies on segment 1 (x=1, y=3 is between y=1 and y=5) ✓
- (2,5): Lies on segment 2 (y=5, x=2 is between x=1 and x=2) ✓
- (5,5): Does not lie on any segment ✗

Output:
2

================================================================================
EXAMPLE 2:
================================================================================

Input:
4 4
2 4 6 8
3 3 3 3
1 1 6 6
1 5 5 8

Explanation:
- N = 4 points to check: (2,3), (4,3), (6,3), (8,3)
- M = 4 turning points: (1,1), (1,5), (6,5), (6,8)
- Path segments:
  * Segment 1: (1,1) to (1,5) - vertical line at x=1, y from 1 to 5
  * Segment 2: (1,5) to (6,5) - horizontal line at y=5, x from 1 to 6
  * Segment 3: (6,5) to (6,8) - vertical line at x=6, y from 5 to 8

Checking points:
- (2,3): Does not lie on any segment ✗
- (4,3): Does not lie on any segment ✗
- (6,3): Does not lie on any segment ✗
- (8,3): Does not lie on any segment ✗

Output:
0

================================================================================
EXAMPLE 3:
================================================================================

Input:
5 2
3 5 7 9 10
4 4 4 4 4
3 10
4 4

Explanation:
- N = 5 points to check: (3,4), (5,4), (7,4), (9,4), (10,4)
- M = 2 turning points: (3,4), (10,4)
- Path segments:
  * Segment 1: (3,4) to (10,4) - horizontal line at y=4, x from 3 to 10

Checking points:
- (3,4): Lies on segment (endpoint) ✓
- (5,4): Lies on segment (y=4, x=5 is between x=3 and x=10) ✓
- (7,4): Lies on segment (y=4, x=7 is between x=3 and x=10) ✓
- (9,4): Lies on segment (y=4, x=9 is between x=3 and x=10) ✓
- (10,4): Lies on segment (endpoint) ✓

Output:
5

================================================================================
*/
#include<bits/stdc++.h>
using namespace std ;

void solve(){
     int n , m ; 
     cin>>n>>m ; 
 
      map<int , vector<int>> mpx , mpy ; 

     vector<int> px(n) , py(n);
     for(int i = 0 ; i <n ; i++){
         cin>>px[i];
     }

     for(int i = 0 ; i <n ; i++){
         cin>>py[i];
     }

     
     vector<int> pax(m) , pay(m) ; 
     for(int i = 0 ; i <m ; i++){
         cin>>pax[i];
     }

     for(int i = 0 ; i <m ; i++){
         cin>>pay[i];
     }


     for(int i = 0 ; i <n ; i++){
            mpx[px[i]].push_back(py[i]);
            mpy[py[i]].push_back(px[i]);
       }

       for(auto& it: mpx){
          vector<int>& vec = it.second ; 
          sort(vec.begin() , vec.end());
       }

       for(auto& it: mpy){
          vector<int>& vec = it.second ; 
          sort(vec.begin() , vec.end());
       }



     int cnt = 0 ; 

     // assuming the paths given is parallel to x and y
     // otherwise its still easy to calc those lines from given points ;
     
     for(int i = 0 ; i <m-1; i++){
          
         // searching for [pay[i] , pay[i+1])
          if(pax[i] == pax[i+1]){
            auto itl =  lower_bound(mpx[pax[i]].begin() , mpx[pax[i]].end() ,pay[i]);
            auto itr =  upper_bound(mpx[pax[i]].begin() , mpx[pax[i]].end() ,pay[i+1]);
             
             int curr = max(0 , (int)(itr - itl));
              cnt+=curr;

              cout<<curr<<" "<<pax[i]<<" "<<pay[i]<<" "<<"xsame"<<"\n";
         } 
          else{
            // pay[i] == pay[i+1]
            auto itl =  lower_bound(mpy[pay[i]].begin() , mpy[pay[i]].end() ,pax[i]);
            auto itr =  upper_bound(mpy[pay[i]].begin() , mpy[pay[i]].end() ,pax[i+1]);
             
             int curr = max(0 , (int)(itr - itl));
              cnt+=curr;

              cout<<curr<<" "<<pax[i]<<" "<<pay[i]<<" "<<"ysame"<<"\n";
          }  
        
     }

     cout<<cnt<<"\n";


}
int main(){
   
    solve();
    return 0 ; 
}