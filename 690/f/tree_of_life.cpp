#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<unordered_map>
#include<list>
#include<sstream>
using namespace std;

#define MAX_V 110
#define DEBUG 0

bool list_comp(list<int> l1, list<int> l2)
{
  for(list<int>::iterator it1 = l1.begin(), it2 =  l2.begin();
      it1 != l1.end() && it2 != l2.end(); it1++, it2++)
    {     
      if(*(it1) != *(it2) )
	{
	  return *(it1) < *(it2);
	}
    }
  return false;
}

class Forest
{
public:
  int vsize; //number of vertices in this tree
  vector<int> v[MAX_V]; //adjs of the vertices
  int d[MAX_V]; //degree counts of tree vertices

  //parse the forest into rooted trees that are gravity centered
  //this can potenitally result in a bicentered tree
  vector<pair<int, int> > roots;

  int parents[MAX_V];
  vector<int> sons[MAX_V];
  //for finding tree roots
  int weights[MAX_V];
  int visited[MAX_V];

  //allow temporary marking of vertices deleted
  bool deleted[MAX_V];
  int num_deleted;

  Forest() {Forest(MAX_V-1);}

  //Forest with at most n vertices
  Forest(int n) 
  {
    vsize = 0; num_deleted = 0;
    for(int i=1; i<=n; i++){d[i] = 0; deleted[i] = false;}
  }

  void markDeleted(int node)
  {
    if(!deleted[node]) deleted[node] = true; vsize--; num_deleted++;
  }
  
  void markUndeleted(int node)
  {
    if(deleted[node]) deleted[node] = false; vsize++; num_deleted--;
  }

  int weightTree(int root)
  {
    visited[root] = true;
    int weight = 0, node;
    for(int i=0; i<v[root].size(); i++)
      {
	node = v[root][i];
	if( !visited[node] && !deleted[node])
	  {
	    weight += weightTree(node);
	  }
      }
    weights[root] = weight + 1;
    return weights[root];
  }

  void shift(int root, int new_root)
  {
    weights[root] -= weights[new_root];
    weights[new_root] += weights[root];
  }

  pair<int,int> findGravityRoot(int root)
  {
    int curr = root, adj;
    int weight = weightTree(root);
    bool done = false;
    while(!done)
      {
	done = true;
	for(int i=0; i<v[curr].size(); i++)
	  {
	    adj = v[curr][i];
	    if(deleted[adj]) continue;

	    //two centroids of the tree
	    if(weights[adj] == weight/2)
	      {
		return make_pair(curr, adj);
	      }
	    //move towards the centroid
	    if(weights[adj] > weight/2)
	      {
		done = false;
		shift(curr, adj);
		curr = adj;
		break;
	      }
	  }
      }
    //only one center
    return make_pair(curr, 0);
  }

  void labelParentSons(int root)
  {
    for(int i=1; i<=vsize+num_deleted; i++)
      {
	visited[i] = false;
      }
    labelParentSonsHelp(root);
  }

  void labelParentSonsHelp(int root)
  {
    sons[root].clear();
    visited[root] = true;
    int node;
    for(int i=0; i<v[root].size(); i++)
      {
	node = v[root][i];
	if(!visited[node] && !deleted[node])
	  {
	    sons[root].push_back(node);	  
	    parents[node] = root;
	    labelParentSonsHelp(node);
	  }
      }
  }
  void findTreeRoots()
  {
    roots.clear();
    for(int i=1; i<=vsize+num_deleted; i++)
      {
	visited[i] = false;
      }
    pair<int,int> root;
    for(int i=1; i<=vsize+num_deleted; i++)
      {
	if(!visited[i] && !deleted[i])
	  {
	    root = findGravityRoot(i);
	    roots.push_back(root);
	  }
      }
  }

  void rootTreeIso(list<int> * rep)
  {
    vector<list<int> > sub_lists;
    
    for(int i=0; i<roots.size(); i++)
      {
	list<int> new_list;
	sub_lists.push_back(new_list);

	//single centered tree
	if(roots[i].second == 0)
	  {
	    labelParentSons(roots[i].first);
	    rootTreeIsoHelp(roots[i].first, &sub_lists[i]);
	  }
	//bi-centered tree
	else
	  {
	    vector<list<int> > centers;
	    centers.resize(2);
	    labelParentSons(roots[i].first);
	    rootTreeIsoHelp(roots[i].first, &centers[0]);

	    labelParentSons(roots[i].second);
	    rootTreeIsoHelp(roots[i].second, &centers[1]);

	    spliceSubLists(centers, &sub_lists[i]);
	  }
      }
    
    spliceSubLists(sub_lists, rep);
    rep->push_front(roots.size());
    
  }
  void rootTreeIsoHelp(int root, list<int> * rep)
  {
    int size = sons[root].size();
    if(size == 0){rep->push_front(0); return; } //leaf node
    
    vector<list<int> > sub_lists;
    for(int i=0; i<size; i++)
      {
	list<int> new_list;
	sub_lists.push_back(new_list);
	rootTreeIsoHelp(sons[root][i], &sub_lists[i]);
      }
    spliceSubLists(sub_lists, rep);
    rep->push_front(size);
  }

  void spliceSubLists(vector<list<int> > &sub_lists, list<int> * sort_combine)
  {
    sort(sub_lists.begin(), sub_lists.end(), list_comp);
    int size = sub_lists.size();
    for(int i=0; i<size; i++)
      {
	sort_combine->splice(sort_combine->end(), sub_lists[i]);
      }
  }

  void convertListToString(list<int> & l, string & s)
  {
    stringstream ss;
    for(list<int>::iterator it = l.begin(); it != l.end(); it++)
      {
	if(it == l.begin())
	  {
	    ss << *(it);
	  }
	else
	  {
	    ss << "," << *(it);
	  }
      }
    s = ss.str();
  }

  void forestIsoHash(string & s)
  {
    findTreeRoots();

    list<int> rep;
    rootTreeIso(&rep);

    //remove 0s in front- unconnected components
    list<int>::iterator begin, it;
    int c = 0;
    begin = rep.begin(); it = begin; it++;
    while(it != rep.end() && *(it) == 0) {c++; it = rep.erase(it);}
    *(begin) -= c;

    //convert this representation of the forest to a string
    convertListToString(rep,s);

    if(DEBUG) cout << s << endl;
  }

  void parseForest(int numEdges)
  {
    int x,y;
    unordered_map<int,int> vmap;
    int label = 1;
    for(int i=1; i<=numEdges; i++)
    {
      cin >> x >> y;
      if(vmap[x] == 0){vmap[x] = label; label++;}
      if(vmap[y] == 0){vmap[y] = label; label++;}
      x = vmap[x];
      y = vmap[y];
      addEdge(x,y);
    }
  }

  void addEdge(int x, int y)
  {
    //add (x,y) to adj
    if(v[x].size() == 0){vsize++;}
    if(v[y].size() == 0){vsize++;}
    v[x].push_back(y);
    v[y].push_back(x);
    //add to the degrees
    d[x]++; d[y]++;
  }

  void removePrevEdge(int x, int y)
  {
    v[x].pop_back();
    v[y].pop_back();
    if(v[x].size() == 0){vsize--;}
    if(v[y].size() == 0){vsize--;}
    // remove from the degrees
    d[x]--; d[y]--;
  }
  
  void printRootedTree(int root)
  {
    labelParentSons(root);
    printRootedTreeHelp(root);
  }
  void printRootedTreeHelp(int root)
  {
    int adj;
    for(int i=0; i<sons[root].size(); i++)
      {
	adj = sons[root][i];
	cout << root << " " << adj << endl;
	printRootedTreeHelp(adj);
      }
  }
};

int find2P(int start, Forest &t)
{
  int next;
  int count = 0;
  for(int i=0; i<t.v[start].size(); i++)
    {
      next = t.v[start][i];
      count += t.v[next].size() - 1;
    }
  return count;
}

void solveEasy()
{
  int n,ans = 0;
  cin >> n;
  Forest t1(n);
  t1.parseForest(n-1);
  for(int i=1; i<=n; i++)
    {
      ans += find2P(i, t1);
    }
  cout << ans/2 << endl;
}

void freeMemory(vector<Forest * > & trees)
{
  while(trees.size())
    {      
      delete trees[trees.size() -1 ];
      trees.pop_back();
    }
}

void solveMedium(vector<Forest *> & trees)
{
  int n,k;
  cin >> n  >> k;
  if(DEBUG) cout << "N is " << n << " K is " << k << endl;
  int m;
  int totalDegree = 0;
  int index = -1; //index of a tree with n-1 vertices
  string s;
  unordered_map<string, int> hm, hmcmp;
  for(int i=0; i<n; i++)
    {
      cin >> m;
      trees.push_back(new Forest(n));
      trees[i]->parseForest(m);
      if(DEBUG) {cout << "vsize: " << trees[i]->vsize << " roots: " << trees[i]->roots.size() << " "; }
      trees[i]->forestIsoHash(s);
      hm[s]++;
      //find a single rooted tree with n-1 vertices
      if(trees[i]->vsize == n-1 && trees[i]->roots.size() == 1){index = i;}
      totalDegree += (n-m-1);
    }
  if(DEBUG) cout << "index: " << index << endl;
  if(DEBUG) cout << "totalDegree: " << totalDegree << endl;
  
  if(n == 2) {if(trees[0]->roots.size() != 0 || trees[1]->roots.size() != 0){cout << "NO" << endl;} else{cout << "YES" << "\n" << "1 2" << endl;} return;}

  //if there is no Forest with exactly n-1 vertices -> impossible
  //underlying tree must have one vertex with degree 1
  if(index == -1){cout << "NO" << endl; return;}
  
  //if sum of degrees is not = 2*e or 2*n-1 then there cannot be an underlying tree
  if(totalDegree != 2*(n-1)){cout << "NO" << endl; return;}

  //brute force
  //try adding a new vertex to the Tree found with n-1 vertices
  //with an edge to one of the n-1 vertices
  //and then check if each Forest formed by removing one vertex
  //from this new tree corresponds to exactly one of the inputs
  
  Forest * t = trees[index];
  if(DEBUG) cout << "initial T: " << endl; t->forestIsoHash(s);
  int nv;

  //add a vertex-nth one is empty
  nv = n;

  bool found;
  for(int i=1; i<=n-1; i++)
    {
      //add an edge from this vertex to the ith vertex
      t->addEdge(nv,i);
      if(DEBUG){ cout << "after adding to " << i << ": "; t->forestIsoHash(s);}
      found = true;
      for(int j=1; j<=n; j++)
	{
	  t->markDeleted(j);
	  t->forestIsoHash(s);
	  t->markUndeleted(j);
	  int x = ++hmcmp[s]; if(hm[s] < x) {found = false; break;}
	}
      if(found)
	{
	  cout << "YES" << endl;
	  t->printRootedTree(t->roots[0].first);
	  return;
	}
      t->removePrevEdge(nv,i);
      if(DEBUG) {cout << "after remove " << i << ": "; t->forestIsoHash(s);}
      hmcmp.clear();
    }
  cout << "NO" << endl;
}


int main()
{
  int z, n, k;
  vector<Forest * > trees;
  cin >> z;;
  for(int i=0; i<z; i++)
    {
      solveMedium(trees);
      freeMemory(trees);
    }
}
