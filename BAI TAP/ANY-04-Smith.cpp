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

// Tiền xử lý bảng Quick Search
void preQsBc(const string &pattern, vector<int> &qsBc) {
    int m = pattern.size();

    // Gán mặc định m + 1 cho mọi ký tự
    qsBc.assign(ASIZE, m + 1);

    // Tính khoảng dịch cho từng ký tự
    for (int i = 0; i < m; i++) {
        qsBc[(unsigned char)pattern[i]] = m - i;
    }
}

// Thuật toán Smith
void SMITH(const string &pattern, const string &text) {
    int m = pattern.size();
    int n = text.size();

    vector<int> bmBc, qsBc;

    // Tiền xử lý hai bảng dịch chuyển
    preBmBc(pattern, bmBc);
    preQsBc(pattern, qsBc);

    int j = 0;

    // Bắt đầu tìm kiếm
    while (j <= n - m) {

        // So sánh pattern với đoạn hiện tại
        if (text.substr(j, m) == pattern) {
            cout << "Tim thay tai vi tri: " << j << endl;
        }

        // Nếu đã tới cuối text thì dừng
        if (j + m >= n)
            break;

        // Lấy giá trị lớn nhất giữa BM và QS
        int shift = max(
            bmBc[(unsigned char)text[j + m - 1]],
            qsBc[(unsigned char)text[j + m]]
        );

        // Dịch chuyển
        j += shift;
    }
}

int main() {
    string text, pattern;

    cin >> pattern >> text;

    // Gọi thuật toán Smith
    SMITH(pattern, text);

    return 0;
}