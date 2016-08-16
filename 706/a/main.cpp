#include<iostream>
#include<algorithm>
#include<math.h>
using namespace std;

double x,y;

double timeToHouse(int xi, int yi, int vi)
{
  return sqrt(pow((x-xi),2) + pow((y-yi),2))/vi;
}
int main()
{
  int n;

  cin >> x >> y >> n;
  
  int xi, yi, vi;
  double time;
  cin >> xi >> yi >> vi;
  double min = timeToHouse(xi,yi,vi);
  for(int i=1;i<n;++i)
    {
      cin >> xi >> yi >> vi;
      time = timeToHouse(xi,yi,vi);
      if(time < min) {min = time;}
    }
  cout.precision(17);
  cout << fixed << min << endl;
}
