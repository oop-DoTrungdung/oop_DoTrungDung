#include <iostream>
#include <string>

using namespace std;

class phuongtien {
private:
    int ma_xe;       
    string loai_xe;  
    int gio_vao;     
    int thoigian_do;       

public:
    phuongtien() { ma_xe = 0; loai_xe = ""; gio_vao = 0; thoigian_do = 0; }
    phuongtien(int ma, string loai, int gio, int tg) {
        ma_xe = ma; loai_xe = loai; gio_vao = gio; thoigian_do = tg;
    }

   
    int lay_ma_xe() const { return ma_xe; }
    string lay_loai_xe() const { return loai_xe; }

   
    double tinh_phi() const {
        if (loai_xe == "Car" || loai_xe == "car") return thoigian_do * 10000;
        return thoigian_do * 5000;
    }

    // Hiển thị thông tin xe
    void hien_thi() const {
        cout << "Ma xe: " << ma_xe << " | Loai: " << loai_xe
            << " | Gio vao: " << gio_vao << " | TG do: " << thoigian_do << "h"
            << " | Phi: " << tinh_phi() << " VND\n";
    }
};

class bai_xe {
private:
    int ma_bai;
    char kich_thuoc;
    phuongtien pt1, pt2, pt3;
    bool co1, co2, co3;

public:
    // Constructor
    bai_xe() { ma_bai = 0; kich_thuoc = 'S'; co1 = co2 = co3 = false; }
    bai_xe(int ma, char kt) { ma_bai = ma; kich_thuoc = kt; co1 = co2 = co3 = false; }

    int lay_ma() const { return ma_bai; }

    // Thêm xe vào bãi (tìm vị trí trống đầu tiên)
    bool them(phuongtien v) {
        if (!co1) { pt1 = v; co1 = true; return true; }
        if (!co2) { pt2 = v; co2 = true; return true; }
        if (!co3) { pt3 = v; co3 = true; return true; }
        return false; 
    }

    bool xoa(int ma_xe) {
        if (co1 && pt1.lay_ma_xe() == ma_xe) { co1 = false; return true; }
        if (co2 && pt2.lay_ma_xe() == ma_xe) { co2 = false; return true; }
        if (co3 && pt3.lay_ma_xe() == ma_xe) { co3 = false; return true; }
        return false; // 
    }

    bool chua(int ma_xe) const {
        if (co1 && pt1.lay_ma_xe() == ma_xe) return true;
        if (co2 && pt2.lay_ma_xe() == ma_xe) return true;
        if (co3 && pt3.lay_ma_xe() == ma_xe) return true;
        return false;
    }

    bool co_loai(string loai, int& dem, double& tong) const {
        dem = 0; tong = 0;
        if (co1 && pt1.lay_loai_xe() == loai) { dem++; tong += pt1.tinh_phi(); }
        if (co2 && pt2.lay_loai_xe() == loai) { dem++; tong += pt2.tinh_phi(); }
        if (co3 && pt3.lay_loai_xe() == loai) { dem++; tong += pt3.tinh_phi(); }
        return dem > 0;
    }

    void hien_thi() const {
        cout << "--- Bai xe ma: " << ma_bai << " | Kich thuoc: " << kich_thuoc << " ---\n";
        if (co1) { cout << "  [Slot 1] "; pt1.hien_thi(); }
        if (co2) { cout << "  [Slot 2] "; pt2.hien_thi(); }
        if (co3) { cout << "  [Slot 3] "; pt3.hien_thi(); }
        if (!co1 && !co2 && !co3) cout << "  (Bai xe dang trong)\n";
    }
};

class SystemInterface {
private:
    bai_xe bai1, bai2, bai3;
    bool co1, co2, co3; 

public:
    SystemInterface() {
        co1 = co2 = co3 = false;
    }

    void runMenu() {
        int choice;
        do {
            cout << "\nHệ thống quản lý\n";
            cout << "1. Tạo bãi xe\n";
            cout << "2. Thêm xe vào bãi\n";
            cout << "3. Xóa bãi xe\n";
            cout << "4. Lấy xe ra\n";
            cout << "5. Hiển thị toàn bộ hệ thống\n";
            cout << "0. Thoát chương trình\n";
            cout << "Chọn chức năng: ";
            cin >> choice;

            switch (choice) {
            case 1: { 
                int ma; char kt;
                cout << "Nhap ma bai xe: "; cin >> ma;
                cout << "Nhap kich thuoc (S/M/L): "; cin >> kt;

                if (!co1) { bai1 = bai_xe(ma, kt); co1 = true; cout << "Tạo bãi 1 thành công\n"; }
                else if (!co2) { bai2 = bai_xe(ma, kt); co2 = true; cout << "Tạo bãi 2 thành công\n"; }
                else if (!co3) { bai3 = bai_xe(ma, kt); co3 = true; cout << "Tạo bãi 3 thành công\n"; }
                else cout << "Hệ thống đã đầy (Tối đa 3 bãi)\n";
                break;
            }
            case 2: { 
                int mabai, maxe, gio, tg; string loai;
                cout << "Nhập mã bãi xe cần thêm vào: "; cin >> mabai;
                cout << "Nhập mã xe: "; cin >> maxe;
                cout << "Nhập loại xe (Car/Moto): "; cin >> loai;
                cout << "Nhập giờ vào (0-23): "; cin >> gio;
                cout << "Nhập thời gian đỗ (Giờ): "; cin >> tg;

                phuongtien pt(maxe, loai, gio, tg);
                bool added = false;

                if (co1 && bai1.lay_ma() == mabai) added = bai1.them(pt);
                else if (co2 && bai2.lay_ma() == mabai) added = bai2.them(pt);
                else if (co3 && bai3.lay_ma() == mabai) added = bai3.them(pt);

                if (added) cout << "Thêm xe vao bãi thành công!\n";
                else cout << "Lỗi. Không tìm thấy bãi xe hoặc bãi đã đầy!\n";
                break;
            }
            case 3: { 
                int mabai;
                cout << "Nhập mã bãi xe cần xóa: "; cin >> mabai;
                if (co1 && bai1.lay_ma() == mabai) { co1 = false; cout << "Đã xóa bãi 1.\n"; }
                else if (co2 && bai2.lay_ma() == mabai) { co2 = false; cout << "Đã xóa bãi 2.\n"; }
                else if (co3 && bai3.lay_ma() == mabai) { co3 = false; cout << "Đã xóa bãi 3.\n"; }
                else cout << "Không tìm thấy bãi xe này!\n";
                break;
            }
            case 4: { 
                int maxe;
                cout << "Nhập mã xe cần lấy ra: "; cin >> maxe;
                bool removed = false;
                if (co1) removed = bai1.xoa(maxe);
                if (!removed && co2) removed = bai2.xoa(maxe);
                if (!removed && co3) removed = bai3.xoa(maxe);

                if (removed) cout << "Đã lấy xe ra khỏi bãi\n";
                else cout << "Không tìm thấy xe trong hệ thống\n";
                break;
            }
            case 5: { // 5 hiển thị
                cout << "\nTình trạng hệ thống\n";
                if (co1) bai1.hien_thi();
                if (co2) bai2.hien_thi();
                if (co3) bai3.hien_thi();
                if (!co1 && !co2 && !co3) cout << "Hệ thống chưa có bãi xe nào\n";
                break;
            }
            case 0:
                cout << "Thoát chương trình\n";
                break;
            default:
                cout << "Lựa chọn không hợp lệ!\n";
            }
        } while (choice != 0);
    }
};
int main() {
    SystemInterface heThong;
    heThong.runMenu();
    return 0;
}