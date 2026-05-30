#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

// Hàm tính maximal suffix với thứ tự <=
int maxSuf(string pattern, int& p) {

    int m = pattern.length(); // Độ dài pattern

    int ms = -1; // Vị trí maximal suffix
    int j = 0;   // Vị trí đang xét
    int k = 1;   // Độ dài đoạn đang so sánh

    p = 1; // Chu kỳ ban đầu

    // Duyệt cho tới khi vượt quá pattern
    while (j + k < m) {
        char a = pattern[j + k];  // Ký tự phía sau
        char b = pattern[ms + k]; // Ký tự phía trước

        if (a < b) {
            j += k; // Bỏ qua đoạn hiện tại
            k = 1; // Reset độ dài so sánh
            p = j - ms;  // Cập nhật chu kỳ
        }
        else if (a == b) {
            // Nếu chưa đạt chu kỳ
            if (k != p) ++k; // Tăng độ dài so sánh
            else {
                j += p; // Nhảy theo chu kỳ
                k = 1; // Reset
            }
        }
        else {
            ms = j; // Cập nhật maximal suffix
            j = ms + 1; // Dịch sang vị trí tiếp theo
            k = 1;
            p = 1;
        }
    }
    return ms;
}

// Hàm tính maximal suffix với thứ tự >=
int maxSufTilde(string pattern, int& p) {
    int m = pattern.length();

    int ms = -1;
    int j = 0;
    int k = 1;

    p = 1;

    while (j + k < m) {
        char a = pattern[j + k], b = pattern[ms + k];

        if (a > b) {
            j += k;
            k = 1;
            p = j - ms;
        }
        else if (a == b) {
            if (k != p) ++k;
            else {
                j += p;
                k = 1;
            }
        }
        else {
            ms = j;
            j = ms + 1;
            k = 1;
            p = 1;
        }
    }
    return ms;
}

// Thuật toán Two-Way String Matching
void twoWay(string pattern, string text) {
    int m = pattern.length(); // Độ dài pattern
    int n = text.length();    // Độ dài text

    int p, q; // Chu kỳ
    int ell;  // Critical position
    int per;  // Period

    // Tiền xử lý maximal suffix theo <=
    int i = maxSuf(pattern, p);
    // Tiền xử lý maximal suffix theo >=
    int j = maxSufTilde(pattern, q);

    // Chọn suffix lớn hơn
    if (i > j) {
        ell = i;
        per = p;
    }
    else {
        ell = j;
        per = q;
    }

    // Kiểm tra pattern có tuần hoàn không
    if (pattern.substr(0, ell + 1) == pattern.substr(per, ell + 1)) {
        j = 0;
        // Memory dùng để tối ưu so sánh
        int memory = -1;
        // Duyệt text
        while (j <= n - m) {
            // So sánh nửa phải trước
            i = max(ell, memory) + 1;

            while (i < m && pattern[i] == text[i + j])  ++i;

            // Nếu nửa phải khớp
            if (i >= m) {
                i = ell; // So sánh nửa trái

                while (i > memory && pattern[i] == text[i + j]) --i;

                if (i <= memory) cout << "Match at position: " << j << endl;

                j += per; // Dịch theo chu kỳ
                memory = m - per - 1;
            }
            else {
                j += (i - ell); // Dịch theo vị trí mismatch
                memory = -1;
            }
        }
    }
    else {
        per = max(ell + 1, m - ell - 1) + 1; // Tính chu kỳ mới

        j = 0;
        while (j <= n - m) {
            i = ell + 1; // So sánh nửa phải trước

            while (i < m && pattern[i] == text[i + j]) ++i; 

            // Nếu nửa phải khớp
            if (i >= m) {
                i = ell; // So sánh nửa trái
                while (i >= 0 && pattern[i] == text[i + j]) --i;

                if (i < 0) cout << "Match at position: " << j << endl;

                j += per; // Dịch theo period
            }

            // Dịch theo mismatch
            else j += (i - ell);
        }
    }
}

int main() {
    string pattern, text;
    cin >> pattern >> text;

    twoWay(pattern, text);

    return 0;
}