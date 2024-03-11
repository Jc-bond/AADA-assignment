#include <iostream>
#include <vector>

using namespace std;

vector<int> naiveStringMatching(const string& text, const string& pattern) {
    vector<int> occurrences;
    int n = text.length();
    int m = pattern.length();

    for (int i = 0; i <= n - m; ++i) {
        bool match = true;
        for (int j = 0; j < m; ++j) {
            if (text[i + j] != pattern[j]) {
                match = false;
                break;
            }
        }

        if (match) {
            occurrences.push_back(i);
        }
    }

    return occurrences;
}

int main() {
    string text = "abracadabra";
    string pattern = "brac";

    vector<int> result = naiveStringMatching(text, pattern);

    if (!result.empty()) {
        cout << "Pattern found at positions: ";
        for (int pos : result) {
            cout << pos << " ";
        }
        cout << endl;
    } else {
        cout << "Pattern not found in the text." << endl;
    }

    return 0;
}
