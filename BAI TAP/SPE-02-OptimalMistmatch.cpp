#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

const int ASIZE = 256;

// Struct lưu vị trí và ký tự trong pattern
struct Pattern {
    int loc; 
    char c;  
};

// Bảng tần suất ký tự
vector<int> freq(ASIZE, 0);

// Hàm tiền xử lý Quick Search Bad Character
void preQsBc(const string &pattern, vector<int> &qsBc) {
    int m = pattern.length();

    for (int i = 0; i < ASIZE; ++i) qsBc[i] = m + 1;
    for (int i = 0; i < m; ++i) qsBc[(unsigned char)pattern[i]]= m - i;
}

// Hàm so sánh cho Optimal Mismatch
bool optimalPcmp(const Pattern &pat1, const Pattern &pat2) {
    // So sánh theo tần suất ký tự
    int fx = freq[(unsigned char)pat1.c] - freq[(unsigned char)pat2.c];

    // Nếu tần suất khác nhau
    if (fx != 0)  return fx < 0;
    // Nếu bằng nhau thì ưu tiên vị trí lớn hơn
    return pat1.loc > pat2.loc;
}

// Hàm xây ordered pattern
void orderPattern(const string &pattern, vector<Pattern> &pat) {
    int m = pattern.length();
    pat.resize(m);

    for (int i = 0; i < m; ++i) {
        pat[i].loc = i;
        pat[i].c = pattern[i];
    }
    sort(pat.begin(), pat.end(), optimalPcmp);
}

// Hàm tìm leftward matching shift tiếp theo
int matchShift(const string &pattern, int ploc, int lshift, vector<Pattern> &pat) {
    int m = pattern.size(), i, j;

    // Thử từng shift
    for (; lshift < m; ++lshift) {
        i = ploc;

        // Kiểm tra các ký tự đã xét
        while (--i >= 0) {
            // Vị trí tương ứng sau khi dịch
            j = pat[i].loc - lshift;

            // Nếu vượt trái thì bỏ qua
            if (j < 0) continue;

            // Nếu mismatch thì dừng
            if (pat[i].c != pattern[j]) break;
        }

        // Nếu match hoàn toàn
        if (i < 0) break;
    }

    return lshift;
}

// Hàm tiền xử lý adapted good suffix
void preAdaptedGs(const string &pattern, vector<int> &adaptedGs, vector<Pattern> &pat) {
    int m = pattern.size(), lshift, i, ploc;

    adaptedGs.resize(m + 1);
    adaptedGs[0] = lshift = 1;

    // Xây shift cơ bản
    for (ploc = 1; ploc <= m; ++ploc) adaptedGs[ploc] = matchShift(pattern, ploc, lshift, pat);

    // Tối ưu lại bảng shift
    for (ploc = 0; ploc <= m; ++ploc) {
        lshift = adaptedGs[ploc];

        while (lshift < m) {
            // Vị trí kiểm tra tiếp theo
            i = pat[ploc].loc - lshift;

            // Nếu vượt biên hoặc mismatch
            if (i < 0 || pat[ploc].c != pattern[i]) break;

            ++lshift;

            // Tìm shift hợp lệ tiếp theo
            lshift = matchShift(pattern, ploc, lshift, pat);
        }
        // Cập nhật shift tối ưu
        adaptedGs[ploc] = lshift;
    }
}

// Thuật toán Optimal Mismatch
void optimalMistmatch(string pattern, string text) {
    int m = pattern.length(), n = text.length();

    for (char c: pattern) freq[(unsigned int) c]++;

    vector<int> adaptedGs, qsBc(ASIZE);
    vector<Pattern> pat;

    orderPattern(pattern, pat);
    preQsBc(pattern, qsBc);
    preAdaptedGs(pattern,  adaptedGs, pat);

    for (auto pi: pat) cout << pi.c << " " << pi.loc << endl;
    cout << endl;

    for (auto ada: adaptedGs) cout << ada << " ";
    cout << endl;

    int j = 0;

    // Duyệt text
    while (j <= n - m) {
        int i = 0;
        // So sánh theo thứ tự đã sắp xếp
        while (i < m && pat[i].c == text[j + pat[i].loc]) ++i;

        if (i >= m) cout << "Match at position: " << j << endl;

        j += max(adaptedGs[i], qsBc[(unsigned char) text[j + m]]);
    }
}

int main() {
    string pattern, text;
    cin >> pattern >> text;

    optimalMistmatch(pattern, text);

    return 0;
}