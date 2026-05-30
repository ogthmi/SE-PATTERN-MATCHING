#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// Hàm tiền xử lý tạo bảng kmpNext (Tagged Border)
vector<int> preKmp(const string& pattern) {
    int m = pattern.length();
    vector<int> kmpNext(m + 1);

    int i = 0;
    int j = -1;
    kmpNext[0] = -1;

    while (i < m) {
        while (j > -1 && pattern[i] != pattern[j]) {
            // Nếu sai khác, quay lại vị trí kmpNext của j
            j = kmpNext[j];
        }

        i++;
        j++;
        
        // Nếu ký tự kế tiếp trùng nhau và chưa vượt quá m
        // kế thừa giá trị bước nhảy để tối ưu tagged border
        if (i < m && pattern[i] == pattern[j]) {
            kmpNext[i] = kmpNext[j];
        } else {
            kmpNext[i] = j; // Gán giá trị bước nhảy bằng độ dài border hiện tại
        }
    }

    return kmpNext;
}

// Hàm tìm kiếm Knuth-Morris-Pratt
void knuthMorrisPratt(const string& pattern, const string& text) {
    int m = pattern.length();
    int n = text.length();

    vector<int> kmpNext = preKmp(pattern);
     
    int i = 0;
    int j = 0;

    while (j < n) {
        // Sai khác, quay lại vị trí kmpNext của i
        while (i > -1 && pattern[i] != text[j]) {
            i = kmpNext[i];
        }

        
        i++;
        j++;

        // Tìm thấy mẫu
        if (i >= m) {
            cout << "Match at position: " << (j - i) << endl;
            // Quay lại vị trí kmpNext của i và tiếp tục tìm kiếm
            i = kmpNext[i];
        }
    }
}

void printStepKMP(const string& pattern, const string& text) {
    int m = pattern.length();
    int n = text.length();

    vector<int> kmpNext = preKmp(pattern);

    int i = 0;
    int j = 0;
    int step = 1;

    // Header bảng log
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

        // Nhánh xử lý: Sai khác (Mismatch)
        while (i > -1 && pattern[i] != text[j]) {

            int oldI = i;

            cout << left
                 << setw(6)  << step++
                 << setw(5)  << oldI
                 << setw(5)  << j
                 << setw(8)  << pattern[oldI]
                 << setw(8)  << text[j]
                 << setw(22) << (string(1, pattern[oldI]) + "!=" + string(1, text[j]) + " (false)")
                 << setw(35) << ("i=kmpNext[" + to_string(oldI) + "]=" + to_string(kmpNext[oldI]))
                 << setw(18) << j
                 << setw(18) << "Sai khac"
                 << ""
                 << endl;

            i = kmpNext[i];
        }

        // Nhánh xử lý: Khớp (Match) hoặc Ngắn mạch Ngoài mảng (i == -1)
        int oldI = i;
        string compStr, actionStr, resStr;
        int nextJ = j + 1;

        if (i == -1) {
            compStr = "Bỏ qua";
            actionStr = "0   i += 1";
            resStr = "Ngoai mang";
        } else {
            compStr = string(1, pattern[i]) + "==" + string(1, text[j]) + " (true)";
            actionStr = to_string(i + 1) + "   i += 1";
            resStr = "Khop";
        }

        cout << left
             << setw(6)  << step++
             << setw(5)  << (oldI == -1 ? "-1" : to_string(oldI))
             << setw(5)  << j
             << setw(8)  << (oldI == -1 ? "" : string(1, pattern[oldI]))
             << setw(8)  << text[j]
             << setw(22) << compStr
             << setw(35) << actionStr
             << setw(18) << nextJ
             << setw(18) << resStr;

        i++;
        j++;

        // Nhánh xử lý: Tìm thấy mẫu hoàn chỉnh
        if (i >= m) {

            cout << (j - i) << endl;

            cout << left
                 << setw(6)  << step++
                 << setw(5)  << i
                 << setw(5)  << j
                 << setw(8)  << ""
                 << setw(8)  << ""
                 << setw(22) << ""
                 << setw(35) << ("i=kmpNext[" + to_string(i) + "]=" + to_string(kmpNext[i]))
                 << setw(18) << j
                 << setw(18) << "Tim thay mau"
                 << (j - i)
                 << endl;

            i = kmpNext[i];
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

    knuthMorrisPratt(pattern, text);
    cout << endl;
    
    printStepKMP(pattern, text);

    return 0;
}