#include<iostream>
#include<vector>

using namespace std;

string reverse(string &s)
{
  string str = "";
  int size = s.size();
  for(int i=0;i<size;++i)
    {
      str += s[size - 1 - i];
    }
  return str;
}

int main()
{
  int n;
  vector<int> work;
  vector<string> strings;
  int x;
  string str;

  cin >> n;
  for(int i=0;i<n;++i)
    {
      cin >> x;
      work.push_back(x);
    }
  for(int i=0;i<n;++i)
    {
      cin >> str;
      strings.push_back(str);
    }

  pair<long long,long long>  work_required;
  string prev_rev, rev;
  work_required = make_pair(0,work[0]);
  //cout << work_required.first << " " << work_required.second << endl;
  long long a,b;
  for(int i=1;i<n;++i)
    {
      prev_rev = reverse(strings[i-1]);
      rev = reverse(strings[i]);

      //cout << "prev_rev= " << prev_rev << endl;
      //cout << "rev= " << rev << endl;

      //if already lexi sorted
      a = -1;
      if(work_required.first != -1)
	{
	  if(strings[i-1] <= strings[i])
	    {
	      a = work_required.first;
	    }
	}
      if(work_required.second != -1)
	{
	  if(prev_rev <= strings[i])
	    {       
	      if(a != -1)
		{
		  a = min(a, work_required.second);
		}
	      else
		{
		  a = work_required.second;
		}
	    }
	}
      b = -1;
      //if reverse of string is sorted
      if(work_required.first != -1)
	{
	  if(strings[i-1] <= rev)
	    {
	      b = work_required.first + work[i];
	    }
	}
      if(work_required.second != -1)
	{
	  if(prev_rev <= rev)
	    {
	      if(b != -1)
		{
		  b = min(b, work_required.second + work[i]);
		}
	      else
		{
		  b = work_required.second + work[i];
		}
	    }
	}
      if(a == -1 && b == -1)
	{
	  cout << -1 << endl;
	  return 0;
	}
      else
	{
	  //cout << "a= " << a << endl;
	  //cout << "b= " << b << endl;
	  work_required.first = a;
	  work_required.second = b;
	}
    }

  if(work_required.first == -1)
    {
      cout << work_required.second << endl;
    }
  else if(work_required.second == -1)
    {
      cout << work_required.first << endl;
    }
  else
    {
      cout <<  min(work_required.first, work_required.second) << endl;
    }
}
