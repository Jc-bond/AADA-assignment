#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Function to find the length of LCS and reconstruct the LCS string
string findLCS(const string& s1, const string& s2) {
    int m = s1.length();
    int n = s2.length();

    // Create a 2D vector to store the lengths of LCS for all substrings
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    // Fill the dp table
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    // Find the length of LCS
    int lengthOfLCS = dp[m][n];

    // Reconstruct the LCS string
    string lcs;
    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (s1[i - 1] == s2[j - 1]) {
            lcs = s1[i - 1] + lcs;
            i--;
            j--;
        } else {
            if (dp[i - 1][j] > dp[i][j - 1]) {
                i--;
            } else {
                j--;
            }
        }
    }

    return lcs;
}

int main() {
    string s1 = "ABCBDAB";
    string s2 = "BDCAB";

    // Find the length of LCS and the LCS string
    string lcs = findLCS(s1, s2);
    int lengthOfLCS = lcs.length();

    // Print the length of LCS and the LCS itself
    cout << "Length of LCS: " << lengthOfLCS << endl;
    cout << "LCS: " << lcs << endl;

    return 0;
}
