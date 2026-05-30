#include <bits/stdc++.h>
using namespace std;

const int ASIZE = 256;

// Tiền xử lý bảng bad character
void preBmBc(const string &pattern, vector<int> &bmBc) {
    int m = pattern.size();
    bmBc.assign(ASIZE, m);

    for (int i = 0; i < m - 1; i++) {
        bmBc[(unsigned char)pattern[i]] = m - i - 1;
    }
}

// Thuật toán Horspool
void horspool(const string &pattern, const string &text) {
    int m = pattern.size();
    int n = text.size();
    vector<int> bmBc;

    preBmBc(pattern, bmBc);

    int j = 0;

    while (j <= n - m) {
        //
        char c = text[j + m - 1];

        // So sánh ký tự cuối trước
        if (pattern[m - 1] == c && memcmp(pattern.c_str(), text.c_str() + j, m - 1) == 0) {
            cout << "Match at position: " << j << endl;
        }

        j += bmBc[(unsigned char)c];
    }
}

int main() {
    string pattern, text;

    cin >> pattern >> text;

    horspool(pattern, text);

    return 0;
}