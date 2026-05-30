#include <bits/stdc++.h>
using namespace std;

const int ASIZE = 256;

// Tiền xử lý bảng bad character
void preBmBc(const string &pattern, const string &text,
             vector<int> &bmBc) {
    int m = pattern.size();
    // Khởi tạo bảng bad character với giá trị mặc định là m
    bmBc.assign(ASIZE, m);

    for (int i = 0; i < m - 1; i++) {
        // Lưu khoảng dịch chuyển của ký tự pattern[i]
        bmBc[(unsigned char)pattern[i]] = m - i - 1;
    }
}

// Tính mảng suff
void suffixes(const string &pattern, const string &text, vector<int> &suff) {
    int m = pattern.size();

    // Khởi tạo mảng suff với giá trị mặc định là 0
    suff.assign(m, 0);

    int f = 0, g = m - 1;

    // Suffix dài nhất kết thúc tại vị trí m-1 là chính nó
    suff[m - 1] = m;

    for (int i = m - 2; i >= 0; i--) {
        // Tái sử dụng kết quả đã tính trước đó
        if (i > g && suff[i + m - 1 - f] < i - g) {
            // Suffix tại i có độ dài bằng suff tại vị trí tương ứng
            suff[i] = suff[i + m - 1 - f];
        } else {

            // Mở rộng đoạn khớp suffix
            if (i < g)  g = i;
            //
            f = i;

            while (g >= 0 && pattern[g] == pattern[g + m - 1 - f]) {
                g--;
            }

            // Tính độ dài suffix khớp tại vị trí i
            suff[i] = f - g;
        }
    }
}

// Tiền xử lý bảng good suffix
void preBmGs(const string &pattern, const string &text, const vector<int> &suff, vector<int> &bmGs) {
    int m = pattern.size();

    // Khởi tạo bảng good suffix với giá trị mặc định là m
    bmGs.assign(m, m);

    int j = 0;

    // Xử lý trường hợp suffix cũng là prefix
    for (int i = m - 1; i >= 0; i--) {
        // Nếu suff[i] bằng i + 1, nghĩa là suffix tại i cũng là prefix
        if (suff[i] == i + 1) {
            for (; j < m - 1 - i; j++) {
                // Cập nhật bước dịch cho các vị trí chưa được cập nhật
                if (bmGs[j] == m)  bmGs[j] = m - 1 - i;
            }
        }
    }

    // Xử lý trường hợp suffix xuất hiện lại bên trong mẫu
    for (int i = 0; i <= m - 2; i++) {
        bmGs[m - 1 - suff[i]] = m - 1 - i;
    }
}

// Thuật toán Apostolico-Giancarlo
void apostolicoGiancarlo(const string &pattern, const string &text) {
    int m = pattern.size();
    int n = text.size();

    vector<int> bmBc, bmGs, suff, skip;

    preBmBc(pattern, text, bmBc);
    suffixes(pattern, text, suff);
    preBmGs(pattern, text, suff, bmGs);

    // Khởi tạo bảng skip
    skip.assign(m, 0);

    int j = 0;
    while (j <= n - m) {
        // So khớp từ phải sang trái
        int i = m - 1;
        
        int shift = 1;

        while (i >= 0) {
            int k = skip[i];
            int s = suff[i];
            // Có thông tin skip từ lần dò trước
            if (k > 0) {
                // Đoạn đã biết khớp dài hơn suffix của pattern tại i
                if (k > s) {
                    if (i + 1 == s) i = -1;
                    else i -= s;
                    break;
                } 
                else {
                    i -= k;
                    if (k < s) break;
                }
            } 
            // Không có thông tin skip, so sánh trực tiếp
            else {
                if (pattern[i] == text[i + j]) i--;
                // Nếu không khớp, dừng lại
                else break;
            }
        }

        // Tìm thấy pattern
        if (i < 0) {
            cout << "Match at position: " << j << "\n";
            // Cập nhật bảng skip cho lần dò tiếp theo
            skip[m - 1] = m;
            // Dịch pattern sang phải để tìm kiếm lần tiếp theo
            shift = bmGs[0];

        } 
        // Không tìm thấy pattern, tính bước dịch dựa trên bad character và good suffix
        else {
            // Lưu độ dài suffix đã khớp
            skip[m - 1] = m - 1 - i;

            // Chọn bước dịch lớn nhất giữa bad character và good suffix
            shift = max(bmGs[i], bmBc[(unsigned char)text[i + j]] - m + 1 + i);
        }
        j += shift;

        // Cập nhật lại bảng skip sau khi dịch
        if (shift < m) {
            for (int t = 0; t < m - shift; t++) skip[t] = skip[t + shift];
            for (int t = m - shift; t < m; t++) skip[t] = 0;

        } 
        // Nếu dịch đủ xa để không còn thông tin skip, reset bảng skip
        else  fill(skip.begin(), skip.end(), 0);
    }
}

int main() {

    string text, pattern;

    cin >> pattern;
    cin >> text;

    apostolicoGiancarlo(pattern, text);

    return 0;
}