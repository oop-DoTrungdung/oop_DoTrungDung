#include <iostream>
#include <string>
#include <cctype>

using namespace std;

class phuong_tien {
private:
    int ma_xe;
    string loai_xe;
    int gio_vao;
    int tg_do;

public:
    phuong_tien() {
        ma_xe = 0;
        loai_xe = "";
        gio_vao = 0;
        tg_do = 0;
    }
    phuong_tien(int ma, string loai, int gio, int tg) {
        ma_xe = ma;
        loai_xe = loai;
        gio_vao = gio;
        tg_do = tg;
    }

    int lay_ma_xe() const { return ma_xe; }
    string lay_loai_xe() const { return loai_xe; }
    int lay_gio_vao() const { return gio_vao; }
    int lay_tg_do() const { return tg_do; }

    double tinh_phi() const {
        if (loai_xe == "Car" || loai_xe == "car") return tg_do * 10000.0;
        if (loai_xe == "Motorcycle" || loai_xe == "motorcycle" || loai_xe == "Moto") return tg_do * 5000.0;
        return tg_do * 2000.0;
    }

    void hien_thi() const {
        cout << "  -> Ma xe: " << ma_xe
            << " | Loai xe: " << loai_xe
            << " | Gio vao: " << gio_vao << "h"
            << " | Thoi gian do: " << tg_do << "h"
            << " | Phi do xe: " << tinh_phi() << " VND\n";
    }
};

class bai_xe {
private:
    int ma_bai;
    char kich_thuoc; 
    phuong_tien pt1, pt2, pt3;
    bool co1, co2, co3;

public:
    bai_xe() {
        ma_bai = 0;
        kich_thuoc = 'S';
        co1 = co2 = co3 = false;
    }

    bai_xe(int ma, char kt) {
        ma_bai = ma;
        kich_thuoc = kt;
        co1 = co2 = co3 = false;
    }

    int lay_ma() const { return ma_bai; }
    char lay_kich_thuoc() const { return kich_thuoc; }

    bool them(phuong_tien v);
    bool xoa(int ma_xe);
    bool chua(int ma_xe) const;
    void hien_thi() const;
    bool co_loai(string loai, int& dem, double& tong) const;

    void tinh_tong_bai(int& dem_xe, double& tong_phi) const {
        dem_xe = 0;
        tong_phi = 0;
        if (co1) { ++dem_xe; tong_phi += pt1.tinh_phi(); }
        if (co2) { ++dem_xe; tong_phi += pt2.tinh_phi(); }
        if (co3) { ++dem_xe; tong_phi += pt3.tinh_phi(); }
    }
};

bool bai_xe::them(phuong_tien v) {
    int cap = (kich_thuoc == 'S') ? 1 : (kich_thuoc == 'M') ? 2 : 3;
    if (cap >= 1 && !co1) { pt1 = v; co1 = true; return true; }
    if (cap >= 2 && !co2) { pt2 = v; co2 = true; return true; }
    if (cap >= 3 && !co3) { pt3 = v; co3 = true; return true; }
    return false;
}

bool bai_xe::xoa(int ma_xe) {
    if (co1 && pt1.lay_ma_xe() == ma_xe) {
        if (co2) {
            pt1 = pt2;
            if (co3) { pt2 = pt3; co3 = false; }
            else co2 = false;
        }
        else co1 = false;
        return true;
    }
    if (co2 && pt2.lay_ma_xe() == ma_xe) {
        if (co3) { pt2 = pt3; co3 = false; }
        else co2 = false;
        return true;
    }
    if (co3 && pt3.lay_ma_xe() == ma_xe) {
        co3 = false;
        return true;
    }
    return false;
}

bool bai_xe::chua(int ma_xe) const {
    if (co1 && pt1.lay_ma_xe() == ma_xe) return true;
    if (co2 && pt2.lay_ma_xe() == ma_xe) return true;
    if (co3 && pt3.lay_ma_xe() == ma_xe) return true;
    return false;
}

void bai_xe::hien_thi() const {
    int cap = (kich_thuoc == 'S') ? 1 : (kich_thuoc == 'M') ? 2 : 3;
    int so_xe = co1 + co2 + co3;
    cout << "Bai do " << ma_bai << " [" << kich_thuoc << "] "
        << so_xe << "/" << cap << " xe\n";
    if (co1) pt1.hien_thi();
    if (co2) pt2.hien_thi();
    if (co3) pt3.hien_thi();
}

bool bai_xe::co_loai(string loai, int& dem, double& tong) const {
    dem = 0; tong = 0;
    if (co1 && pt1.lay_loai_xe() == loai) { ++dem; tong += pt1.tinh_phi(); }
    if (co2 && pt2.lay_loai_xe() == loai) { ++dem; tong += pt2.tinh_phi(); }
    if (co3 && pt3.lay_loai_xe() == loai) { ++dem; tong += pt3.tinh_phi(); }
    return dem > 0;
}

class SystemInterface {
private:
    bai_xe bai1, bai2, bai3;
    bool co1, co2, co3;

public:
    SystemInterface() {
        co1 = co2 = co3 = false;
    }

    void runMenu();
};

void SystemInterface::runMenu() {
    int chon;
    while (true) {
        cout << "\n Quan ly bai do xe \n";
        cout << "1. Tao bai do\n";
        cout << "2. Them xe\n";
        cout << "3. Xoa bai do\n";
        cout << "4. Lay xe ra\n";
        cout << "5. Hien thi tat ca bai do\n";
        cout << "6. Hien thi xe theo bai\n";
        cout << "7. Liet ke xe theo loai\n";
        cout << "8. Bao cao phi trung binh\n";
        cout << "9. Thoat\n";
        cout << "Chon: ";
        cin >> chon;

        if (chon == 1) {
            int ma;
            char kt;
            cout << "Nhap ma bai do: ";
            cin >> ma;
            cout << "Nhap kich thuoc bai (S/M/L): ";
            cin >> kt;
            kt = toupper(kt);

            if (kt != 'S' && kt != 'M' && kt != 'L') {
                cout << "Loi: Kich thuoc chi duoc nhap S, M hoac L \n";
                continue;
            }

            if (!co1) {
                bai1 = bai_xe(ma, kt);
                co1 = true;
                cout << "Tao bai do " << ma << " thanh cong\n";
            }
            else if (!co2) {
                bai2 = bai_xe(ma, kt);
                co2 = true;
                cout << "Tao bai do " << ma << " thanh cong\n";
            }
            else if (!co3) {
                bai3 = bai_xe(ma, kt);
                co3 = true;
                cout << "Tao bai do " << ma << " thanh cong\n";
            }
            else {
                cout << "Loi: He thong da dat gioi han toi da 3 bai do\n";
            }
        }
        else if (chon == 2) {
            int ma_b, ma_x, gio, tg;
            string loai;
            cout << "Nhap ma bai do can them xe: ";
            cin >> ma_b;
            cout << "Nhap ma xe: ";
            cin >> ma_x;
            cout << "Nhap loai xe (Car/Motocycle/Bicycle): ";
            cin >> loai;
            cout << "Nhap gio vao (0..23): ";
            cin >> gio;
            cout << "Nhap thoi gian do (gio): ";
            cin >> tg;

            phuong_tien v(ma_x, loai, gio, tg);
            bool thanh_cong = false;

            if (co1 && bai1.lay_ma() == ma_b) thanh_cong = bai1.them(v);
            else if (co2 && bai2.lay_ma() == ma_b) thanh_cong = bai2.them(v);
            else if (co3 && bai3.lay_ma() == ma_b) thanh_cong = bai3.them(v);
            else {
                cout << "Loi: Khong tim thay bai do " << ma_b << "\n";
                continue;
            }

            if (thanh_cong) cout << "-> Them xe thanh cong vao bai " << ma_b << "\n";
            else cout << "Loi: Bai do da day hoac vuot qua suc chua cua kich thuoc bai\n";
        }
        else if (chon == 3) {
            int ma_b;
            cout << "Nhap ma bai do can xoa: ";
            cin >> ma_b;

            if (co1 && bai1.lay_ma() == ma_b) { co1 = false; cout << "-> Da xoa bai do " << ma_b << "\n"; }
            else if (co2 && bai2.lay_ma() == ma_b) { co2 = false; cout << "-> Da xoa bai do " << ma_b << "\n"; }
            else if (co3 && bai3.lay_ma() == ma_b) { co3 = false; cout << "-> Da xoa bai do " << ma_b << "\n"; }
            else cout << "Loi: Khong tim thay bai do " << ma_b << "\n";
        }
        else if (chon == 4) {
            int ma_x;
            cout << "Nhap ma xe can lay ra: ";
            cin >> ma_x;

            bool da_xoa = false;
            if (co1 && bai1.xoa(ma_x)) da_xoa = true;
            if (!da_xoa && co2 && bai2.xoa(ma_x)) da_xoa = true;
            if (!da_xoa && co3 && bai3.xoa(ma_x)) da_xoa = true;

            if (da_xoa) cout << "-> Da lay xe " << ma_x << " ra khoi bai va cap nhat lai vi tri\n";
            else cout << "Loi: Khong tim thay ma xe " << ma_x << " trong he thong\n";
        }
        else if (chon == 5) {
            cout << "\nDanh sach tat ca bai do\n";
            if (!co1 && !co2 && !co3) cout << "Chua co bai do nao trong he thong.\n";
            else {
                if (co1) bai1.hien_thi();
                if (co2) bai2.hien_thi();
                if (co3) bai3.hien_thi();
            }
        }
        else if (chon == 6) {
            int ma_b;
            cout << "Nhap ma bai do can xem: ";
            cin >> ma_b;

            bool tim_thay = false;
            if (co1 && bai1.lay_ma() == ma_b) { bai1.hien_thi(); tim_thay = true; }
            else if (co2 && bai2.lay_ma() == ma_b) { bai2.hien_thi(); tim_thay = true; }
            else if (co3 && bai3.lay_ma() == ma_b) { bai3.hien_thi(); tim_thay = true; }

            if (!tim_thay) cout << "Loi: Khong tim thay bai do " << ma_b << "\n";
        }
        else if (chon == 7) {
            string loai;
            cout << "Nhap loai xe can liet ke (Car/Motorcycle/Bicycle): ";
            cin >> loai;

            int tong_dem = 0;
            double tong_phi = 0;
            int dem = 0;
            double phi = 0;

            cout << "\nKet qua liet ke xe: " << loai << " \n";
            if (co1 && bai1.co_loai(loai, dem, phi)) { tong_dem += dem; tong_phi += phi; }
            if (co2 && bai2.co_loai(loai, dem, phi)) { tong_dem += dem; tong_phi += phi; }
            if (co3 && bai3.co_loai(loai, dem, phi)) { tong_dem += dem; tong_phi += phi; }

            if (tong_dem > 0) {
                cout << "Tong so xe loai " << loai << " trong he thong: " << tong_dem << " xe\n";
                cout << "Tong phi do xe loai " << loai << ": " << tong_phi << " VND\n";
            }
            else {
                cout << "Khong co xe loai " << loai << " trong he thong\n";
            }
        }
        else if (chon == 8) {
            int tong_xe = 0;
            double tong_phi = 0;
            int dem_b = 0;
            double phi_b = 0;

            if (co1) { bai1.tinh_tong_bai(dem_b, phi_b); tong_xe += dem_b; tong_phi += phi_b; }
            if (co2) { bai2.tinh_tong_bai(dem_b, phi_b); tong_xe += dem_b; tong_phi += phi_b; }
            if (co3) { bai3.tinh_tong_bai(dem_b, phi_b); tong_xe += dem_b; tong_phi += phi_b; }

            cout << "\nPhi trung binh\n";
            cout << "Tong so xe hien tai: " << tong_xe << " xe\n";
            cout << "Tong doanh thu phi do: " << tong_phi << " VND\n";
            if (tong_xe > 0) cout << "Phi trung binh moi xe: " << (tong_phi / tong_xe) << " VND/xe\n";
            else cout << "Chua co xe nao trong he thong de tinh phi trung binh.\n";
        }
        else if (chon == 9) {
            cout << "Thoat\n";
            break;
        }
        else {
            cout << "Lua chon lai\n";
        }
    }
}
int main() {
    SystemInterface heThong;
    heThong.runMenu();
    return 0;
}
