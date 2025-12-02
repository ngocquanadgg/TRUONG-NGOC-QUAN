#include <bits/stdc++.h>
#include <limits.h>
using namespace std;

// ====================== LỚP SINH VIÊN ======================
class SinhVien {
private:
    string maSV, tenSV, lop;
public:
    SinhVien() {}
    SinhVien(string ma, string ten, string l) : maSV(ma), tenSV(ten), lop(l) {}

    void Nhap() {
        cout << "Hãy nhập mã số sinh viên: "; getline(cin, maSV);
        cout << "Hãy nhập họ và tên sinh viên: "; getline(cin, tenSV);
        cout << "Hãy nhập lớp: "; getline(cin, lop);
    }

    void Xuat() const {
        cout << left << setw(10) << maSV << setw(25) << tenSV << setw(10) << lop << endl;
    }

    string getMaSV() const { return maSV; }
    string getTenSV() const { return tenSV; }

    void setTenSV(string ten) { tenSV = ten; }
    void setLop(string l) { lop = l; }

    string toFile() const {
        return maSV + "|" + tenSV + "|" + lop;
    }

    void fromFile(const string &line) {
        stringstream ss(line);
        getline(ss, maSV, '|');
        getline(ss, tenSV, '|');
        getline(ss, lop, '|');
    }
};

// ====================== LỚP MÔN HỌC ======================
class MonHoc {
private:
    string maMH, tenMH;
    int soTinChi;
public:
    MonHoc() {}
    MonHoc(string ma, string ten, int stc) : maMH(ma), tenMH(ten), soTinChi(stc) {}

    void Nhap() {
        cout << "Hãy nhập mã môn học: "; getline(cin, maMH);
        cout << "Hãy nhập tên môn học: "; getline(cin, tenMH);
        cout << "Hãy nhập số tín chỉ (là số nguyên): "; cin >> soTinChi;
        cin.ignore();
    }

    void Xuat() const {
        cout << left << setw(10) << maMH << setw(25) << tenMH << setw(10) << soTinChi << endl;
    }

    string getMaMH() const { return maMH; }
    void setTenMH(string ten) { tenMH = ten; }
    void setSoTinChi(int stc) { soTinChi = stc; }

    string toFile() const {
        return maMH + "|" + tenMH + "|" + to_string(soTinChi);
    }

    void fromFile(const string &line) {
        string stc;
        stringstream ss(line);
        getline(ss, maMH, '|');
        getline(ss, tenMH, '|');
        getline(ss, stc, '|');
        soTinChi = stoi(stc);
    }
};

// ====================== LỚP BẢNG ĐIỂM ======================
class BangDiem {
private:
    string maSV, maMH;
    float diemTX, diemThi, diemTB;
public:
    BangDiem() {}
    BangDiem(string sv, string mh, float tx, float thi)
        : maSV(sv), maMH(mh), diemTX(tx), diemThi(thi) { TinhDiemTB(); }

    void Nhap() {
        cout << "Hãy nhập mã số sinh viên: "; getline(cin, maSV);
        cout << "Hãy nhập mã môn học: "; getline(cin, maMH);
        cout << "Hãy nhập điểm thường xuyên (TX - thang 10): "; cin >> diemTX;
        cout << "Hãy nhập điểm thi (Thi - thang 10): "; cin >> diemThi;
        cin.ignore();
        TinhDiemTB();
    }

    void Xuat() const {
        cout << left << setw(10) << maSV << setw(10) << maMH
             << setw(10) << fixed << setprecision(2) << diemTX 
             << setw(10) << fixed << setprecision(2) << diemThi 
             << setw(10) << fixed << setprecision(2) << diemTB << endl;
    }

    // Công thức tính điểm trung bình: 30% TX + 70% Thi
    void TinhDiemTB() { diemTB = 0.3 * diemTX + 0.7 * diemThi; }

    string getMaSV() const { return maSV; }
    string getMaMH() const { return maMH; }

    void setDiem(float tx, float thi) {
        diemTX = tx; diemThi = thi; TinhDiemTB();
    }

    string toFile() const {
        return maSV + "|" + maMH + "|" + to_string(diemTX) + "|" + to_string(diemThi) + "|" + to_string(diemTB);
    }

    void fromFile(const string &line) {
        stringstream ss(line);
        string sTX, sThi, sTB;
        getline(ss, maSV, '|');
        getline(ss, maMH, '|');
        getline(ss, sTX, '|');
        getline(ss, sThi, '|');
        getline(ss, sTB, '|');
        diemTX = stof(sTX);
        diemThi = stof(sThi);
        diemTB = stof(sTB);
    }
};

// ====================== LỚP QUẢN LÝ ======================
class QuanLy {
private:
    vector<SinhVien> dsSV;
    vector<MonHoc> dsMH;
    vector<BangDiem> dsDiem;
public:
    // --- Sinh viên ---
    void ThemSV(const SinhVien &sv) { 
        if (TimSV(sv.getMaSV())) {
            cout << "Lỗi: Mã SV " << sv.getMaSV() << " đã tồn tại. Không thêm được!\n";
            return;
        }
        dsSV.push_back(sv); 
        cout << "Đã thêm sinh viên thành công!\n";
    }
    vector<SinhVien>& getSV() { return dsSV; }

    bool SuaSV(const string &ma, const string &ten, const string &lop) {
        for (auto &sv : dsSV)
            if (sv.getMaSV() == ma) { sv.setTenSV(ten); sv.setLop(lop); return true; }
        return false;
    }

    bool XoaSV(const string &ma) {
        auto it = remove_if(dsSV.begin(), dsSV.end(),
                             [&](SinhVien &s){ return s.getMaSV() == ma; });
        if (it != dsSV.end()) { 
            dsSV.erase(it, dsSV.end()); 
            dsDiem.erase(remove_if(dsDiem.begin(), dsDiem.end(),
                                   [&](BangDiem &d){ return d.getMaSV() == ma; }), dsDiem.end());
            return true; 
        }
        return false;
    }

    SinhVien* TimSV(const string &ma) {
        for (auto &sv : dsSV) if (sv.getMaSV() == ma) return &sv;
        return nullptr;
    }
    
    MonHoc* TimMH(const string &ma) {
        for (auto &mh : dsMH) if (mh.getMaMH() == ma) return &mh;
        return nullptr;
    }


    // --- Môn học ---
    void ThemMH(const MonHoc &mh) { 
        if (TimMH(mh.getMaMH())) {
            cout << "Lỗi: Mã MH " << mh.getMaMH() << " đã tồn tại. Không thêm được!\n";
            return;
        }
        dsMH.push_back(mh); 
        cout << "Đã thêm môn học thành công!\n";
    }
    vector<MonHoc>& getMH() { return dsMH; }

    // --- Bảng điểm ---
    void ThemDiem(const BangDiem &bd) { 
        if (!TimSV(bd.getMaSV())) {
            cout << "Lỗi: Mã SV " << bd.getMaSV() << " không tồn tại. Không thêm được điểm!\n";
            return;
        }
        if (!TimMH(bd.getMaMH())) {
            cout << "Lỗi: Mã MH " << bd.getMaMH() << " không tồn tại. Không thêm được điểm!\n";
            return;
        }
        
        for (const auto& d : dsDiem) {
            if (d.getMaSV() == bd.getMaSV() && d.getMaMH() == bd.getMaMH()) {
                cout << "Lỗi: Sinh viên " << bd.getMaSV() << " đã có điểm cho môn " << bd.getMaMH() << ". Hãy dùng chức năng Sửa điểm.\n";
                return;
            }
        }

        dsDiem.push_back(bd); 
        cout << "Đã thêm điểm thành công!\n";
    }
    vector<BangDiem>& getDiem() { return dsDiem; }

    bool SuaDiem(const string &sv, const string &mh, float tx, float thi) {
        for (auto &d : dsDiem)
            if (d.getMaSV() == sv && d.getMaMH() == mh) {
                d.setDiem(tx, thi); return true;
            }
        return false;
    }

    bool XoaDiem(const string &sv, const string &mh) {
        auto it = remove_if(dsDiem.begin(), dsDiem.end(),
                             [&](BangDiem &d){ return d.getMaSV() == sv && d.getMaMH() == mh; });
        if (it != dsDiem.end()) { dsDiem.erase(it, dsDiem.end()); return true; }
        return false;
    }

    // --- Lưu/Đọc file ---
    void LuuFile() {
        ofstream f1("SinhVien.txt"), f2("MonHoc.txt"), f3("BangDiem.txt");
        if (f1.is_open() && f2.is_open() && f3.is_open()) {
            for (auto &sv : dsSV) f1 << sv.toFile() << endl;
            for (auto &mh : dsMH) f2 << mh.toFile() << endl;
            for (auto &d : dsDiem) f3 << d.toFile() << endl;
            f1.close(); f2.close(); f3.close();
            cout << "Đã lưu dữ liệu vào các file SinhVien.txt, MonHoc.txt, BangDiem.txt!\n";
        } else {
             cout << "Lỗi: Không thể mở file để lưu dữ liệu!\n";
        }
    }

    void DocFile() {
        dsSV.clear(); dsMH.clear(); dsDiem.clear();
        ifstream f1("SinhVien.txt"), f2("MonHoc.txt"), f3("BangDiem.txt");
        string line;
        while (getline(f1, line)) { SinhVien s; s.fromFile(line); dsSV.push_back(s); }
        while (getline(f2, line)) { MonHoc m; m.fromFile(line); dsMH.push_back(m); }
        while (getline(f3, line)) { BangDiem d; d.fromFile(line); dsDiem.push_back(d); }
        
        if (!f1.is_open() && !f2.is_open() && !f3.is_open()) {
            cout << "Chú ý: Các file dữ liệu (SinhVien.txt,...) chưa tồn tại hoặc không mở được. Dữ liệu quản lý là rỗng.\n";
        }
        f1.close(); f2.close(); f3.close();
    }
};

// ====================== HÀM MAIN ======================
int main() {
    QuanLy ql;
    ql.DocFile();
    int ch;
    do {
        cout << "\n==============================\n";
        cout << "===== MENU QUẢN LÝ ĐIỂM SINH VIÊN =====\n";
        cout << "==============================\n";
        cout << "  SINH VIÊN\n";
        cout << "  1. Thêm sinh viên\n  2. Xuất danh sách sinh viên\n  3. Sửa thông tin sinh viên\n  4. Xóa sinh viên\n  5. Tìm kiếm sinh viên theo mã\n";
        cout << "  MÔN HỌC\n";
        cout << "  6. Thêm môn học\n  7. Xuất danh sách môn học\n";
        cout << "  BẢNG ĐIỂM\n";
        cout << "  8. Thêm điểm cho sinh viên\n  9. Xuất bảng điểm chi tiết\n  10. Sửa điểm của sinh viên\n  11. Xóa điểm của sinh viên\n";
        cout << "  QUẢN LÝ FILE\n";
        cout << "  12. Lưu dữ liệu vào file\n  13. Đọc dữ liệu từ file\n";
        cout << "  0. Thoát chương trình\n";
        cout << "==============================\n";
        cout << "Hãy chọn chức năng (0-13): ";

        if (!(cin >> ch)) {
            cout << "Lỗi nhập liệu! Vui lòng nhập một số nguyên.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            ch = -1;
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch(ch) {
            case 1: {
                cout << "\n--- THÊM SINH VIÊN ---\n";
                SinhVien sv; sv.Nhap(); ql.ThemSV(sv); break;
            }
            case 2: {
                cout << "\n--- DANH SÁCH SINH VIÊN ---\n";
                cout << left << setw(10) << "MA SV" << setw(25) << "TEN SINH VIEN" << setw(10) << "LOP" << endl;
                cout << "------------------------------------------------\n";
                if (ql.getSV().empty()) { cout << "Danh sách sinh viên rỗng.\n"; }
                for (auto &sv : ql.getSV()) sv.Xuat();
                break;
            }
            case 3: {
                cout << "\n--- SỬA THÔNG TIN SINH VIÊN ---\n";
                string ma, ten, lop;
                cout << "Nhập mã SV cần sửa: "; getline(cin, ma);
                cout << "Nhập tên mới cho SV: "; getline(cin, ten);
                cout << "Nhập lớp mới cho SV: "; getline(cin, lop);
                cout << (ql.SuaSV(ma, ten, lop) ? "Đã sửa thông tin sinh viên có mã " + ma + "!\n" : "Không tìm thấy sinh viên có mã " + ma + " để sửa!\n");
                break;
            }
            case 4: {
                cout << "\n--- XÓA SINH VIÊN ---\n";
                string ma; cout << "Nhập mã SV cần xóa: "; getline(cin, ma);
                cout << (ql.XoaSV(ma) ? "Đã xóa sinh viên có mã " + ma + " và tất cả điểm liên quan!\n" : "Không tìm thấy sinh viên có mã " + ma + " để xóa!\n");
                break;
            }
            case 5: {
                cout << "\n--- TÌM SINH VIÊN ---\n";
                string ma; cout << "Nhập mã SV cần tìm: "; getline(cin, ma);
                SinhVien *sv = ql.TimSV(ma);
                if (sv) {
                    cout << "\n--- KẾT QUẢ TÌM KIẾM ---\n";
                    cout << left << setw(10) << "MA SV" << setw(25) << "TEN SINH VIEN" << setw(10) << "LOP" << endl;
                    sv->Xuat();
                } else {
                    cout << "Không tìm thấy sinh viên có mã " << ma << "!\n";
                }
                break;
            }
            case 6: {
                cout << "\n--- THÊM MÔN HỌC ---\n";
                MonHoc mh; mh.Nhap(); ql.ThemMH(mh); break;
            }
            case 7: {
                cout << "\n--- DANH SÁCH MÔN HỌC ---\n";
                cout << left << setw(10) << "MA MH" << setw(25) << "TEN MON HOC" << setw(10) << "SO TC" << endl;
                cout << "------------------------------------------------\n";
                if (ql.getMH().empty()) { cout << "Danh sách môn học rỗng.\n"; }
                for (auto &mh : ql.getMH()) mh.Xuat();
                break;
            }
            case 8: {
                cout << "\n--- THÊM ĐIỂM ---\n";
                BangDiem bd; bd.Nhap(); ql.ThemDiem(bd); break;
            }
            case 9: {
                cout << "\n--- BẢNG ĐIỂM CHI TIẾT ---\n";
                cout << left << setw(10) << "MA SV" << setw(10) << "MA MH" << setw(10) << "DIEM TX" << setw(10) << "DIEM THI" << setw(10) << "DIEM TB" << endl;
                cout << "--------------------------------------------------------\n";
                 if (ql.getDiem().empty()) { cout << "Bảng điểm rỗng.\n"; }
                for (auto &d : ql.getDiem()) d.Xuat();
                break;
            }
            case 10: {
                cout << "\n--- SỬA ĐIỂM ---\n";
                string sv, mh; float tx, thi;
                cout << "Nhập mã SV có điểm cần sửa: "; getline(cin, sv);
                cout << "Nhập mã MH có điểm cần sửa: "; getline(cin, mh);
                cout << "Nhập điểm TX mới: "; cin >> tx;
                cout << "Nhập điểm Thi mới: "; cin >> thi; cin.ignore();
                cout << (ql.SuaDiem(sv, mh, tx, thi) ? "Đã sửa điểm cho SV " + sv + " môn " + mh + "!\n" : "Không tìm thấy điểm để sửa!\n");
                break;
            }
            case 11: {
                cout << "\n--- XÓA ĐIỂM ---\n";
                string sv, mh;
                cout << "Nhập mã SV có điểm cần xóa: "; getline(cin, sv);
                cout << "Nhập mã MH có điểm cần xóa: "; getline(cin, mh);
                cout << (ql.XoaDiem(sv, mh) ? "Đã xóa điểm cho SV " + sv + " môn " + mh + "!\n" : "Không tìm thấy điểm để xóa!\n");
                break;
            }
            case 12: ql.LuuFile(); break;
            case 13: ql.DocFile(); break;
            case 0: cout << "Đang thoát chương trình. Tạm biệt!\n"; break;
            default: cout << "Lựa chọn không hợp lệ. Vui lòng chọn lại.\n";
        }
    } while(ch != 0);
    return 0;
}