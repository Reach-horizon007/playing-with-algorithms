/**
 * 
 * 
 * 

https://codeforces.com/gym/449346/problem/E

E. Bottles

time limit per test 2 seconds
memory limit per test 512 megabytes
inputstandard input
outputstandard output
Nick has n bottles of soda left after his birthday. Each bottle is described by two values: remaining amount of soda ai and bottle volume bi (ai ≤ bi).

Nick has decided to pour all remaining soda into minimal number of bottles, moreover he has to do it as soon as possible. Nick spends x seconds to pour x units of soda from one bottle to another.

Nick asks you to help him to determine k — the minimal number of bottles to store all remaining soda and t — the minimal time to pour soda into k bottles. A bottle can't store more soda than its volume. All remaining soda should be saved.

Input
The first line contains positive integer n (1 ≤ n ≤ 100) — the number of bottles.

The second line contains n positive integers a1, a2, ..., an (1 ≤ ai ≤ 100), where ai is the amount of soda remaining in the i-th bottle.

The third line contains n positive integers b1, b2, ..., bn (1 ≤ bi ≤ 100), where bi is the volume of the i-th bottle.

It is guaranteed that ai ≤ bi for any i.

Output
The only line should contain two integers k and t, where k is the minimal number of bottles that can store all the soda and t is the minimal time to pour the soda into k bottles.

Input
4
3 3 4 3
4 7 6 5

Output
2 6

---------

Input 

2
1 1
100 100


Output

1 1

 * 
 * 
*/


#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using vvvi = vector<vvi>;
using vl = vector<ll>;
using vvl = vector<vl>;
using vb = vector<bool>;
using vvb = vector<vb>;
using vc = vector<char>;
using vvc = vector<vc>;
#define fast ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define pb push_back
void setIO()
{
	fast;
	#ifndef ONLINE_JUDGE
	freopen("input1.txt","r",stdin);
	freopen("output1.txt","w",stdout);
	#endif
}
bool cmp(vi&f,vi&s)
{
	return f[1] > s[1];//in decreasing order of their capacities
}
int main()
{
	setIO();
	int n;
	cin>>n;
	
	vvi a(n + 1,vi(2));

	vi rem(n + 1),cap(n + 1);
	int S = 0,res = 0;

	for (int i = 1;i<=n;i++){cin>>a[i][0];S += a[i][0];}
	for (int i = 1;i<=n;i++){cin>>a[i][1];res += a[i][1];}
	
	vvi dp(n + 1,vi(res + 1,-1));//2D DP table of size n + 1 by res + 1 (corresponding to j and k in the 3D DP state)
	 
	//Part 1 Begins
	sort(a.begin() + 1,a.end(),cmp);

	for (int i = 1;i<=n;i++)rem[i] = a[i][0],cap[i] = a[i][1];

	int cnt = 0,runningSum = 0;//cnt is k
	for (int i = 1;i<=n;i++){
		runningSum += a[i][1];
		if (runningSum >= S){
			cnt = i;//k = i then break
			break;
		}
	}
	
	//Part 1 Ends

	//We found the min # of bottles using the greedy above
	//Now dp[i][j][k] is the max sum of remaining soda if we choose j bottles
	//from the first i bottles with sum of capacities >= k

	dp[0][0] = 0;//Base case : dp[i][0][0] = 0 for all i

	for (int i = 1;i<=n;i++){

		for (int j = cnt;j>=1;j--){//this order matters because we are overwriting dp[i - 1][j][k] with dp[i][j][k]
		
		
			for (int k = cap[i];k<=res;k++){//this order doesnt matter, adhish has done in oppsite order and has explained this wrong
				if (dp[j - 1][k - cap[i]] != -1){//dp[i - 1][j - 1][k - cap[i]] is not invalid
					//By invalid I mean j bottles can be taken with sum of capacities >= k
					dp[j][k] = max(dp[j][k],dp[j - 1][k - cap[i]] + rem[i]);
				}
		
			}
		}
	}
	int mx = 0;
	int k = cnt;

	for (int i = S;i<= res;i++)// i is the sum of capacities (i loops over all valid sum of capacities)
		mx = max(mx,dp[k][i]);//-1 is invalid and is < 0 hence mx will never contain an invalid possibility

	cout<<k<<" "<<S - mx;
	return 0;
}