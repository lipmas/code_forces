#include<iostream>
#include<stdio.h>
using namespace std;
#define EMPTY 'O'
#define FILLED 'X'
#define SIT '+'
int main()
{
  char ch1,ch2;
  int n;
  string s;
  bool found = false;
  cin >> n;
  getline(cin,s);
  s = "";
  for(int i=0; i<n; i++){
      for(int j=0; j<2; j++){
	  ch1 = getchar(); ch2 = getchar();
	  if(!found){
	      if(ch1 == EMPTY && ch2 == EMPTY){
		  found = true;
		  ch1 = SIT; ch2 = SIT;
		}
	    }
	  s += ch1; s+= ch2;
	  if(j == 0){ s += getchar();}
	}
      s += getchar();
    }
  if(found){
    cout << "YES" << endl;
    cout << s;
  }
  else{
    cout << "NO";
  }
}
