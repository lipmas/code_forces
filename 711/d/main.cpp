#include<iostream>
using namespace std;
#define MAX 2000001
#define MOD 1000000007
typedef long long LL;

int n;
int a[MAX]; 
int visited[MAX];

LL effpow2(int n)
{
  if(n == 0){return 1;}
  LL ans = effpow2(n/2);
  ans = (ans*ans)%MOD;
  if(n&1){ans=(ans*2)%MOD;}
  return ans;
}

LL pow2(int n)
{
  LL ans = 1;
  for(int i=0; i<n; i++)
    {
      ans = (ans*2)%MOD;
    }
  return ans;
}

LL cycle(int n)
{
  return (effpow2(n) - 2 + MOD)%MOD;
}

LL dfs(int curr, int depth)
{
  //cout << "dfs visiting " << curr << endl;
  if(visited[curr] == 0)
    {
      //found a cycle
      int len = 1;
      int next = a[curr];
      while(next != curr){next = a[next]; len++;} 
      int rem = depth - len - 1;
      LL ans = effpow2(rem);
      //cout << "found a cycle of length: " << len << " has value " << cycle(len) << endl;
      //cout << "rem is: " << rem << " has value: " << pow2(rem) <<  endl;
      ans = (ans * cycle(len))%MOD;
      return ans;
    }
  visited[curr] = 0;
  if(visited[a[curr]] == 1)
    {
      //found an already dfs'd component
      //cout << "found a path to removed section: " << depth << endl;
      visited[curr] = 1;
      return effpow2(depth);
    }
  LL ans = dfs(a[curr], depth+1);
  visited[curr] = 1;
  return ans;
}


int main()
{
  cin >> n;
  for(int i=1; i<=n; i++)
    {
      cin >> a[i];
      visited[i] = -1;
    }
  LL ans = 1;
  for(int i=1; i<=n; i++)
    {
      if(visited[i] == -1)
	{
	  ans  = ans*dfs(i, 1)%MOD;
	}
    }
  cout << ans << endl;
}
