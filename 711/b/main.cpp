#include<iostream>
#include<utility>
using namespace std;
#define MAX 500
typedef long long LL;

int main()
{
  int n,x;
  int a[MAX][MAX];
  LL col[MAX], row[MAX], diag[2], sum=0, ans=-1;
  bool exists = true;
  pair<int,int> empty;
  cin >> n;
  if(n == 1){cout << 1 << endl; return 0;}
  for(int i=0; i<n; i++){
    col[i] = 0;
    row[i] = 0;
  }
  diag[0] = 0; diag[1]=0;
  for(int i=0; i<n; i++){
    for(int j=0; j<n; j++){
      cin >> x;
      if(x == 0){empty = make_pair(i,j);}
      if(i == j){diag[0] += x;}
      if(i == n-j-1){diag[1] += x;}
      row[i] += x;
      col[j] += x;
    }
  }
  sum = row[(empty.first + 1)%n]; 
  for(int i=0; i<n; i++){
    if(i == empty.first){continue;}
    if(row[i] != sum){exists = false; break;}
  }
  for(int i=0; i<n; i++){
    if(i == empty.second){continue;}
    if(col[i] != sum){exists = false; break;}
  }
  if(empty.first != empty.second){
    if(diag[0] != sum){exists = false;}
  }
  if(empty.first != n - 1 - empty.second){
    if(diag[1] != sum){exists = false; }
  }
  if(exists){
    if(sum - row[empty.first] == sum - col[empty.second]){
      ans = sum - row[empty.first];
    }
    if(empty.first == empty.second){
      if(sum - diag[0] != ans){ans = -1;}
    }
    if(empty.first == n - 1 - empty.second){
      if(sum - diag[1] != ans){ans = -1;}
    }
  }
  if(ans <= 0){ans = -1;}
  cout << ans << endl;
}
