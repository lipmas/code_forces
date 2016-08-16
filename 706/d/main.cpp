#include<iostream>

using namespace std;

class Node
{
public:

  Node(): p(NULL), left(NULL), right(NULL), value(0), count(0) {}

  Node(Node * parent, bool isLeftPath)
  {
    //set parent and left/right pointers
    p = parent;
    left = NULL;
    right = NULL;
    
    //calculate value of this new node
    value = (p->value) << 1;
    if(isLeftPath)
      {
	value += 1;
      }

    //new node so count is 1
    count = 1;
  }
  Node * p; //parent
  Node * left; //corresponds to 1
  Node * right; //corresponds to 0
  
  unsigned int value; // value corresponding to this node
  unsigned int count; //number of nodes below this node in the tree

};

void insertValue(Node * root, unsigned int val)
{
  Node * curr = root;
  curr->count++;

  unsigned int temp;
  //for each of the values 32 bits
  for(int i=0;i<32;++i)
    {
      temp = val >> (31 - i);

      //go to left
      if(temp % 2 == 1)
	{
	  if(curr->left == NULL)
	    {
	      curr->left = new Node(curr, true);
	      curr = curr->left;
	    }
	  else
	    {
	      curr = curr->left;
	      curr->count++;
	    }
	}
      //go to right
      else
	{
	  if(curr->right == NULL)
	    {
	      curr->right = new Node(curr, false);
	      curr = curr->right;
	    }
	  else
	    {
	      curr = curr->right;
	      curr->count++;
	    }
	}
    }
}

void deleteNode(Node * n)
{
  if(n->left != NULL)
    {
      deleteNode(n->left);
    }
  if(n->right != NULL)
    {
      deleteNode(n->right);
    }
  
  delete n;
}

//will be at least one value in the tree
void removeValue(Node * root, unsigned int val)
{
  Node * curr = root;
  curr->count--;

  unsigned int temp;
  //for each of the values 32 bits
  for(int i=0;i<32;++i)
    {
      temp = val >> (31 - i);

      //go to left
      if(temp % 2 == 1)
	{	  
	  //if this subtree only has one node destroy it
	  if(curr->left->count == 1)
	    {
	      deleteNode(curr->left);
	      curr->left = NULL;
	      return;
	    }
	  //otherwise continue down this path
	  else
	    {
	      curr = curr->left;
	      curr->count--;
	    }
	}
      //go to right
      else
	{
	  //if this subtree only has one node destroy it
	  if(curr->right->count == 1)
	    {
	      deleteNode(curr->right);
	      curr->right = NULL;
	      return;
	    }
	  //otherwise continue down this path
	  else
	    {
	      curr = curr->right;
	      curr->count--;
	    }
	}
    }
}

unsigned int queryValue(Node * root, unsigned int value)
{
  Node * curr = root;
  unsigned int temp;
  if(curr->count < 1)
    {
      return value;
    }

  //for each of the values 32 bits
  for(int i=0;i<32;++i)
    {
      temp = value >> (31 - i);
      
      //if most significant bit so far is 1 try to recurse down right path
      if(temp % 2 == 1)
	{
	  if(curr->right != NULL)
	    {
	      curr = curr->right;
	    }
	  else
	    {
	      curr = curr->left;
	    }
	}
      //if most significant bit so far is 0 try to recurse down left path
      if(temp % 2 == 0)
	{
	  if(curr->left != NULL)
	    {
	      curr = curr->left;
	    }
	  else
	    {
	      curr = curr->right;
	    }
	}
    }
  //at lead node in tree with max XOR value..return it
  return value ^ curr->value;
}


int main()
{
  Node * root = new Node();
  insertValue(root, 0);

  int q;
  char type;
  unsigned int max, value;

  cin >> q;
  for(int i=0;i<q;++i)
    {
      cin >> type >> value;
      if(type == '+')
	{
	  insertValue(root, value);
	}
      else if(type == '-')
	{
	  removeValue(root, value);
	}
      else if(type == '?')
	{
	  max = queryValue(root, value);
	  cout << max << endl;
	}
      else
	{
	  cout << "error" << endl;
	}
    }
}
