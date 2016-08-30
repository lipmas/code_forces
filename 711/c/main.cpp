#include<iostream>
#include<vector>
#include<limits>
#define INF std::numeric_limits<long long>::max() - 1000000000- 1
#define MAX 100 + 1

using namespace std;
typedef long long LL;

int main()
{
  int n,m,k;
  int  p[MAX][MAX];
  int c[MAX];
  LL min[MAX][MAX][MAX];
  
  cin >> n >> m >> k;
  for(int i=1; i<=n; i++){
    cin >> c[i];
  }
  for(int i=1; i<=n; i++){
    for(int j=1; j<=m; j++){
      cin >> p[i][j];
    }
  }

  //initialize
  for(int i=1; i<=n; i++){
    for(int j=1; j<=m; j++){
      min[i][j][0] = INF;
    }
  }
  for(int kk=2; kk<=k; kk++){
    for(int i=1; i<k; i++){
      for(int j=1; j<=m; j++){
	min[i][j][kk] = INF;
      }
    }
  }
  for(int j=1; j<=m; j++){
    min[1][j][1] = (c[1] == 0 ? p[1][j] : (c[1] == j ? 0 : INF));
  }

  //recurrence
  for(int kk=1; kk<=k; kk++){
    for(int i=2; i<=n; i++){
      for(int j=1; j<=m; j++){
	if(c[i] != 0 && c[i] != j) {
	  min[i][j][kk] = INF;
	}
	else if(c[i] != 0 && c[i] == j) {
	  LL min_value = INF;
	  LL cost;
	  for(int j2=1; j2<=m; j2++){
	    if(c[i] != j2){ cost = min[i-1][j2][kk-1];}
	    else {cost = min[i-1][j2][kk];}
	    if(cost < min_value){min_value = cost;}
	  }
	  min[i][j][kk] = min_value;
	}
	else{
	  LL min_value = INF;
	  for(int j2=1; j2<=m; j2++){
	    LL cost;
	    if(j2 != j){
	      cost = min[i-1][j2][kk-1] + p[i][j];
	    }
	    else{
	      cost = min[i-1][j2][kk] + p[i][j];
	    }
	    if(cost < min_value){min_value = cost;} 
	  }
	  min[i][j][kk] = min_value;
	}
      }
    }
  }
  /*
  for(int kk=0; kk<=k; kk++){
    for(int i=1; i<=n; i++){
      for(int j=1; j<=m; j++){
	cout << "(" << i << "," << j << "," << kk << ") = " << min[i][j][kk] << endl;
      }
    }
  }
  */
  LL min_ans = INF;
  for(int c=1; c<=m; c++){
    if(min[n][c][k] < min_ans){min_ans = min[n][c][k];}
  }
  if(min_ans == INF) {cout << -1 << endl;}
  else{cout << min_ans << endl;}
}

/*
opt(n, m, k) = min cost of coloring the nth tree color m with k total paritions

opt(n,m,k) = min: { opt(n-1,!m,k-1) + p(n,!m) , opt(n-1,m,k) + p(n,m) }

opt(0,m,0) = 0

*/
