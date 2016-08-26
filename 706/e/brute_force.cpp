#include<iostream>

using namespace std;

const int MAX_ROW(1000);
const int MAX_COL(1000);


void swapSubMatrix(int matrix[MAX_ROW][MAX_COL], int a, int b, int c, int d, int l, int w)
{
  int tmp;
  for(int i=0, s1x= a, s2x=c;i<l;i++,s1x++,s2x++)
    {
      for(int j=0,s1y = b, s2y=d;j<w;j++,s1y++,s2y++)
	{
	  // cout << "(" << s1x << "," << s1y << ")" << endl;
	  // cout << "(" << s2x << "," << s2y << ")" << endl;
	  tmp = matrix[s1x][s1y];
	  matrix[s1x][s1y] = matrix[s2x][s2y];
	  matrix[s2x][s2y] = tmp;
	}
    }
}

void printMatrix(int matrix[MAX_ROW][MAX_COL], int n, int m)
{
  for(int i=0;i<n;++i)
    {
      for(int j=0;j<m;++j)
	{
	  if(j != 0)
	    {
	      cout << " ";
	    }
	  cout << matrix[i][j];
	}
      cout << endl;
    }
}

int main()
{
  int n, m, q;
  int matrix[MAX_ROW][MAX_COL];

  cin >> n >> m >> q;
  for(int i=0;i<n;++i)
    {
      for(int j=0;j<m;++j)
	{
	  cin >> matrix[i][j];
	}
    }
  //printMatrix(matrix,n,m);
  
  int a,b,c,d,l,w;
  for(int i=0;i<q;++i)
    {
      cin >> a >> b >> c >> d >> l >> w;
      swapSubMatrix(matrix,a-1,b-1,c-1,d-1,l,w);
    }
  printMatrix(matrix,n,m);

}
