#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>

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
            j = kmpNext[j];
        }

        i++;
        j++;
        
        if (i < m && pattern[i] == pattern[j]) {
            kmpNext[i] = kmpNext[j];
        } else {
            kmpNext[i] = j;
        }
    }

    return kmpNext;
}

// Hàm tìm kiếm Apostolico-Crochemore 
void apostolicoCrochemore(const string& pattern, const string& text) {
    int m = pattern.length();
    int n = text.length();

    vector<int> kmpNext = preKmp(pattern);
    int i, j, k, ell;

    // Tính toán giá trị ell đặc biệt
    for (ell = 1; pattern[ell - 1] == pattern[ell]; ell++);
    if (ell == m)
        ell = 0;

    // Thiết lập trạng thái ban đầu cho bộ ba (i, j, k)
    i = ell;
    j = k = 0;
    while (j <= n - m) {
        // Pha 1: So khớp vùng phải (Hậu tố) từ vị trí i
        while (i < m && pattern[i] == text[i + j])
            ++i;
        // Pha 2: Nếu vùng phải khớp hoàn toàn, kiểm tra vùng trái (Tiền tố) từ vị trí k
        if (i >= m) {
            while (k < ell && pattern[k] == text[j + k])
                ++k;
            // Nếu vùng trái cũng khớp, tìm thấy mẫu tại vị trí j
            if (k >= ell)
                cout << "Match at position: " << j << endl;
        }
        
        // Cập nhật dịch chuyển cửa sổ và bộ ba trạng thái
        j += (i - kmpNext[i]);
        if (i == ell)
            k = max(0, k - 1);
        else if (kmpNext[i] <= ell) {
            k = max(0, kmpNext[i]);
            i = ell;
        }
        else {
            k = ell;
            i = kmpNext[i];
        }
    }
}

// Hàm in chi tiết từng bước chạy mô phỏng của thuật toán AC
void printStepAC(const string& pattern, const string& text) {
    int m = pattern.length();
    int n = text.length();

    vector<int> kmpNext = preKmp(pattern);
    int i, j, k, ell;
    int step = 1;

    // Giai đoạn tiền xử lý tính toán giá trị ell
    for (ell = 1; pattern[ell - 1] == pattern[ell]; ell++);
    if (ell == m)
        ell = 0;

    cout << "\n--- BANG TRACE THUAT TOAN APOSTOLICO-CROCHEMORE ---\n";
    cout << "Gia tri dac biet ell = " << ell << "\n\n";

    // Thiết lập Header cho bảng hiển thị
    cout << left
         << setw(6)  << "Buoc"
         << setw(12) << "Bo ba(i,j,k)"
         << setw(8)  << "Vi tri"
         << setw(12) << "So khop"
         << setw(18) << "Ket qua so khop"
         << setw(18) << "Dich cua so j"
         << "Cap nhat (i, k) cho buoc sau\n";

    i = ell;
    j = k = 0;

    // Vòng lặp chính quản lý dịch chuyển cửa sổ trên Text
    while (j <= n - m) {
        int startI = i; // Lưu lại giá trị i đầu cửa sổ để in log
        int startK = k; // Lưu lại giá trị k đầu cửa sổ để in log
        string compStr = "";
        string matchRes = "Mismatch";

        // Pha 1: So khớp vùng phải (Hậu tố) từ vị trí i
        while (i < m && pattern[i] == text[i + j]) {
            compStr += pattern[i];
            ++i;
        }

        // Kiểm tra nếu vùng phải khớp hoàn toàn
        if (i >= m) {
            // Pha 2: Quay lại kiểm tra vùng trái (Tiền tố) từ vị trí k
            while (k < ell && pattern[k] == text[j + k]) {
                ++k;
            }
            if (k >= ell) {
                matchRes = "TIM THAY MAU";
            } else {
                matchRes = "Loi vung trai";
            }
        } else {
            compStr += (pattern[i] + string("!=") + text[i + j]);
        }

        // Tính toán độ dịch j_shift và trạng thái kế tiếp
        int j_shift = i - kmpNext[i];
        int nextI = i;
        int nextK = k;

        if (i == ell) {
            nextK = max(0, k - 1);
        } else if (kmpNext[i] <= ell) {
            nextK = max(0, kmpNext[i]);
            nextI = ell;
        } else {
            nextK = ell;
            nextI = kmpNext[i];
        }

        // In thông tin chi tiết của bước hiện tại ra màn hình
        cout << left
             << setw(6)  << step++
             << ("(" + to_string(startI) + "," + to_string(j) + "," + to_string(startK) + ")")
             << setw(3)  << "" 
             << "y[" << setw(2) << (startI + j) << "]"
             << setw(3)  << ""
             << setw(12) << (i == startI ? string(1, pattern[i]) + "!=" + text[i+j] : compStr)
             << setw(18) << matchRes
             << "j += " << setw(11) << j_shift
             << "i=" << nextI << ", k=" << nextK << "\n";

        // Thực hiện dịch chuyển cửa sổ văn bản j
        j += j_shift;
        i = nextI;
        k = nextK;
    }
    cout << "---------------------------------------------------------\n";
}

int main() {
    string pattern, text;
    
    // Nhập dữ liệu chuỗi mẫu và chuỗi văn bản từ bàn phím
    cout << "Nhap chuoi mau (Pattern): ";
    cin >> pattern;
    cout << "Nhap chuoi van ban (Text): ";
    cin >> text;

    cout << "\n--- KET QUA TIM KIEM GOC ---" << endl;
    apostolicoCrochemore(pattern, text);
    
    // Gọi hàm in trace để phân tích tường tận từng bước chạy
    printStepAC(pattern, text);

    return 0;
}