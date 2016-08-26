#include<iostream>
#include<sstream>
#include<stdio.h>
#include <assert.h> 

#define fastio ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
 
using namespace std;

const int MAX_ROW(1000);
const int MAX_COL(1000);

class Cell
{
public:
  Cell() : value(0), down(NULL), right(NULL) {}

  int value; //value of the cell
  
  //Cell * left;
  Cell * right;
  //Cell * up;
  Cell * down;

  /*
  void print()
  {
    cout << "value: " << value << endl;
    cout << "right:" << right << endl;
    cout << "down:" << down << endl;
  }
  */
};

//hack to print intgers to console faster
//rather than converting to strings
inline void print_int(int val)
{
   char chars[10];   // Max int = 2147483647
   int digits = 0;
   if (val < 0)
   {
      putchar('-');
      val = -val;
   }

   do
   {
      chars[digits++] = ((val % 10) + 0x30);
      val /= 10;
   }while (val && digits < 10);

   while (digits>0)
   {
      putchar(chars[--digits]);
   }
}

void printMatrix(Cell * root, int n, int m)
{
  stringstream ss;
  Cell * curr = root;
  Cell * next;
  int i =0, j = 0;

  for(int i=0;i<n;++i)
    {
      next = curr->down;
      for(int j=0;j<m;++j)
	{
	  if(j != 0)
	    {
	      ss << " ";
	    }
	  ss << curr->value;
	  curr = curr->right;
	}
      ss << "\n";
      curr = next;
    }
  cout << ss.str() << endl;
}

void printMatrix2(Cell * root, int n, int m)
{
  //stringstream ss;
  Cell * curr = root;
  Cell * next;
  int i =0, j = 0;

  for(int i=0;i<n;++i)
    {
      next = curr->down;
      for(int j=0;j<m;++j)
	{
	  //curr->print();
	  if(j != 0)
	    {
	      putchar(' ');
	      //ss << " ";
	    }
	  //ss << curr->value;
	  print_int(curr->value);
	  curr = curr->right;
	}
      putchar('\n');
      //ss << "\n";
      curr = next;
    }
  //cout << ss.str() << endl;
}

Cell * spliceSubMatrices2(Cell * root, int a, int b, int c, int d, int l, int w)
{
  Cell * sub1 = root;
  Cell * sub2 = root;
  Cell * tmp; //temp ptr used for swapping
  Cell * sub1l;
  Cell * sub1u;
  Cell * sub2l;
  Cell * sub2u;
  Cell * sub1s;
  Cell * sub2s;
  Cell * sub1r;
  Cell * sub1d;
  Cell * sub2r;
  Cell * sub2d;
  Cell * curr1;
  Cell * curr2;

  //find 1 before start of submatrix 1
  for(int i=0;i<a-1;++i)
    {
      sub1 = sub1->down;
    }
  for(int j=0;j<b-1;++j)
    {
      sub1 = sub1->right;
    }
  //find 1 before start of submatrix 2
  for(int i=0;i<c-1;++i)
    {
      sub2 = sub2->down;
    }
  for(int j=0;j<d-1;++j)
    {
      sub2 = sub2->right;
    }

  sub1s = sub1;
  sub2s = sub2;
  sub1l = sub1;
  sub1u = sub1;
  sub2l = sub2;
  sub2u = sub2;
  
  if(a != 0)
    {
      sub1s = sub1s->down;
      sub1l = sub1l->down;
    }
  if(b != 0)
    {
      sub1s = sub1s->right;
      sub1u = sub1u->right;
    }
  if(c != 0)
    {
      sub2s = sub2s->down;
      sub2l = sub2l->down;
    }
  if(d != 0)
    {
      sub2s = sub2s->right;
      sub2u = sub2u->right;
    }
  //remember new root
  if(a == 0 && b == 0)
    {
      root = sub2s;
    }
  
  if(a == 0)
    {
      curr2 = sub2s;
      for(int i=0;i<w;++i)
	{
	   if(i != w-1)
	     {
	       curr2 = curr2->right;
	     }
	}
      sub2r = curr2;
    }
  else
    {
      curr1 = sub1u;
      curr2 = sub2s;
      for(int i=0;i<w;++i)
	{
	  curr1->down = curr2;
	   if(i != w-1)
	     {
	       curr1 = curr1->right;
	       curr2 = curr2->right;
	     }
	}
      sub2r = curr2;
    }
  if(b == 0)
    {
      curr2 = sub2s;
      for(int i=0;i<l;++i)
	{
	   if(i != l-1)
	     {
	       curr2 = curr2->down;
	     }
	}
      sub2d = curr2;
    }
  else
    {
      curr1 = sub1l;
      curr2 = sub2s;
      for(int i=0;i<l;++i)
	{
	  curr1->right = curr2;
	   if(i != l-1)
	     {
	       curr1 = curr1->down;
	       curr2 = curr2->down;
	     }
	}
      sub2d = curr2;
    }
   //remember new root
  if(c == 0 && d == 0)
    {
      root = sub1s;
    }
  if(c == 0)
    {
      curr2 = sub1s;
      for(int i=0;i<w;++i)
	{
	  if(i != w-1)
	    {
	      curr2 = curr2->right;
	    }
	}
      sub1r = curr2;
    }
  else
    {
      curr1 = sub2u;
      curr2 = sub1s;
      for(int i=0;i<w;++i)
	{
	  curr1->down = curr2;
	   if(i != w-1)
	     {
	       curr1 = curr1->right;
	       curr2 = curr2->right;
	     }
	}
      sub1r = curr2;
    }
  if(d == 0)
    {
      curr2 = sub1s;
      for(int i=0;i<l;++i)
	{
	   if(i != l-1)
	     {
	       curr2 = curr2->down;
	     }
	}
      sub1d = curr2;
    }
  else
    {
      curr1 = sub2l;
      curr2 = sub1s;
      for(int i=0;i<l;++i)
	{
	  curr1->right = curr2;
	   if(i != l-1)
	     {
	       curr1 = curr1->down;
	       curr2 = curr2->down;
	     }
	}
      sub1d = curr2;
    }
  curr1 = sub1d;
  curr2 = sub2d;
  for(int i=0;i<w;++i)
    {
      tmp = curr1->down;
      curr1->down = curr2->down;
      curr2->down = tmp;

      curr1 = curr1->right;
      curr2 = curr2->right;
    }
  curr1 = sub1r;
  curr2 = sub2r;

  for(int i=0;i<l;++i)
    {
      tmp = curr1->right;
      curr1->right = curr2->right;
      curr2->right = tmp;
     
      curr1 = curr1->down;
      curr2 = curr2->down;
    } 
  return root;
}

/*
//switches 2 submatrices in the matrix
//returns new root
Cell * spliceSubMatrices(Cell * root, int a, int b, int c, int d, int l, int w)
{
  Cell * sub1 = root;
  Cell * sub2 = root;
  Cell * tmp; //temp ptr used for swapping

  //find start of submatrix 1
  for(int i=0;i<a;++i)
    {
      sub1 = sub1->down;
    }
  for(int j=0;j<b;++j)
    {
      sub1 = sub1->right;
    }
  //find start of submatrix 2
  for(int i=0;i<c;++i)
    {
      sub2 = sub2->down;
    }
  for(int j=0;j<d;++j)
    {
      sub2 = sub2->right;
    }
  //remember new root
  if(a == 0 && b == 0)
    {
      root = sub2;
    }
  else if(c == 0 && d == 0)
    {
      root = sub1;
    }
  //follow along perimeter of both submatrices and change pointers
  //exchange left perimeter
  for(int i=0;i<l;++i)
    {
      tmp = sub1->left;
      if(sub2->left != NULL)
	{
	  sub2->left->right = sub1;
	}

      if(tmp != NULL)
	{
	  tmp->right = sub2;
	}

      sub1->left = sub2->left;
      sub2->left = tmp;

      //move to next node down
      if(i != l-1)
	{
	  sub1 = sub1->down;
	  sub2 = sub2->down;
	}
    }
  //exchange bottom perimeter
  for(int i=0;i<w;++i)
    {
      tmp = sub1->down;

      if(sub2->down != NULL)
	{
	  sub2->down->up = sub1;
	}
      if(tmp != NULL)
	{
	  tmp->up = sub2;
	}

      sub1->down = sub2->down;
      sub2->down = tmp;

      //move to next node to the right
      if(i != w-1)
	{
	  sub1 = sub1->right;
	  sub2 = sub2->right;
	}

    }
  //exchange right perimeter
  for(int i=0;i<l;++i)
    {
      tmp = sub1->right;

      if(sub2->right != NULL)
	{
	  sub2->right->left = sub1;
	}
      if(tmp != NULL)
	{
	  tmp->left = sub2;
	}

      sub1->right = sub2->right;
      sub2->right = tmp;

      //move to next node up
      if(i != l-1)
	{
	  sub1 = sub1->up;
	  sub2 = sub2->up;
	}
    }
  //exchange top perimeter
  for(int i=0;i<w;++i)
    {
      tmp = sub1->up;

      if(sub2->up != NULL)
	{
	  sub2->up->down = sub1;
	}
      if(tmp != NULL)
	{
	  tmp->down = sub2;
	}
      
      sub1->up = sub2->up;
      sub2->up = tmp;

      //move to the next node to the left
      if(i != w-1)
	{
	  sub1 = sub1->left;
	  sub2 = sub2->left;
	}
    }	  
  return root;
}
*/

int main()
{
  fastio;
  //create a large buffer for printing to stdout
  int err;
  int BigBuf = 16*1024*1024;

  char* outbuf = new char[BigBuf]; 
  assert (outbuf != NULL); 
  err = setvbuf (stdout, outbuf, _IOFBF, BigBuf); // full line buffering 
  assert (err == 0);

  int n, m, q;
  int value;

  //Cell  matrix[MAX_ROW][MAX_COL];

  cin >> n >> m >> q;


  Cell ** matrix = new Cell *[n];  
  //read in all values for cells
  for(int i=0;i<n;++i)
    {
      matrix[i] = new Cell[m];
      /*
      for(int j=0;j<m;++j)
	{
	  Cell * cell = new Cell();
	  matrix[i][j] = cell;
	}
      */
    }

  //initialize adjacent pointers
  for(int i=0;i<n;++i)
    {
      for(int j=0;j<m;++j)
	{
	  cin >> value;
	  Cell * cell = &matrix[i][j];
	  cell->value = value;
	  /*
	  if(i == 0)
	    {
	      cell->up = NULL;
	    }
	  else
	    {
	      cell->up = matrix[i-1][j];
	    }
	  */
	  if(i == n-1)
	    {
	      cell->down = NULL;
	    }
	  else
	    {
	      cell->down = &matrix[i+1][j];
	    }
	  /*
	  if(j == 0)
	    {
	      cell->left = NULL;
	    }
	  else
	    {
	      cell->left = matrix[i][j-1];
	    }
	  */
	  if(j == m-1)
	    {
	      cell->right = NULL;
	    }
	  else
	    {
	      cell->right = &matrix[i][j+1];
	    }
	}
    }

  Cell * root = &matrix[0][0];

  //printMatrix(root,n,m); cout << endl;

  //read queries
  int a,b,c,d,l,w;
  for(int i=0;i<q;++i)
    {
      cin >> a >> b >> c >> d >> l >> w;
      root = spliceSubMatrices2(root,a-1,b-1,c-1,d-1,l,w);      
      //printMatrix(root,n,m); cout << endl;
    }
  printMatrix2(root,n,m);
}
