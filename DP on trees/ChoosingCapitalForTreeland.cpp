



// @link : https://codeforces.com/gym/449239/problem/B


#include <iostream>
#include <bits/stdc++.h>
#include <cmath>
using namespace std;


int n;
vector<pair<int,int>> adj[200005];
int up[200005];
int down[200005];
int total_up;


bool isleaf(int node)
{
	if(node!=1 && adj[node].size()==1) return true;
	return false;
}


void dfs(int node,int par)
{	
	if(isleaf(node)) return;

	for(pair<int,int> child : adj[node] )
	{
		if(child.first != par)
		{
			if(child.second==1) down[child.first] = down[node] + 1;
			else down[child.first] = down[node];

			if(child.second==-1)
			{
				up[child.first] = up[node] + 1;
				total_up++;
			}
			else up[child.first] = up[node];
			dfs(child.first,node);
		}
	}
	return;
}

int main()
{	
	#ifndef ONLINE_JUDGE
	freopen("input1.txt", "r", stdin);
	freopen("output1.txt", "w", stdout);
	#endif


	cin>>n;
	for(int i=1;i<n;i++)
	{
		int a,b;
		cin>>a>>b;
		adj[a].push_back({b,1});
		adj[b].push_back({a,-1});
		up[i] = 0 , down[i] = 0;
	}
	total_up = 0 , up[n] = 0 , down[n] = 0;
	dfs(1,-1);
	vector<int>v;
	int ans = 200006;
	for(int i=1;i<=n;i++)
		ans = min(ans,down[i] - up[i] + total_up);
	cout<<ans<<endl;
	for(int i=1;i<=n;i++)
		if((down[i] + total_up - up[i]) == ans)
			cout<<i<<" ";

	
	


}