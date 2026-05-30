#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int ASIZE = 256;

// Tiền xử lý bảng bad character của Boyer-Moore
void preBmBc(const string &pattern, vector<int> &bmBc) {
    int m = pattern.size();

    // Gán mặc định mọi giá trị bằng độ dài pattern
    bmBc.assign(ASIZE, m);

    // Tính khoảng dịch cho từng ký tự
    for (int i = 0; i < m - 1; i++) {
        bmBc[(unsigned char)pattern[i]] = m - i - 1;
    }
}

// Thuật toán Raita
void raita(const string &pattern, const string &text) {
    int m = pattern.size();
    int n = text.size();

    vector<int> bmBc;

    // Tiền xử lý bảng bad character
    preBmBc(pattern, bmBc);

    // Lấy các ký tự đặc biệt để kiểm tra nhanh
    char firstCh = pattern[0];
    char middleCh = pattern[m / 2];
    char lastCh = pattern[m - 1];

    int j = 0;

    // Bắt đầu tìm kiếm
    while (j <= n - m) {

        // Lấy ký tự cuối của cửa sổ hiện tại
        char c = text[j + m - 1];

        // Kiểm tra nhanh ký tự đầu, giữa, cuối
        if (lastCh == c &&
            middleCh == text[j + m / 2] &&
            firstCh == text[j]) {

            // So sánh phần còn lại của pattern
            if (text.substr(j + 1, m - 2) ==
                pattern.substr(1, m - 2)) {

                cout << "Tim thay tai vi tri: " << j << endl;
            }
        }

        // Dịch chuyển theo bảng bad character
        j += bmBc[(unsigned char)c];
    }
}

int main() {
    string text, pattern;

    cin >> pattern >> text;

    // Gọi thuật toán Raita
    raita(pattern, text);

    return 0;
}