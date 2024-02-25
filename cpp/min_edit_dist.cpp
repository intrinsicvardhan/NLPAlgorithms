//implementing min edit distance levenshtein
#include <iostream>
#include <vector> 
#include <algorithm>
using namespace std;
//
vector<vector<int>> returnDPTable(string word1, string word2) {
    int m = word1.size();
    int n = word2.size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    //initialize the dp table 
    //d[i,0] = i and d[0,j] = j 
    for(int i = 0; i<=m; i++) {
        dp[i][0] = i;
    }
    for(int j = 0; j<=n; j++) {
        dp[0][j] = j;
    }
    for (int i = 1; i <= m; ++i) {
        for(int j = 1; j<= n; ++j) {
            dp[i][j] = min(dp[i-1][j]+1, min(dp[i][j-1]+1, word1[i]==word2[j]?dp[i-1][j-1]:dp[i-1][j-1]+2));
        }
    }
    return dp;
}

vector<string> backtraceAlignment(vector<vector<int>> dp, string word1, string word2) {
    vector<string> result; 
    string w1 = "", w2 = ""; 
    int i = dp.size()-1; 
    int j = dp.size()-1; 
    while(i>0 && j>0) {
        //find which operation was performed by finding min of i-1,j-1, i-1,j, i,j-1
        int min_val = min(dp[i-1][j-1], min(dp[i-1][j], dp[i][j-1]));
        if(min_val == dp[i-1][j-1]) { //ptr going diagonal
            w1 = word1[i-1] + w1; 
            w2 = word2[j-1] + w2; 
            i--; 
            j--; 
        } else if(min_val == dp[i-1][j]) { //ptr going up
            w1 = word1[i-1] + w1; 
            w2 = "-" + w2; 
            i--; 
        } else { //ptr going left
            w1 = "-" + w1; 
            w2 = word2[j-1] + w2; 
            j--; 
        }
    }
    while(i>0) {
        w1 = word1[i-1] + w1; 
        w2 = "-" + w2; 
        i--; 
    }
    while(j>0) {
        w1 = "-" + w1; 
        w2 = word2[j-1] + w2; 
        j--; 
    }
    result.push_back(w1);
    result.push_back(w2);
    return result;

}

int returnMinDist(vector<vector<int>> dp) {
    return dp[dp.size() - 1][dp[0].size() - 1];
}

void printMinDistTable(vector<vector<int>> dp) {
    for(int i = 0; i < dp.size(); i++) {
        for(int j = 0; j < dp[0].size(); j++) {
            cout << dp[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    string word1 = "intention";
    string word2 = "execution";
    vector<vector<int>> dp = returnDPTable(word1, word2);
    cout << "Minimum Edit Distance: " << returnMinDist(dp) << endl; 
    cout<<"Following is the DP table: "<<endl;
    printMinDistTable(dp);
    vector<string> result = backtraceAlignment(dp, word1, word2);
    cout << "Alignment: " << endl;
    cout << result[0] << endl;
    cout << result[1] << endl;
    return 0;
}
