#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int ASIZE = 256;

// Tiền xử lý bảng bad character
void preBmBc(const string &pattern, vector<int> &bmBc) {
    int m = pattern.size();

    // Gán mặc định mọi giá trị bằng độ dài pattern
    bmBc.assign(ASIZE, m);

    // Tính khoảng dịch cho từng ký tự
    for (int i = 0; i < m - 1; i++) {
        bmBc[(unsigned char)pattern[i]] = m - i - 1;
    }
}

// Thuật toán Tuned Boyer-Moore
void tunedBoyerMoore(const string &pattern, const string &text) {
    int m = pattern.size();
    int n = text.size();

    vector<int> bmBc;

    // Tiền xử lý bảng bad character
    preBmBc(pattern, bmBc);

    // Lấy giá trị dịch của ký tự cuối
    int shift = bmBc[(unsigned char)pattern[m - 1]];

    // Đặt ký tự cuối có giá trị dịch bằng 0
    bmBc[(unsigned char)pattern[m - 1]] = 0;

    // Tạo chuỗi phụ để tránh truy cập vượt biên
    string tempText = text + string(m, pattern[m - 1]);

    int j = 0;

    // Bắt đầu tìm kiếm
    while (j < n) {

        // Lấy khoảng dịch theo ký tự cuối hiện tại
        int k = bmBc[(unsigned char)tempText[j + m - 1]];

        // Dịch nhanh nhiều lần liên tiếp
        while (k != 0) {
            j += k;
            k = bmBc[(unsigned char)tempText[j + m - 1]];

            j += k;
            k = bmBc[(unsigned char)tempText[j + m - 1]];

            j += k;
            k = bmBc[(unsigned char)tempText[j + m - 1]];
        }

        // So sánh m - 1 ký tự đầu
        if (tempText.substr(j, m - 1) == pattern.substr(0, m - 1) && j < n) {
            cout << "Tim thay tai vi tri: " << j << endl;
        }

        // Dịch theo shift
        j += shift;
    }
}

int main() {
    string text, pattern;

    cin >> pattern >> text;

    tunedBoyerMoore(pattern, text);

    return 0;
}