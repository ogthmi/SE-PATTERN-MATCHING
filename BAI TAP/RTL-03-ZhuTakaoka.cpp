#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

const int ASIZE = 256;

// Tiền xử lý bảng dịch chuyển bad character
void preZtBc(const string &pattern, vector<vector<int>> &ztBc) {
    int m = pattern.size();

    for (int i = 0; i < ASIZE; ++i) {
        for (int j = 0; j < ASIZE; ++j) ztBc[i][j] = m;
    }

    // Gán giá trị cho mọi cặp ký tự có ký tự thứ 2 là pattern[0]
    for (int i = 0; i < ASIZE; ++i) ztBc[i][(unsigned char)pattern[0]] = m - 1;
    
    // Tính khoảng dịch cho từng cặp ký tự liên tiếp trong pattern
    for (int i = 1; i < m - 1; ++i) {
        ztBc[(unsigned char)pattern[i - 1]][(unsigned char)pattern[i]] = m - 1 - i;
    }
}

void suffixes(const string &x, vector<int> &suff) {
    int m = x.size();

    suff[m - 1] = m;

    int g = m - 1;
    int f = 0;

    for (int i = m - 2; i >= 0; --i) {

        if (i > g && suff[i + m - 1 - f] < i - g) suff[i] = suff[i + m - 1 - f];

        else {
            if (i < g) g = i;
            while (g >= 0 && x[g] == x[g + m - 1 - f]) --g;
            suff[i] = f - g;
        }
    }
}

// Tiền xử lý good suffix 
void preBmGs(const string &x, vector<int> &bmGs) {
    int m = x.size();

    vector<int> suff(m);

    suffixes(x, suff);

    for (int i = 0; i < m; ++i) bmGs[i] = m;

    int j = 0;

    for (int i = m - 1; i >= 0; --i) {
        if (suff[i] == i + 1) {
            for (; j < m - 1 - i; ++j) {
                if (bmGs[j] == m) bmGs[j] = m - 1 - i;
            }
        }
    }

    for (int i = 0; i <= m - 2; ++i) bmGs[m - 1 - suff[i]] = m - 1 - i;
}

// Thuật toán Zhu-Takaoka
void zhuTakaoka(const string &pattern, const string &text) {
    int m = pattern.size();
    int n = text.size();

    vector<vector<int>> ztBc(ASIZE, vector<int>(ASIZE));
    vector<int> bmGs(m);

    preZtBc(pattern, ztBc);
    preBmGs(pattern, bmGs);

    for (char i = 'a'; i < 'a' + m - 1; i++){
        for (char j = 'a'; j < 'a' + m - 1; j++) {
            cout << ztBc[(unsigned char)i][(unsigned char)j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    

    int j = 0;
    while (j <= n - m) {
        // So sánh từ cuối pattern
        int i = m - 1;

        // So khớp từ phải sang trái
        while (i >= 0 && pattern[i] == text[i + j])  --i;

        // Nếu i < 0 nghĩa là đã khớp hoàn toàn
        if (i < 0) {
            cout << "Match at position: " << j << endl;
            // Dịch theo good suffix
            j += bmGs[0];
        } else {
            // Bước dịch theo good suffix
            int shift1 = bmGs[i];
            // Bước dịch theo cặp 2 ký tự cuối cửa sổ hiện tại
            int shift2 = ztBc[(unsigned char)text[j + m - 2]][(unsigned char)text[j + m - 1]];

            j += max(shift1, shift2);
        }
    }
}

int main() {
    string text, pattern;

    cin >> pattern >> text;

    zhuTakaoka(pattern, text);

    return 0;
}