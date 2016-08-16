#include<iostream>

using namespace std;

int main()
{
  int n;
  cin >> n;

  string hate = "I hate";
  string love = "I love"; 
  for(int i=0;i<n;++i)
    {
      if(i % 2 == 0)
	{
	  cout << hate;
	}
      else
	{
	  cout << love;
	}

      if(i == n-1)
	{
	  cout << " it" << endl;
	}
      else
	{
	  cout << " that ";
	}
    }
}
