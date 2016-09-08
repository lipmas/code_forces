#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include<time.h>
#include<stdlib.h>

using namespace std;

typedef vector<pair<int,int> > EdgeSet; 

void createRandomTree(int n, EdgeSet &edges)
{
  srand(time(NULL));
  vector<int> connected, unconnected;
  for(int i=1; i<=n; i++)
    {
      unconnected.push_back(i);
    }

  //choose first node 
  unsigned int index = rand() % n;
  connected.push_back(unconnected[index]);
  unconnected.erase(unconnected.begin() + index);
  int x, y;
  for(int i=0; i<n-1; i++)
    {
      x = rand() % connected.size();
      y = rand() % unconnected.size();
      edges.push_back(make_pair(connected[x],unconnected[y]));
      connected.push_back(unconnected[y]);
      unconnected.erase(unconnected.begin() + y);
    }
  
}

void createRandomTreeInput(int n, string & output)
{
  stringstream size;
  size << n << " " << n << endl;
  output += size.str();
  EdgeSet edges;
  createRandomTree(n, edges);
  int first, second;
  int count;
  //create the input where the ith vertex has been deleted
  for(int i=1; i<=n; i++)
    {
      stringstream ss, c;      
      count = 0;
      for(int j=0; j<n-1; j++)
	{
	  first = edges[j].first;
	  second = edges[j].second;	 
	  if(first == i || second == i) continue;
	  ss << (first + i)%n << " " << (second + i)%n << endl;
	  count++;
	}
      c << count << endl;
      output += c.str() + ss.str();
    }
}
void createOneConnectedNode(int t, int n, string & output)
{
  stringstream ss;
  ss << t << endl;

  for(int tt=0; tt<t; tt++)
    {
      ss << n << " " << n << endl;
      ss << 0 << endl;
      for(int i=1;i<=n-1;i++)
	{
	  ss << n-2 << endl;
	  for(int j=2;j<=n-1;j++)
	    {
	      ss << 1 << " " << j << endl;
	    }
	}
      
    }
  output = ss.str();
}



void writeToFile(string & output)
{
  static int i = 1;
  ofstream out; 
  stringstream ss;
  ss << "output" << i << ".txt";
  out.open(ss.str().c_str());
  out << output;
  i++;
}

int main(int argc, char * argv[])
{ 
  int t = 1;
  int n = 10;
  t = atoi(argv[1]);
  n = atoi(argv[2]);
  stringstream ss;
  ss << t << endl;
  string output = ss.str();
  for(int i=0;i<t;i++)
    {
      createRandomTreeInput(n, output);
    }
  writeToFile(output);
}

