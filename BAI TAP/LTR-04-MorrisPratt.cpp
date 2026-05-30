#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// Hàm tiền xử lý tạo bảng mpNext
vector<int> preMp(const string& pattern) {
    int m = pattern.length();
    vector<int> mpNext(m + 1);

    int i = 0;
    int j = -1;
    mpNext[0] = -1;

    while (i < m) {
        while (j > -1 && pattern[i] != pattern[j]) {
            // Nếu sai khác, quay lại vị trí mpNext của j
            j = mpNext[j];
        }

        // Nếu khớp, tăng i và j lên
        i++;
        j++;
        mpNext[i] = j;
    }

    return mpNext;
}

// Hàm tìm kiếm Morris-Pratt
void morrisPratt(const string& pattern, const string& text) {
    int m = pattern.length();
    int n = text.length();

    vector<int> mpNext = preMp(pattern);
    // i là chỉ số của pattern, j là chỉ số của text
    int i = 0;
    int j = 0;

    while (j < n) {
        // Sai khác, quay lại vị trí mpNext của i
        while (i > -1 && pattern[i] != text[j]) {
            i = mpNext[i];
        }

        // Khớp, tăng i và j lên
        i++;
        j++;

        // Tìm thấy mẫu
        if (i >= m) {
            cout << "Match at position: " << (j - i) << endl;

            // Quay lại vị trí mpNext của i và tiếp tục tìm kiếm
            i = mpNext[i];
        }
    }
}


void printStep(const string& pattern, const string& text) {
    int m = pattern.length();
    int n = text.length();

    vector<int> mpNext = preMp(pattern);

    int i = 0;
    int j = 0;
    int step = 1;

    // Header
    cout << left
         << setw(6)  << "Buoc"
         << setw(5)  << "i"
         << setw(5)  << "j"
         << setw(8)  << "x[i]"
         << setw(8)  << "y[j]"
         << setw(22) << "x[i] == y[j]?"
         << setw(35) << "i (cap nhat) va giai thich"
         << setw(18) << "j (cap nhat)"
         << setw(18) << "Ket qua"
         << "Output\n";

    while (j < n) {

        // Sai khác
        while (i > -1 && pattern[i] != text[j]) {

            int oldI = i;

            cout << left
                 << setw(6)  << step++
                 << setw(5)  << oldI
                 << setw(5)  << j
                 << setw(8)  << pattern[oldI]
                 << setw(8)  << text[j]
                 << setw(22) << (string(1, pattern[oldI]) + "!=" + string(1, text[j]) + " (false)")
                 << setw(35) << ("i=mpNext[" + to_string(oldI) + "]=" + to_string(mpNext[oldI]))
                 << setw(18) << j
                 << setw(18) << "Sai khac"
                 << ""
                 << endl;

            i = mpNext[i];
        }

        // Khớp
        cout << left
             << setw(6)  << step++
             << setw(5)  << i
             << setw(5)  << j
             << setw(8)  << pattern[i]
             << setw(8)  << text[j]
             << setw(22) << (string(1, pattern[i]) + "==" + string(1, text[j]) + " (true)")
             << setw(35) << (to_string(i + 1) + "   i += 1")
             << setw(18) << (j + 1)
             << setw(18) << "Khop";

        i++;
        j++;

        // Tìm thấy mẫu
        if (i >= m) {

            cout << (j - i) << endl;

            cout << left
                 << setw(6)  << step++
                 << setw(5)  << i
                 << setw(5)  << j
                 << setw(8)  << ""
                 << setw(8)  << ""
                 << setw(22) << ""
                 << setw(35) << ("i=mpNext[" + to_string(i) + "]=" + to_string(mpNext[i]))
                 << setw(18) << j
                 << setw(18) << "Tim thay mau"
                 << (j - i)
                 << endl;

            i = mpNext[i];
        }
        else {
            cout << endl;
        }
    }
}

int main() {
    string pattern, text;
    cin >> pattern;
    cin >> text;

    morrisPratt(pattern, text);
    
    cout << endl;
    // printStep(pattern, text);

    return 0;
}