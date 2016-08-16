#include<iostream>

using namespace std;

bool cycleFirstPlayerWin(int n)
{
  if(n % 2 == 0)
    {
      return true;
    }
  else
    {
      return false;
    }
}

void outputFormat(bool win)
{
  if(win)
    {
      cout << 1 << endl;
    }
  else
    {
      cout << 2 << endl;
    }
}

int main()
{
  int n,x;
  cin >> n;

  bool firstPlayerWin;
  cin >> x;
  firstPlayerWin = cycleFirstPlayerWin(x);
  outputFormat(firstPlayerWin);

  for(int i=1;i<n;i++)
    {
      cin >> x;
      firstPlayerWin = firstPlayerWin^cycleFirstPlayerWin(x);
      outputFormat(firstPlayerWin);
    }

}
