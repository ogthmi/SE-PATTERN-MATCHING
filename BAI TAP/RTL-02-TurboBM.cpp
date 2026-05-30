#include <bits/stdc++.h>
using namespace std;

const int ASIZE = 256;

// Khởi tạo bảng bad character dùng để xác định bước dịch khi gặp ký tự lệch
void preBmBc(const string &pattern, vector<int> &bmBc) {
    int m = pattern.size();
    bmBc.assign(ASIZE, m);

    for (int i = 0; i < m - 1; i++) {
        bmBc[(unsigned char)pattern[i]] = m - i - 1;
    }
}

// Tính mảng suff để xác định độ dài hậu tố trùng với suffix của pattern
void suffixes(const string &pattern, vector<int> &suff) {
    int m = pattern.size();
    suff.assign(m, 0);

    int f = 0, g = m - 1;
    suff[m - 1] = m;

    for (int i = m - 2; i >= 0; i--) {
        if (i > g && suff[i + m - 1 - f] < i - g) {
            suff[i] = suff[i + m - 1 - f];
        } else {
            if (i < g) g = i;
            f = i;

            while (g >= 0 && pattern[g] == pattern[g + m - 1 - f]) {
                g--;
            }

            suff[i] = f - g;
        }
    }
}

// Tạo bảng good suffix để xác định bước dịch tối ưu khi mismatch
void preBmGs(const string &pattern, const vector<int> &suff, vector<int> &bmGs) {
    int m = pattern.size();
    bmGs.assign(m, m);

    int j = 0;

    for (int i = m - 1; i >= 0; i--) {
        if (suff[i] == i + 1) {
            for (; j < m - 1 - i; j++) {
                if (bmGs[j] == m)
                    bmGs[j] = m - 1 - i;
            }
        }
    }

    for (int i = 0; i <= m - 2; i++) {
        bmGs[m - 1 - suff[i]] = m - 1 - i;
    }
}

// Thuật toán Turbo Boyer-Moore tìm kiếm pattern trong text
void turboBM(const string &pattern, const string &text) {
    int m = pattern.size();
    int n = text.size();

    vector<int> bmBc, bmGs, suff;

    preBmBc(pattern, bmBc);
    suffixes(pattern, suff);
    preBmGs(pattern, suff, bmGs);

    int j = 0;
    int u = 0;          // lưu độ dài đoạn hậu tố đã khớp ở lần dò trước
    int shift = m;

    while (j <= n - m) {
        int i = m - 1;

        while (i >= 0 && pattern[i] == text[i + j]) {
            --i;

            // bỏ qua phần đã được xác nhận khớp từ lần dò trước
            if (u != 0 && i == m - 1 - shift) i -= u;
        }

        if (i < 0) {
            cout << "Match at position: " << j << "\n";

            shift = bmGs[0]; // dịch khi khớp hoàn toàn
            u = m - shift;   // cập nhật độ dài hậu tố khớp
        }
        else {
            int v = m - 1 - i; // độ dài hậu tố đã khớp trước mismatch

            int turboShift = u - v;
            int bcShift = bmBc[(unsigned char)text[i + j]] - m + 1 + i;

            shift = max({turboShift, bcShift, bmGs[i]});

            if (shift == bmGs[i]) {
                u = min(m - shift, v); // giữ lại phần hậu tố có ích
            }
            else {
                if (turboShift < bcShift)
                    shift = max(shift, u + 1);

                u = 0; // reset nếu không dùng good suffix
            }
        }

        j += shift; // dịch cửa sổ sang phải
    }
}

int main() {
    string pattern, text;

    cin >> pattern >> text;

    turboBM(pattern, text);

    return 0;
}