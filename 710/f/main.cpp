#include<iostream>
#include<string>
#include<queue>
#include<unordered_map>

#define DEBUG 0
#define MAX_CH 26
#define INF 1000000
using namespace std;

typedef long long ll;
typedef unordered_map<string, int> StringCount;


StringCount hash_map;

class TrieNode
{
public:
  //members
  char ch;
  int num;  //number of strings ending at this node
  int count; //number of strings below this subtree
  TrieNode * adj[MAX_CH];
  TrieNode(char let)
  {
    ch = let;
    count = 0;
    num = 0;
    for(int i=0; i<MAX_CH; i++)
      {
	adj[i] = NULL;
      }
  }
};

void deleteSubtree(TrieNode * root)
{
  for(int i=0; i<MAX_CH; i++)
    {
      if(root->adj[i] != NULL)
	{
	  deleteSubtree(root->adj[i]);
	}
    }
  delete root;
}
void insertString(TrieNode * root, string &s)
{
  if(DEBUG) cout << "inserting string " << s << endl;
  TrieNode * curr = root;
  curr->count++;
  for(int i=0; i<s.size(); i++)
    {
      char let = s[i];
      int size_left = s.size() - 1 - i;
      int index = let-97;
      if(curr->adj[index] == NULL)
	{
	  TrieNode * new_node = new TrieNode(let);
	  curr->adj[index] = new_node;
	  curr = new_node;
	}
      else
	{
	  curr = curr->adj[index];
	}
      curr->count++;
    }
  curr->num++;
}

void deleteString(TrieNode * root, string &s)
{
  if(DEBUG) cout << "deleting string: " << s << endl;
  TrieNode * curr = root;
  curr->count--;
  for(int i=0; i<s.size(); i++)
    {
      char let = s[i];
      int index = let-97;
      if(curr->adj[index]->count == 1 )
	{
	  deleteSubtree(curr->adj[index]);
	  curr->adj[index] = NULL;
	  break;
	}
      else
	{
	  curr = curr->adj[index];
	}
      curr->count--;
      if(i == s.size() -1)
	{
	  curr->num--;
	}
    }
}

void printTree(TrieNode * root, int &level)
{
  //cout << "printing tree at root node: " << root->ch << endl;
  int max_level = 0;
  int prev_level;
  for(int i=0; i<MAX_CH; i++)
    {
      prev_level = level;
      if(root->adj[i] != NULL)
	{
	  printTree(root->adj[i],level);
	  if(level > max_level) max_level = level;
	  level = prev_level;
	}
    }
  for(int i=0; i<max_level; i++)
    {
      cout << "\t";
    }
  cout << root->ch  << "(" << root->count
       << "," << root->num << ")" << endl;
  level = max_level + 1;
}

ll findSubstringMatches(TrieNode * root, string & s)
{
  ll matches = 0;
  queue<TrieNode *> q;
  TrieNode * curr;
  int index;
  for(int i=0; i<s.size(); i++)
    {
      index = s[i]-97;
      int qsize = q.size();
      if(DEBUG)
	{
	  if(i%1000 == 0) 
	    {
	      cout << "iteration: " << i << endl;
	      cout << "queue size is: " << qsize << endl;
	    }
	}
      for(int i=0; i<qsize; i++)
	{
	  curr = q.front();
	  q.pop();
	  if(curr->adj[index] != NULL)
	    {
	      curr = curr->adj[index];
	      matches += curr->num;
	      q.push(curr);
	    }
	}
      if(root->adj[index] != NULL) 
	{
	  curr = root->adj[index];
	  matches += curr->num;
	  q.push(curr);
	}
    }
  return matches;
}

int main()
{
  int q, type;
  string s;
  TrieNode * root = new TrieNode('-');

  cin >> q;
  for(int i=0; i<q; i++)
    {
      cin >> type;
      if(type == 1)
	{
	  cin >> s;
	  insertString(root,s);
	  hash_map[s]++;
	}
      if(type == 2)
	{
	  cin >> s;
	  deleteString(root,s);
	  hash_map[s]--;
	}
      if(type == 3)
	{
	  cin >> s;
	  ll ans = findSubstringMatches(root, s);
	  if(DEBUG) cout << "answer for " << s << " is: ";
	  cout << ans << endl;
	}
      int level = 0;
      if(DEBUG) printTree(root, level);
    }
}
