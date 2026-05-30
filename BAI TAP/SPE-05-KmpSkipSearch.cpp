#include <iostream>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

const int ASIZE = 256;

// Hàm tiền xử lý Morris-Pratt
vector<int> preMp(const string& pattern) {
    int m = pattern.length();
    vector<int> mpNext(m + 1);

    int i = 0, j = -1;
    mpNext[0] = -1;

    while (i < m) {
        while (j > -1 && pattern[i] != pattern[j])  j = mpNext[j];
        ++i; ++j;
        mpNext[i] = j;
    }
    return mpNext;
}

// Hàm tiền xử lý KMP Tagged Border
vector<int> preKmp(const string& pattern) {
    int m = pattern.length();
    vector<int> kmpNext(m + 1);

    int i = 0, j = -1;
    kmpNext[0] = -1;

    while (i < m) {
        while (j > -1 && pattern[i] != pattern[j]) j = kmpNext[j];
        ++i; ++j;
        // Nếu ký tự tiếp theo cũng giống nhau thì thừa kế border
        if (i < m && pattern[i] == pattern[j])  kmpNext[i] = kmpNext[j];
        else  kmpNext[i] = j;
    }
    return kmpNext;
}

// Hàm kiểm tra match bắt đầu từ start
int attempt(const string& text, const string& pattern, int start, int wall) {
    int m = pattern.length(), k = wall - start; // k là vị trí bắt đầu từ phần đã biết match
    while (k < m && pattern[k] == text[k + start])  ++k;
    return k;
}

void kmpSkipSearch(string pattern, string text) {
    int m = pattern.length(), n = text.length();

    vector<int> mpNext = preMp(pattern), kmpNext = preKmp(pattern);
    vector<int> list(m, -1), z(ASIZE, -1);

    for (int mp: mpNext) cout << mp << " ";
    cout << endl;

    for (int kmp: kmpNext) cout << kmp << " ";
    cout << endl;


    z[(unsigned char)pattern[0]] = 0;

    for (int i = 1; i < m; ++i) {
        list[i] = z[(unsigned char)pattern[i]];
        z[(unsigned char)pattern[i]] = i;
    }

    int wall = 0, per = m - kmpNext[m]; // per là period của pattern
    int i = -1, j = -1;

    // Tìm block đầu tiên có ký tự xuất hiện
    do j += m;
    while (j < n && z[(unsigned char)text[j]] < 0); // Tìm block đầu tiên có ký tự xuất hiện

    if (j >= n) return; // Không tìm thấy

    i = z[(unsigned char)text[j]]; // Vị trí ký tự trong pattern

    int start = j - i;
    while (start <= n - m) {
        if (start > wall) wall = start;

        int k = attempt(text, pattern, start, wall); // Thử match

        wall = start + k;

        if (k == m) {
            cout << "Match at position: " << start << endl;
            i -= per;
        }
        else i = list[i];

        // Nếu không còn candidate
        if (i < 0) {
            // Tìm block tiếp theo
            do j += m;
            while (j < n && z[(unsigned char) text[j]] < 0);

            if (j >= n) return; // Không còn block nào

            i = z[(unsigned char)text[j]];
        }

        // Vị trí bắt đầu theo KMP
        int kmpStart = start + k - kmpNext[k];

        k = kmpNext[k];
        start = j - i;

        // Đồng bộ Skip + KMP
        while (start < kmpStart || (kmpStart < start && start < wall)) {
            // Nếu start quá nhỏ
            if (start < kmpStart) {
                i = list[i];

                // Nếu hết candidate
                if (i < 0) {
                    // Tìm block tiếp theo
                    do j += m;
                    while (j < n && z[(unsigned char) text[j]] < 0);

                    if (j >= n) return; // Không còn block nào

                    i = z[(unsigned char) text[j]];
                }
                start = j - i;
            }
            // Nếu KMP cần tiến thêm
            else {
                kmpStart += (k - mpNext[k]);
                k = mpNext[k];
            }
        }
    }
}

int main() {
    string pattern, text;
    cin >> pattern >> text;

    kmpSkipSearch(pattern, text);

    return 0;
}