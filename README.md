# Chuyên đề CNPM: Thuật toán đối sánh mẫu

## 1. Giới thiệu

Repo này chứa mã nguồn và tài liệu liên quan đến chuyên đề **thuật toán tìm kiếm chuỗi (String Matching Algorithms)**.  
Mục tiêu là cài đặt, phân loại và kiểm nghiệm hiệu năng các thuật toán.



## 2. Cấu trúc thư mục

- BAI TAP: Source code C++ các thuật toán  
- TAI LIEU: Tài liệu tham khảo chính  
- BAO CAO: Báo cáo + file phân loại và kiểm nghiệm (PDF)

## 3. Phân loại 35 thuật toán theo nhóm

| Nhóm | Thuật toán |
|------|------------|
| LTR - Left to Right (Trái sang phải) | <ul><li>Brute-force</li><li>Karp and Rabin</li><li>Shift-Or</li><li>Morris-Pratt</li><li>Knuth-Morris-Pratt</li><li>Simon</li><li>Deterministic Finite Automation</li><li>Forward Dawg Matching</li><li>Apostolico-Crochemore</li><li>Not So Naive</li></ul> |
| RTL - Right to Left (Phải sang trái) | <ul><li>Boyer-Moore</li><li>Apostolico-Giancarlo</li><li>Turbo Boyer-Moore</li><li>Reverse Colussi</li><li>Reverse Factor</li><li>Turbo Reverse Factor</li><li>Backward Oracle</li><li>Zhu-Takaoka</li><li>Berry-Ravindran</li><li>BNDM</li></ul> |
| SPE - Specific Order (Theo thứ tự xác định) | <ul><li>Galil-Seiferas</li><li>Two-way</li><li>Colussi</li><li>Galil-Giancarlo</li><li>Sunday Optimal Mismatch</li><li>Maximal Shift</li><li>Skip Search</li><li>KMP Skip Search</li><li>Alpha Skip Search</li><li>String Matching on Ordered Alphabets</li></ul> |
| ANY - Any Position (Bất kỳ vị trí) | <ul><li>Horspool</li><li>Quick Search</li><li>Tuned Boyer-Moore</li><li>Smith</li><li>Raita</li></ul> |

## 4. Các thuật toán được chọn để nghiên cứu

Các thuật toán trong repo được lựa chọn từ danh sách 35 thuật toán ban đầu, nhằm phục vụ việc cài đặt và kiểm nghiệm thuật toán.

Nhóm 20 thuật toán được chọn gồm:

| Nhóm | Thuật toán |
|------|------------|
| LTR | <ul><li>Karp and Rabin</li><li>Shift-Or</li><li>Morris-Pratt</li><li>Knuth-Morris-Pratt</li><li>Apostolico-Crochemore</li><li>Not So Naive</li></ul> |
| RTL | <ul><li>Boyer-Moore</li><li>Apostolico-Giancarlo</li><li>Turbo Boyer-Moore</li><li>Zhu-Takaoka</li><li>Berry-Ravindran</li></ul> |
| SPE | <ul><li>Two-way</li><li>Sunday Optimal Mismatch</li><li>Maximal Shift</li><li>Skip Search</li><li>KMP Skip Search</li></ul> |
| ANY | <ul><li>Horspool</li><li>Quick Search</li><li>Tuned Boyer-Moore</li><li>Smith</li><li>Raita</li></ul> |


## 5. Báo cáo

- Báo cáo chuyên đề (PDF)
- Bảng phân loại thuật toán
- File kiểm nghiệm thực nghiệm (PDF)