#include <bits/stdc++.h>
using namespace std;

// Hàm băm rolling: tính toán hash cho cửa sổ tiếp theo dựa trên hash hiện tại
#define REHASH(a, b, h, d) ((((h) - (a) * (d)) << 1) + (b))

void karpRabin(string pattern, string text) {
    int m = pattern.length();
    int n = text.length();

    int d = 1;   // d = 2^(m-1), trọng số của ký tự đầu tiên trong cửa sổ (MSB)
    int hx = 0, hy = 0;
    int i, j;

    // Tiền xử lý: tính 2^(m-1) để dùng khi loại bỏ ký tự đầu trong rolling hash
    for (i = 1; i < m; i++)
        d = (d << 1);

    // Hash ban đầu của pattern và cửa sổ đầu tiên của text
    for (i = 0; i < m; i++) {
        hx = (hx << 1) + pattern[i];
        hy = (hy << 1) + text[i];
    }

    // Tìm kiếm pattern trong text
    j = 0;
    while (j <= n - m) {

        // So sánh hash + kiểm tra chuỗi thật
        if (hx == hy && text.substr(j, m) == pattern) {
            cout << "Pattern found at index " << j << endl;
        }

        // Cập nhật hash cửa sổ tiếp theo
        if (j < n - m) {
            hy = REHASH(text[j], text[j + m], hy, d);
        }

        j++;
    }
}

void printStep(string pattern, string text) {
    int m = pattern.length();
    int n = text.length();

    int d = 1;
    int hx = 0, hy = 0;
    int i, j;

    for (i = 1; i < m; i++)
        d <<= 1;

    for (i = 0; i < m; i++) {
        hx = (hx << 1) + pattern[i];
        hy = (hy << 1) + text[i];
    }

    cout << left;

    // HEADER
    cout << setw(6) << "j"
         << setw(15) << "window"
         << setw(15) << "hash"
         << setw(15) << "compare"
         << "result\n";

    cout << string(58, '-') << "\n";

    j = 0;

    while (j <= n - m) {

        string window = text.substr(j, m);
        bool match = (hx == hy && window == pattern);

        string compare = to_string(hy) + " vs " + to_string(hx);

        cout << setw(6) << j
             << setw(15) << window
             << setw(15) << hy
             << setw(15) << compare
             << (match ? "MATCH" : "")
             << "\n";

        if (j < n - m)
            hy = REHASH(text[j], text[j + m], hy, d);

        j++;
    }
}

int main() {
    string pattern; cin >> pattern;
    string text; cin >> text;

    karpRabin(pattern, text);

    cout << endl;
    printStep(pattern, text);

    return 0;
}