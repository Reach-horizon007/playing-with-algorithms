



// @link: https://codeforces.com/problemset/problem/1083/A





#include <iostream>
#include <bits/stdc++.h>
#include <cmath>
using namespace std;


int n;
vector<pair<int,long long int>> adj[300005];
long long int w[300005];
long long int dp[300005][2]; // 0 included 1-> not
long long int col;


bool isleaf(int node)
{
	if(node!=1 && adj[node].size()==1) return true;
	return false;
}


void dfs(int node,int par)
{	

	if(isleaf(node))
	{	
		dp[node][0] = w[node];
		dp[node][1] = 0;
		return;
	}

	for(pair<int,long long int> child : adj[node])
		if(child.first !=par)
			dfs(child.first,node);

	long long int ans  = 0;
	long long int ans2 = 0;
	vector<long long int> mol;
	for(pair<int,long long int> child : adj[node])
	{
		if(child.first !=par)
		{
			ans = max(ans,dp[child.first][0] + w[node] - child.second);
			long long int temp = max(dp[child.first][0],dp[child.first][1]);
			ans2 = max(ans2,temp);
			mol.push_back(dp[child.first][0] - child.second);
		}
	}
	sort(mol.begin(),mol.end());
	int sz = mol.size();
	if(sz > 1) col = max(col,mol[sz-1]+mol[sz-2]+w[node]);
	dp[node][0] = max(ans,w[node]);
	dp[node][1] = ans2;
	return;

}

int main()
{	
	#ifndef ONLINE_JUDGE
	freopen("input1.txt", "r", stdin);
	freopen("output1.txt", "w", stdout);
	#endif


	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>w[i];
		adj[i].clear();
		dp[i][0] = 0;
		dp[i][1] = 0;
	}
	for(int i=1;i<n;i++)
	{
		int a,b;
		long long int c;
		cin>>a>>b>>c;
		adj[a].push_back({b,c});
		adj[b].push_back({a,c});
	}
	col = 0;
	if(n==1) cout<<w[1];
	else {
		dfs(1,-1);
		long long int push = max(dp[1][0],dp[1][1]);
		cout<<max(push,col);
	}




}