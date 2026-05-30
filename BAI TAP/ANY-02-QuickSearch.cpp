#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int ASIZE = 256;

// Hàm tiền xử lý bảng dịch chuyển
void preQsBc(const string &pattern, vector<int> &qsBc) {
    int m = pattern.length();

    // Khởi tạo mặc định m + 1 cho mọi ký tự
    for (int i = 0; i < ASIZE; ++i)
        qsBc[i] = m + 1;

    // Tính khoảng dịch cho từng ký tự trong pattern
    for (int i = 0; i < m; ++i)
        qsBc[(unsigned char)pattern[i]] = m - i;
}

// Thuật toán Quick Search
void quickSearch(const string &pattern, const string &text) {
    int m = pattern.length();
    int n = text.length();

    vector<int> qsBc(ASIZE);

    // Tiền xử lý
    preQsBc(pattern, qsBc);

    int j = 0;

    // Duyệt trên text
    while (j <= n - m) {

        // So sánh pattern với đoạn hiện tại của text
        if (text.substr(j, m) == pattern)
            cout << "Match at position: " << j << endl;

        // Nếu đã tới cuối thì dừng
        if (j + m >= n)
            break;

        // Dịch chuyển theo bảng qsBc
        j += qsBc[(unsigned char)text[j + m]];
    }
}

int main() {
    string pattern, text;

    cin >> pattern >> text;

    quickSearch(pattern, text);

    return 0;
}