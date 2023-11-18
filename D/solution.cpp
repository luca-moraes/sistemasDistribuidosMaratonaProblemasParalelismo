#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1000000007; //since the answer may grow a lot, we use the modulus


int main() {
	int n,m;
	cin >> n >> m;
	vector<vector<bool> >  blockedCells(n, vector<bool>(n,false));
	for(int c =0;c<m;c++) {
		int i,j;
		cin >> i >> j;
		blockedCells[i][j] = true;		
	}

	vector<vector<int> > dp(2,vector<int>(n,0));

	if(!blockedCells[0][0])
		dp[0][0] = 1;

	for(int j=1;j<n;j++) if(!blockedCells[0][j]) dp[0][j] = dp[0][j-1];
	dp[1][n-1] = dp[0][n-1];

	for(int i=1;i<n;i++) {
		for(int j=0;j<n;j++) {
			int ans = 0;
			if(!blockedCells[i][j]) {				
				ans = dp[0][j];
				if(j!=0) ans += dp[1][j-1];
			}

			dp[1][j] = ans% MOD;
		}
		for(int j=0;j<n;j++) dp[0][j] = dp[1][j];
	}

	
	cout << dp[1][n-1] << endl;
}