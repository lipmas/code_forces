#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

typedef vector<int>::iterator IT;

int findMin(vector<int> & prices, int m)
{
  int beg = 0;
  int end = prices.size()-1;
  int mid;
  while(beg < end)
    {
      mid = (beg + end)/2;
      if(prices[mid] > m)
	{
	  end = mid-1;
	}
      else
	{
	  beg = mid+1;
	}
    }
  mid = (beg + end)/2 ;
  if(prices[mid] > m)
    {
      return mid-1;
    }
  else
    {
      return mid;
    }
}
int main()
{
  int n;
  cin >> n;
  
  int p,q,m;
  vector<int> prices;
  for(int i=0;i<n;++i)
    {
      cin >> p;
      prices.push_back(p);
    }
  sort(prices.begin(), prices.end());

  cin >> q;
  int min;
  for(int i=0;i<q;++i)
    {
      cin >> m;
      min = findMin(prices, m);
      cout << min + 1 << endl;
    }
}
