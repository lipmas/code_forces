#include<iostream>
#include<algorithm>
#include<cmath>

using namespace std;

long long gcd(long long a, long long b)
{
  if(a % b == 0) return b;
  return gcd(b,a%b);
}

long long lcm(long long a, long long b)
{
  return (a*b)/gcd(max(a,b), min(a,b));
}

long long findFirstintersection(long long l, long long r, long long a1, long long b1, long long a2, long long b2)
{
  long long f1 = b1;
  long long f2 = b2;
  double incr;
  if(f1 < l)
    {
      incr = (l-f1)/(double)a1;
      f1 += a1*ceil(incr);
    }
  if(f2 < l)
    {
      incr = (l-f2)/(double)a2;
      f2 += a2*ceil(incr);
    }
  
  while(f1 != f2 && f1 <= r && f2 <= r)
    {      
      if(f1 < f2)
	{
	  incr = (f2-f1)/(double)a1;
	  f1 += a1*ceil(incr);
	}
      else
	{
	  incr = (f1-f2)/(double)a2;
	  f2 += a2*ceil(incr);
	}
    }
  return max(f1,f2);
}

int main()
{
  long long a1,a2,b1,b2,l,r;
  cin >> a1 >> b1 >> a2 >> b2 >> l >> r;
  
  if( abs(b2-b1) % gcd(max(a1,a2), min(a1,a2)) != 0) 
    {
      cout << 0 << endl;
      return 0;
    }
  long long x0 = findFirstintersection(l, r,  a1, b1, a2, b2);
  //cout << x0 << endl;
  if(x0 > r)
    {
      cout << 0 << endl;
    }
  else
    {
      long long answer = (r-x0)/lcm(a1,a2);	
      cout << answer+1 << endl;

    }
}
