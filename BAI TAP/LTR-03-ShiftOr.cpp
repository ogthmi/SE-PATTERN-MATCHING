#include <bits/stdc++.h>
using namespace std;

const int ASIZE = 256; // Số lượng ký tự có thể xuất hiện (ASCII) - 256 ký tự

// Tiền xử lý chuỗi mẫu pattern để tạo bảng S và giá trị lim
unsigned int preSo(string pattern, unsigned int S[]) {
    unsigned int j, lim;
    
    // Khởi tạo bảng S với tất cả bit được đặt là 1 (tức là ~0)
    for (int i = 0; i < ASIZE; i++)
        // ~ là phép NOT bitwise, ~0 sẽ tạo ra một số có tất cả bit là 1 
        // (tức là ban đầu mọi vị trí đều được coi là không khớp)
        S[i] = ~0;

    lim = 0; // lim dùng để xác định điều kiện "match"

    for (int i = 0, j = 1; i < pattern.size(); i++, j <<= 1) {
        // Cập nhật bảng S: Đặt bit j thành 0 cho ký tự pattern[i]
        S[(unsigned char)pattern[i]] &= ~j;
        lim |= j;
    }

    // Dịch lim và đảo bit để tạo mask kiểm tra match
    lim = ~(lim >> 1);
    return lim;
}


void ShiftOr(string pattern, string text) {
    int m = pattern.size(), n = text.size();

    unsigned int S[ASIZE], lim = preSo(pattern, S), state = ~0;

    for (int j = 0; j < n; j++) {
        state = (state << 1) | S[(unsigned char)text[j]];
        if (state < lim) cout << "Match at position " << (j - m + 1) << endl;
    }
}


string toBinary(unsigned int x, int m) {
    string s = "";
    for (int i = 0; i < m; i++) {
        if (x & (1 << i)) s = "1 " + s;
        else s = "0 " + s;
    }
    return s;
}

void printStep(string pattern, string text) {
    int m = pattern.size();
    int n = text.size();

    unsigned int S[ASIZE];
    unsigned int lim = preSo(pattern, S);

    cout << "Lim: " << toBinary(lim, m) << "\n\n";

    unsigned int state = ~0;

    cout << left;

    cout << setw(3) << "j"
         << setw(6) << "t[j]"
         << setw(15) << "R before"
         << setw(15) << "SHIFT(R)"
         << setw(15) << "S[t[j]]"
         << setw(13) << "R after"
         << "Output" << "\n";

    cout << string(80, '-') << "\n";

    for (int j = 0; j < n; j++) {

        unsigned int R_before = state;
        unsigned int shifted = (state << 1);
        unsigned int S_c = S[(unsigned char)text[j]];

        state = shifted | S_c;

        cout << setw(3) << j
             << setw(6) << text[j]
             << setw(15) << toBinary(R_before, m)
             << setw(15) << toBinary(shifted, m)
             << setw(15) << toBinary(S_c, m)
             << setw(15) << toBinary(state, m);

        if (state < lim) {
            cout << "MATCH at " << (j - m + 1);
        }

        cout << "\n";
    }
}

int main() {
    string pattern; cin >> pattern;
    string text; cin >> text;

    ShiftOr(pattern, text);

    cout << endl;
    printStep(pattern, text);

    return 0;
}