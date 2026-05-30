#include <bits/stdc++.h>
using namespace std;


void notSoNaive(string pattern, string text) {
    int m = pattern.size();
    int n = text.size();

    int j, k, ell;

    // Tiền xử lý: xác định k và ell dựa trên 2 ký tự đầu tiên của pattern
    if (pattern[0] == pattern[1]) {
        k = 2; // Nếu 2 ký tự đầu giống nhau, có thể bỏ qua cả 2 khi mismatch
        ell = 1; // Nếu match, chỉ cần shift 1 để kiểm tra lại
    } else {
        k = 1; // Nếu 2 ký tự đầu khác nhau, chỉ cần bỏ qua 1 ký tự khi mismatch
        ell = 2; // Nếu match, có thể bỏ qua cả 2 ký tự vì đã kiểm tra x[0] và x[1]
    }

    // Tìm kiếm pattern trong text
    j = 0;
    while (j <= n - m) {

        if (pattern[1] != text[j + 1]) {
            j += k; // Mismatch ở x[1], shift theo k
        } else {
            // Kiểm tra tiếp phần còn lại của pattern (bỏ qua x[1] đã match)
            if (text.substr(j + 2, m - 2) == pattern.substr(2, m - 2) &&
                // Đảm bảo x[0] cũng match với y[j]
                text[j] == pattern[0]) {
                cout << "Pattern occurs at shift " << j << endl;
            }
            j += ell; // Match ở x[1], shift theo ell
        }
    }
}

void printStep(string pattern, string text) {
    int m = pattern.size();
    int n = text.size();

    int k, ell;

    if (pattern[0] == pattern[1]) {
        k = 2;
        ell = 1;
    } else {
        k = 1;
        ell = 2;
    }

    int j = 0;
    int step = 1;

    cout << left;

    // HEADER
    cout << setw(6) << "Step"
         << setw(6) << "j"
         << setw(12) << "x"
         << setw(20) << "y[j..j+m-1]"
         << setw(20) << "x[1]==y[j+1]?"
         << setw(30) << "x[2..m-1]==y[j+2..j+m-1]?"
         << "Next shift\n";

    cout << string(104, '-') << "\n";

    while (j <= n - m) {

        string window = text.substr(j, m);

        string compare1 = string(1, pattern[1]) + " vs " + text[j + 1];

        string result;

        if (pattern[1] != text[j + 1]) {
            result = "Mismatch → k";
        } else {
            bool ok = true;

            for (int i = 0; i < m; i++) {
                if (i == 1) continue;
                if (text[j + i] != pattern[i]) {
                    ok = false;
                    break;
                }
            }

            result = ok ? "Match → ell" : "Partial → ell";
        }

        int nextShift = (pattern[1] != text[j + 1]) ? k : ell;

        cout << setw(6) << step
             << setw(6) << j
             << setw(12) << pattern
             << setw(20) << window
             << setw(20) << compare1
             << setw(32) << result
             << j + nextShift
             << "\n";

        j += nextShift;
        step++;
    }
}

int main() {
    string pattern; cin >> pattern;
    string text; cin >> text;

    printStep(pattern, text);

    cout << endl;
    notSoNaive(pattern, text);

    return 0;
}