#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int ASIZE = 256;

// Node của linked list
struct Node {
    int element; // Vị trí trong pattern
    Node* next; 
};

// Thuật toán SKIP
void skipSearch(string pattern, string text) {
    int m = pattern.length(), n = text.length();
    vector<Node*> z(ASIZE, nullptr);

    for (int i = 0; i < m; ++i) {
        Node* ptr = new Node;

        ptr->element = i;
        ptr->next = z[(unsigned char)pattern[i]];

        z[(unsigned char)pattern[i]] = ptr;
    }

    // Duyệt text theo bước nhảy m
    for (int j = m - 1; j < n; j += m) {
        // Lấy linked list tương ứng ký tự cuối
        Node* ptr = z[(unsigned char)text[j]];

        while (ptr != nullptr) {
            int start = j - ptr->element; // Vị trí bắt đầu cần kiểm tra

            if (start >= 0 && start <= n - m) {
                if (text.substr(start, m) == pattern) 
                    cout << "Match at position: "<< start << endl;
            }
            ptr = ptr->next;
        }
    }

    // Giải phóng linked list
    for (int i = 0; i < ASIZE; ++i) {
        Node* ptr = z[i];

        while (ptr != nullptr) {
            Node* temp = ptr;
            ptr = ptr->next;
            delete temp;
        }
    }
}

int main() {
    string pattern, text;

    cin >> pattern >> text;

    skipSearch(pattern, text);

    return 0;
}