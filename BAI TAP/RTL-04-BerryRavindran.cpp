#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int ASIZE = 256; // Bảng mã ASCII

void printBrBc(string pattern, int brBc[ASIZE][ASIZE]) {
    int m = pattern.size();

    for (int i = 0; i < m - 1; ++i) {
        for (int j = 0; j < m - 1; ++j) {
            cout << brBc['a' + i]['a' + j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// Hàm tiền xử lý bảng bad character của thuật toán Berry-Ravindran
void preBrBc(string pattern, int brBc[ASIZE][ASIZE]) {
    int m = pattern.length(); // Độ dài pattern

    for (int a = 0; a < ASIZE; ++a) {
        for (int b = 0; b < ASIZE; ++b) brBc[a][b] = m + 2;
    }
    printBrBc(pattern, brBc);
    
    // Nếu ký tự đầu tiên của pattern xuất hiện ở vị trí thứ 2 sau cửa sổ
    for (int a = 0; a < ASIZE; ++a) brBc[a][(unsigned char)pattern[0]] = m + 1;
    printBrBc(pattern, brBc);
    
    // Gán giá trị dịch cho từng cặp ký tự liên tiếp trong pattern
    for (int i = 0; i < m - 1; ++i) brBc[(unsigned char)pattern[i]][(unsigned char)pattern[i + 1]] = m - i;
    printBrBc(pattern, brBc);
    
    // Nếu ký tự cuối pattern xuất hiện ngay sau cửa sổ
    for (int a = 0; a < ASIZE; ++a) brBc[(unsigned char)pattern[m - 1]][a] = 1;
    printBrBc(pattern, brBc);
}

// Hàm tìm kiếm Berry-Ravindran
void berryRavindran(string pattern, string text) {
    int m = pattern.length(), n = text.length();    

    int brBc[ASIZE][ASIZE]; 
    preBrBc(pattern, brBc);


    // Thêm 2 ký tự giả để tránh truy cập vượt mảng
    text += '\0'; text += '\0';

    int j = 0;
    while (j <= n - m) {
        // So sánh trực tiếp pattern với đoạn text hiện tại
        if (text.substr(j, m) == pattern) {
            // In ra vị trí tìm thấy
            cout << "Match at position: " << j << endl;
        }

        // Dịch chuyển theo bảng Berry-Ravindran
        j += brBc[(unsigned char)text[j + m]][(unsigned char)text[j + m + 1]];
    }
}

int main() {
    string pattern, text;

    cin >> pattern;
    cin >> text;

    berryRavindran(pattern, text);

    return 0;
}