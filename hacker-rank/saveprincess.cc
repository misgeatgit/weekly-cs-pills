/**
 * Category             : Artificial intelligence
 * Challenge description: https://www.hackerrank.com/challenges/saveprincess
 * Author               : Misgana Bayetta <misgana.bayetta@gmail.com>
 */
#include <algorithm>
#include <iostream>
#include <cmath>
#include <string>
#include <set>
#include <vector>

using namespace std;

void display_path_to_princess(int n, vector <string> grid);

int main(int argc, char** args)
{
    int N;
    cin >> N;
    vector<string> grid;

    for(int i=0; i<N; i++) {
        string s;
        cin >> s;
        cout << s << "\n";
        grid.push_back(s);
    }

    display_path_to_princess(N,grid);

    return 0;
}

void display_path_to_princess(int n, vector <string> grid){
 // '-' cells
 // 'm' rescuer always at the center
 // 'p' princess stuck on of the four corners
 
  std::set<string> possible_corners = {grid[0],grid[n-1]};
  int px, py; //princess location
  
  bool top = true;
  for(const string& corner : possible_corners){
      if(corner[0] == 'p') 
      { px = 1;
          if(top) {
              py = 1;
              top = false;
          }
          else{
              py = n ;
          }
          break;
      } 
      else if(corner[n-1] == 'p')
      {  px=n;
          if(top) {
              py = 1;
              top = false;
          }
          else{
              py = n;
          }
      }
      break;
  }
  // my location.
  int mx = (n/2) + 1; 
  int my = mx; 

  // Do the math.
  string up = "UP", down = "DOWN", left = "LEFT", right = "RIGHT";

  int dist = (int) sqrt( pow(py-my,2) + pow(px-mx,2));

  cout << "px,py= " << px <<","<< py << "\n"; 
  cout << "mx,my= " << mx <<","<< my << "\n";
  cout << "distance " << dist <<"\n";
  string direction=""; return;
  if ( px - mx < 0 ){
      for(int i=0; i < dist; i++) direction += (left +"\n");
  }
  else{
      for(int i=0; i < dist; i++) direction += (right +"\n");
  }

  if ( py - my < 0 ){
      for(int i=0; i < dist; i++) direction += (up +"\n");
  }
  else{
      for(int i=0; i < dist; i++) direction += (down +"\n");
  }

  cout << direction;

}
