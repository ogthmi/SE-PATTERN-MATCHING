#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

const int ASIZE = 256;

// Struct lưu vị trí và ký tự
struct Pattern {
    int loc;
    char c;
};

// Bảng minShift
vector<int> minShift;

// Hàm tiền xử lý Quick Search Bad Character
void preQsBc(const string &pattern, vector<int> &qsBc) {
    int m = pattern.length();

    for (int i = 0; i < ASIZE; ++i) qsBc[i] = m + 1;
    for (int i = 0; i < m; ++i) qsBc[(unsigned char)pattern[i]] = m - i;
}

// Tính bảng minShift
void computeMinShift(const string &pattern) {
    int m = pattern.length();
    minShift.resize(m);

    for (int i = 0; i < m; ++i) {
        int j;

        // Tìm ký tự giống gần nhất bên trái
        for (j = i - 1; j >= 0; --j)  if (pattern[i] == pattern[j]) break;

        minShift[i] = i - j; // Khoảng cách tới lần xuất hiện trước
    }
}

// Hàm so sánh cho Maximal Shift
bool maxShiftPcmp(const Pattern &pat1, const Pattern &pat2) {
    int dsh = minShift[pat2.loc] - minShift[pat1.loc]; // So sánh theo minShift
    if (dsh != 0) return dsh < 0; // Nếu khác nhau
    return pat1.loc > pat2.loc; // Nếu bằng nhau ưu tiên vị trí lớn hơn
}

// Sắp xếp pattern theo Maximal Shift
void orderPattern(const string &pattern, vector<Pattern> &pat) {
    int m = pattern.length();
    pat.resize(m);

    for (int i = 0; i < m; ++i) {
        pat[i].loc = i;
        pat[i].c = pattern[i];
    }
    sort(pat.begin(), pat.end(), maxShiftPcmp);
}

// Tìm leftward matching shift tiếp theo
int matchShift(const string &pattern, int ploc, int lshift, vector<Pattern> &pat) {
    int m = pattern.size(), i, j;

    // Thử từng shift
    for (; lshift < m; ++lshift) {
        i = ploc;

        while (--i >= 0) {
            j = pat[i].loc - lshift;

            if (j < 0) continue; // Nếu vượt trái thì bỏ qua
            if (pat[i].c != pattern[j]) break; // Nếu mismatch
        }
        if (i < 0) break; // Nếu match hoàn toàn
    }

    return lshift;
}

// Tiền xử lý adapted good suffix
void preAdaptedGs(const string &pattern, vector<int> &adaptedGs, vector<Pattern> &pat) {
    int m = pattern.size(), lshift, i, ploc;

    adaptedGs.resize(m + 1);
    adaptedGs[0] = lshift = 1;

    // Xây bảng shift cơ bản
    for (ploc = 1; ploc <= m; ++ploc) {
        lshift = matchShift(pattern, ploc, lshift, pat);
        adaptedGs[ploc] = lshift;
    }

    for (ploc = 0; ploc <= m; ++ploc) {
        lshift = adaptedGs[ploc];

        while (lshift < m) {
            i = pat[ploc].loc - lshift;
            if (i < 0 || pat[ploc].c != pattern[i]) break; // Vượt biên/mismatch

            ++lshift;
            lshift = matchShift(pattern, ploc, lshift, pat);
        }

        adaptedGs[ploc] = lshift;
    }
}

// Thuật toán Maximal Shift
void maximalShift(string pattern, string text) {
    int m = pattern.length(), n = text.length();

    vector<int> adaptedGs, qsBc(ASIZE);
    vector<Pattern> pat;

    computeMinShift(pattern);
    orderPattern(pattern, pat);
    preQsBc(pattern, qsBc);
    preAdaptedGs(pattern, adaptedGs, pat);


    for (auto shi: minShift) cout << shi << " ";
    cout << endl;

    for (auto pi: pat) cout << pi.c << " " << pi.loc << endl;
    cout << endl;

    for (auto ada: adaptedGs) cout << ada << " ";
    cout << endl;



    int j = 0;
    while (j <= n - m) {
        int i = 0;
        while (i < m && pat[i].c == text[j + pat[i].loc])  ++i;

        if (i >= m) cout << "Match at position: " << j << endl;

        j += max(adaptedGs[i], qsBc[(unsigned char) text[j + m]]);
    }
}

int main() {
    string pattern, text;

    cin >> pattern >> text;

    maximalShift(pattern, text);

    return 0;
}