#include<iostream>
#include<vector>
#include<sstream>
#include<unordered_map>
#include<set>
#include <iterator>
#include<algorithm>

using namespace std; 

//classes
class Junction 
{
public:
  int id;
  vector<Junction *> adj;
  bool visited;
  Junction * prev;
  Junction(int id): id(id) {}
};

class suit
{
public:
  int id;
  int start_junction; 
  int start_time;
  int c; //speed
};

//typedefs
typedef unordered_map<string, vector<Junction * > > PathMap;
typedef pair<Junction *, Junction *> Edge;

//globals
vector<Junction *> junctions;

//functions
bool findPathHelp(Junction * curr, Junction * end)
{
  if(curr == end)
    {
      return true;
    }
  curr->visited = true;
  for(int i=0;i<curr->adj.size();++i)
    {
      Junction * next = curr->adj[i];
      if(!next->visited)
	{
	  next->prev = curr;
	  if(findPathHelp(next, end))
	    {
	      return true;
	    }
	}
    }
}

static void findPath(Junction * start, Junction * end, vector<Junction *> & path)
{
  //cache paths based on start/end points
  PathMap map;

  stringstream ss;
  ss << start->id << "|" << end->id;
  string key = ss.str();

  PathMap::iterator it = map.find(key);
  if(it != map.end())
    {
      //if already computed this path then return it
      path = it->second;
      return;
    } 
  else
    {
      for(int i=0;i<junctions.size();i++)
	{
	  junctions[i]->visited = false;
	  junctions[i]->prev = NULL;
	}

      //dfs to find path
      findPathHelp(start, end);

      //recover the path
      Junction * curr = end;
      while(curr->prev != NULL)
	{
	  path.push_back(curr);
	  curr = curr->prev;
	}
      //push back the start node
      path.push_back(curr);

      //store path in cache
      map[key] = path;
      return;
    }
}

bool comp(Junction * a, Junction * b)
{
  return a->id < b->id;
}

bool compEdge(Edge a, Edge b)
{
  if(comp(a.first, b.first))
    {
      return true;
    }
  else if(comp(b.first, a.first))
    {
      return false;
    }
  else
    {
      return comp(a.second, b.second);
    }
}

void printPath(vector<Junction *> p)
{
  for(int i=0;i<p.size();++i)
    {
      cout << p[i]->id << " ";
    }
  cout << endl;
}

void printEdges(vector<Edge> e)
{
  for(int i=0;i<e.size();++i)
    {
      cout << "(" << e[i].first << "," << e[i].second << ")" << endl;      
    }
}

void findIntersectionSet(vector<Junction *> & p1, vector<Junction *> & p2, vector<Edge> &intersection)
{
  set<Edge> s1, s2;

  //first compute the 2 edge sets
  Edge e;
  Junction * v1;
  Junction * v2;

  for(int i=0;i<p1.size()-1;++i)
    {
      s1.insert(make_pair(min(p1[i], p1[i-1]), max(p1[i], p1[i-1])));
    }
  for(int i=0;i<p2.size()-1;++i)
    {
      s2.insert(make_pair(min(p2[i], p2[i-1]), max(p2[i], p2[i-1])));
    }
  std::set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(),
			std::back_inserter(intersection),compEdge);
} 

int main()
{
  int n, m;

  cin >> n >> m;

  //create junctions
  for(int i=0;i<n;i++)
    {
      Junction * j = new Junction(i);
      junctions.push_back(j);     
    }

  printPath(junctions);
  
  int v1, v2;
  //add edges to junctions
  for(int i=0;i<n-1;i++)
    {
      cin >> v1 >> v2;
      cout << "adding edge (" << v1-1 << "," << v2-1 << ")" << endl;
      junctions[v1-1]->adj.push_back(junctions[v2-1]);
      junctions[v2-1]->adj.push_back(junctions[v1-1]);
    }

  vector<Junction *> p1;
  vector<Junction *> p2;
  vector<Edge> intersect;

  findPath(junctions[0], junctions[1], p1);
  findPath(junctions[1], junctions[2], p2);

  printPath(p1);
  printPath(p2);

  findIntersectionSet(p1,p2,intersect);
  
  printEdges(intersect);

}
