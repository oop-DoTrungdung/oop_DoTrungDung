#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;


class Vehicle {
private:
    int vehicleID;
    string vehicleType;   
    int entryTime;        
    int parkingDuration;  
    double parkingFee;    

public:
    Vehicle() {
        vehicleID = 0;
        vehicleType = "";
        entryTime = 0;
        parkingDuration = 0;
        parkingFee = 0.0;
    }

    Vehicle(int id, const string& type, int entry, int duration) {
        vehicleID = id;
        vehicleType = type;
        entryTime = entry;
        parkingDuration = duration;
        calculateFee();
    }

    int getVehicleID() const { return vehicleID; }
    const string& getVehicleType() const { return vehicleType; }
    int getEntryTime() const { return entryTime; }
    int getParkingDuration() const { return parkingDuration; }
    double getParkingFee() const { return parkingFee; }

    void setVehicleID(int id) { vehicleID = id; }
    void setVehicleType(const string& type) {
        vehicleType = type;
        calculateFee();
    }
    void setEntryTime(int entry) { entryTime = entry; }
    void setParkingDuration(int duration) {
        parkingDuration = duration;
        calculateFee();
    }

    void calculateFee() {
        if (vehicleType == "Car") {
            parkingFee = parkingDuration * 10000.0;
        } else if (vehicleType == "Motorcycle") {
            parkingFee = parkingDuration * 5000.0;
        } else if (vehicleType == "Bicycle") {
            parkingFee = parkingDuration * 2000.0;
        } else {
            parkingFee = 0.0;
        }
    }

    void display() const {
        cout << "   -> Ma xe: " << vehicleID
             << " | Loai: " << vehicleType
             << " | Gio vao: " << entryTime << "h"
             << " | Thoi gian do: " << parkingDuration << "h"
             << " | Phi: " << parkingFee << " VND\n";
    }
};

class ParkingLot {
private:
    int parkID;
    char size;               
    int capacity;            
    int currentVehicleCount;
    Vehicle** vehicles;      

    int getInitialCapacity(char s) const {
        if (s == 'S') return 1;
        if (s == 'M') return 2;
        return 3; 
    }

    void clearVehicles() {
        if (vehicles != nullptr) {
            for (int i = 0; i < currentVehicleCount; ++i) {
                if (vehicles[i] != nullptr) {
                    delete vehicles[i];
                    vehicles[i] = nullptr;
                }
            }
            delete[] vehicles;
            vehicles = nullptr;
        }
    }

public:
    ParkingLot() {
        parkID = 0;
        size = 'S';
        capacity = 1;
        currentVehicleCount = 0;
        vehicles = new Vehicle*[capacity];
        vehicles[0] = nullptr;
    }
    ParkingLot(int id, char s) {
        parkID = id;
        size = static_cast<char>(toupper(s));
        capacity = getInitialCapacity(size);
        currentVehicleCount = 0;
        vehicles = new Vehicle*[capacity];
        for (int i = 0; i < capacity; ++i) {
            vehicles[i] = nullptr;
        }
    }

    ~ParkingLot() {
        clearVehicles();
    }

    ParkingLot(const ParkingLot& other) {
        parkID = other.parkID;
        size = other.size;
        capacity = other.capacity;
        currentVehicleCount = other.currentVehicleCount;

        vehicles = new Vehicle*[capacity];
        for (int i = 0; i < capacity; ++i) {
            if (i < currentVehicleCount && other.vehicles[i] != nullptr) {
                vehicles[i] = new Vehicle(*other.vehicles[i]);
            } else {
                vehicles[i] = nullptr;
            }
        }
    }


    ParkingLot& operator=(const ParkingLot& other) {
        if (this == &other) {
            return *this;
        }

        clearVehicles();

        parkID = other.parkID;
        size = other.size;
        capacity = other.capacity;
        currentVehicleCount = other.currentVehicleCount;

        vehicles = new Vehicle*[capacity];
        for (int i = 0; i < capacity; ++i) {
            if (i < currentVehicleCount && other.vehicles[i] != nullptr) {
                vehicles[i] = new Vehicle(*other.vehicles[i]);
            } else {
                vehicles[i] = nullptr;
            }
        }
        return *this;
    }

    int getParkID() const { return parkID; }
    char getSize() const { return size; }
    int getCapacity() const { return capacity; }
    int getCurrentVehicleCount() const { return currentVehicleCount; }
    const Vehicle* getVehicleAt(int index) const {
        if (index < 0 || index >= currentVehicleCount) return nullptr;
        return vehicles[index];
    }

    void resize(int newCapacity) {
        if (newCapacity <= capacity) return;

        Vehicle** newVehicles = new Vehicle*[newCapacity];
        for (int i = 0; i < newCapacity; ++i) {
            if (i < currentVehicleCount) {
                newVehicles[i] = vehicles[i];
            } else {
                newVehicles[i] = nullptr;
            }
        }

        delete[] vehicles;
        vehicles = newVehicles;
        capacity = newCapacity;
    }

    bool addVehicle(const Vehicle& v) {
        if (currentVehicleCount == capacity) {
            int newCap = (capacity > 0) ? (capacity * 2) : 1;
            cout << "   [Thong bao] Bai " << parkID << " da day (" << capacity
                 << " cho). Tu dong mo rong suc chua len " << newCap << " cho!\n";
            resize(newCap);
        }

        vehicles[currentVehicleCount] = new Vehicle(v);
        currentVehicleCount++;
        return true;
    }

    int findVehicleIndex(int vID) const {
        for (int i = 0; i < currentVehicleCount; ++i) {
            if (vehicles[i] != nullptr && vehicles[i]->getVehicleID() == vID) {
                return i;
            }
        }
        return -1;
    }

    bool removeVehicle(int vID) {
        int idx = findVehicleIndex(vID);
        if (idx == -1) return false;

        delete vehicles[idx];
        vehicles[idx] = nullptr;
        for (int i = idx; i < currentVehicleCount - 1; ++i) {
            vehicles[i] = vehicles[i + 1];
        }
        vehicles[currentVehicleCount - 1] = nullptr;
        currentVehicleCount--;
        return true;
    }
    void displayLotInfo() const {
        cout << "Bai do " << parkID << " [Size: " << size << "] - Tinh trang: "
             << currentVehicleCount << "/" << capacity << " xe\n";
        if (currentVehicleCount == 0) {
            cout << "   (Bai do dang trong)\n";
        } else {
            for (int i = 0; i < currentVehicleCount; ++i) {
                if (vehicles[i] != nullptr) {
                    vehicles[i]->display();
                }
            }
        }
    }
};

class SystemInterface {
private:
    int lotCapacity;          
    int currentLotCount;     
    ParkingLot** parkingLots; 

    void clearLots() {
        if (parkingLots != nullptr) {
            for (int i = 0; i < currentLotCount; ++i) {
                if (parkingLots[i] != nullptr) {
                    delete parkingLots[i];
                    parkingLots[i] = nullptr;
                }
            }
            delete[] parkingLots;
            parkingLots = nullptr;
        }
    }
    int inputInt(const string& prompt) {
        int val;
        while (true) {
            cout << prompt;
            cin >> val;
            if (cin.fail()) {
                cout << "Loi nhap lieu: Vui long chi nhap so nguyen!\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } else {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return val;
            }
        }
    }
    int inputIntInRange(const string& prompt, int minVal, int maxVal) {
        int val;
        while (true) {
            val = inputInt(prompt);
            if (val >= minVal && val <= maxVal) {
                return val;
            }
            cout << "Loi: Gia tri phai nam trong khoang [" << minVal << ".." << maxVal << "]!\n";
        }
    }
    char inputLotSize() {
        char s;
        while (true) {
            cout << "Nhap kich thuoc bai (S / M / L): ";
            cin >> s;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            s = static_cast<char>(toupper(s));
            if (s == 'S' || s == 'M' || s == 'L') {
                return s;
            }
            cout << "Loi: Kich thuoc chi duoc chon S, M hoac L!\n";
        }
    }
    string normalizeType(string raw) {
        if (raw.empty()) return "";
        for (size_t i = 0; i < raw.length(); ++i) {
            raw[i] = static_cast<char>(tolower(raw[i]));
        }
        raw[0] = static_cast<char>(toupper(raw[0]));
        return raw;
    }
    string inputVehicleType() {
        string raw;
        while (true) {
            cout << "Nhap loai xe (Car / Motorcycle / Bicycle): ";
            cin >> raw;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            string type = normalizeType(raw);
            if (type == "Car" || type == "Motorcycle" || type == "Bicycle") {
                return type;
            }
            cout << "Loi: Loai xe chi duoc nhap Car, Motorcycle hoac Bicycle!\n";
        }
    }
public:
    SystemInterface() {
        lotCapacity = 5;
        currentLotCount = 0;
        parkingLots = new ParkingLot*[lotCapacity];
        for (int i = 0; i < lotCapacity; ++i) {
            parkingLots[i] = nullptr;
        }
    }
    ~SystemInterface() {
        clearLots();
    }
    SystemInterface(const SystemInterface& other) {
        lotCapacity = other.lotCapacity;
        currentLotCount = other.currentLotCount;

        parkingLots = new ParkingLot*[lotCapacity];
        for (int i = 0; i < lotCapacity; ++i) {
            if (i < currentLotCount && other.parkingLots[i] != nullptr) {
                parkingLots[i] = new ParkingLot(*other.parkingLots[i]);
            } else {
                parkingLots[i] = nullptr;
            }
        }
    }
    SystemInterface& operator=(const SystemInterface& other) {
        if (this == &other) {
            return *this;
        }
        clearLots();
        lotCapacity = other.lotCapacity;
        currentLotCount = other.currentLotCount;

        parkingLots = new ParkingLot*[lotCapacity];
        for (int i = 0; i < lotCapacity; ++i) {
            if (i < currentLotCount && other.parkingLots[i] != nullptr) {
                parkingLots[i] = new ParkingLot(*other.parkingLots[i]);
            } else {
                parkingLots[i] = nullptr;
            }
        }
        return *this;
    }
    void resizeSystem(int newCapacity) {
        if (newCapacity <= lotCapacity) return;

        ParkingLot** newLots = new ParkingLot*[newCapacity];
        for (int i = 0; i < newCapacity; ++i) {
            if (i < currentLotCount) {
                newLots[i] = parkingLots[i];
            } else {
                newLots[i] = nullptr;
            }
        }

        delete[] parkingLots;
        parkingLots = newLots;
        lotCapacity = newCapacity;
    }
    bool isParkIDExists(int pID) const {
        for (int i = 0; i < currentLotCount; ++i) {
            if (parkingLots[i] != nullptr && parkingLots[i]->getParkID() == pID) {
                return true;
            }
        }
        return false;
    }
    bool isVehicleIDExists(int vID) const {
        for (int i = 0; i < currentLotCount; ++i) {
            if (parkingLots[i] != nullptr && parkingLots[i]->findVehicleIndex(vID) != -1) {
                return true;
            }
        }
        return false;
    }
    int generateRandomID() {
        return 1000 + rand() % 9000;
    }
    void runMenu() {
        int chon;
        while (true) {
            cout << "\n===== QUAN LY BAI DO XE (GIAI DOAN 3 - DYNAMIC MEMORY) =====\n";
            cout << "1. Tao Bai do xe moi\n";
            cout << "2. Them xe vao bai do\n";
            cout << "3. Xoa mot Bai do xe\n";
            cout << "4. Lay xe ra khoi bai do\n";
            cout << "5. Hien thi danh sach tat ca cac Bai do xe\n";
            cout << "6. Hien thi danh sach xe theo bai cu the\n";
            cout << "7. Liet ke xe theo loai phuong tien\n";
            cout << "8. Tom tat phi do xe trung binh\n";
            cout << "9. Thoat chuong trinh\n";
            chon = inputInt("Chon chuc nang (1-9): ");

            if (chon == 1) { 
                if (currentLotCount == lotCapacity) {
                    int newCap = lotCapacity * 2;
                    cout << "[Thong bao] Danh sach bai do da day (" << lotCapacity
                         << " bai). Tu dong mo rong he thong len " << newCap << " bai!\n";
                    resizeSystem(newCap);
                }

                int pID = inputInt("Nhap ma bai do (parkID): ");
                if (isParkIDExists(pID)) {
                    int newID;
                    do {
                        newID = generateRandomID();
                    } while (isParkIDExists(newID));
                    cout << "Canh bao: Ma bai " << pID << " da ton tai! Tu dong gan ma ngau nhien moi: " << newID << "\n";
                    pID = newID;
                }

                char s = inputLotSize();
                parkingLots[currentLotCount] = new ParkingLot(pID, s);
                currentLotCount++;
                cout << "-> Tao bai do " << pID << " (Size " << s << ") thanh cong!\n";
            }
            else if (chon == 2) { 
                if (currentLotCount == 0) {
                    cout << "Canh bao: Chua co bai do nao trong he thong. Hay tao bai do truoc!\n";
                    continue;
                }

                cout << "Cac ma bai do hien co: ";
                for (int i = 0; i < currentLotCount; ++i) {
                    if (parkingLots[i] != nullptr) {
                        cout << parkingLots[i]->getParkID() << " ";
                    }
                }
                cout << "\n";
                int targetParkID = inputInt("Nhap ma bai do muon gui xe: ");
                int lotIdx = -1;
                for (int i = 0; i < currentLotCount; ++i) {
                    if (parkingLots[i] != nullptr && parkingLots[i]->getParkID() == targetParkID) {
                        lotIdx = i;
                        break;
                    }
                }
                if (lotIdx == -1) {
                    cout << "Loi: Khong tim thay bai do co ma " << targetParkID << "!\n";
                    continue;
                }
                int vID = inputInt("Nhap ma xe (vehicleID): ");
                if (isVehicleIDExists(vID)) {
                    int newID;
                    do {
                        newID = generateRandomID();
                    } while (isVehicleIDExists(newID));
                    cout << "Canh bao: Ma xe " << vID << " da ton tai! Tu dong gan ma ngau nhien moi: " << newID << "\n";
                    vID = newID;
                }
                string vType = inputVehicleType();
                int entry = inputIntInRange("Nhap gio vao (0..23): ", 0, 23);
                int duration = inputIntInRange("Nhap thoi gian do (1..23 gio): ", 1, 23);

                Vehicle v(vID, vType, entry, duration);
                if (parkingLots[lotIdx]->addVehicle(v)) {
                    cout << "-> Da them xe " << vID << " vao bai do " << targetParkID << "!\n";
                }
            }
            else if (chon == 3) { 
                if (currentLotCount == 0) {
                    cout << "He thong chua co bai do nao de xoa!\n";
                    continue;
                }
                int pID = inputInt("Nhap ma bai do can xoa: ");
                int idx = -1;
                for (int i = 0; i < currentLotCount; ++i) {
                    if (parkingLots[i] != nullptr && parkingLots[i]->getParkID() == pID) {
                        idx = i;
                        break;
                    }
                }
                if (idx == -1) {
                    cout << "Loi: Khong tim thay bai do co ma " << pID << "!\n";
                } else {
                    delete parkingLots[idx];
                    parkingLots[idx] = nullptr;

                    for (int i = idx; i < currentLotCount - 1; ++i) {
                        parkingLots[i] = parkingLots[i + 1];
                    }
                    parkingLots[currentLotCount - 1] = nullptr;
                    currentLotCount--;
                    cout << "-> Da giai phong bo nho bai do " << pID << " va don danh sach!\n";
                }
            }
            else if (chon == 4) { 
                if (currentLotCount == 0) {
                    cout << "He thong chua co bai do nao!\n";
                    continue;
                }
                int vID = inputInt("Nhap ma xe can lay ra: ");
                bool removed = false;
                for (int i = 0; i < currentLotCount; ++i) {
                    if (parkingLots[i] != nullptr && parkingLots[i]->removeVehicle(vID)) {
                        cout << "-> Da lay xe " << vID << " ra khoi bai " << parkingLots[i]->getParkID()
                             << ", thu hoi bo nho va don vi tri!\n";
                        removed = true;
                        break;
                    }
                }
                if (!removed) {
                    cout << "Loi: Khong tim thay xe co ma " << vID << " trong toan he thong!\n";
                }
            }
            else if (chon == 5) { 
                cout << "\n--- DANH SACH TAT CA CAC BAI DO (Dang dung: " << currentLotCount
                     << " | Suc chua he thong: " << lotCapacity << ") ---\n";
                if (currentLotCount == 0) {
                    cout << "He thong chua co bai do nao.\n";
                } else {
                    for (int i = 0; i < lotCapacity; ++i) {
                        if (parkingLots[i] != nullptr) {
                            parkingLots[i]->displayLotInfo();
                        }
                    }
                }
            }
            else if (chon == 6) { 
                int pID = inputInt("Nhap ma bai do can xem chi tiet: ");
                bool found = false;

                for (int i = 0; i < currentLotCount; ++i) {
                    if (parkingLots[i] != nullptr && parkingLots[i]->getParkID() == pID) {
                        cout << "\n--- CHI TIET BAI DO " << pID << " ---\n";
                        parkingLots[i]->displayLotInfo();
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    cout << "Loi: Khong tim thay bai do co ma " << pID << "!\n";
                }
            }
            else if (chon == 7) { 
                string targetType = inputVehicleType();
                int count = 0;
                cout << "\n--- DANH SACH XE LOAI: " << targetType << " ---\n";
                for (int i = 0; i < currentLotCount; ++i) {
                    if (parkingLots[i] == nullptr) continue;
                    int vCount = parkingLots[i]->getCurrentVehicleCount();
                    for (int j = 0; j < vCount; ++j) {
                        const Vehicle* v = parkingLots[i]->getVehicleAt(j);
                        if (v != nullptr && v->getVehicleType() == targetType) {
                            cout << "[Bai " << parkingLots[i]->getParkID() << "] ";
                            v->display();
                            count++;
                        }
                    }
                }
                if (count == 0) {
                    cout << "Khong co xe loai " << targetType << " nao trong he thong.\n";
                } else {
                    cout << "=> Tong cong: " << count << " xe loai " << targetType << ".\n";
                }
            }
            else if (chon == 8) { 
                if (currentLotCount == 0) {
                    cout << "Chua co du lieu bai do de thong ke.\n";
                    continue;
                }
                string types[3] = {"Car", "Motorcycle", "Bicycle"};
                int sysCount[3] = {0, 0, 0};
                double sysFee[3] = {0.0, 0.0, 0.0};
                cout << "\n=== BAO CAO PHI DO XE TRUNG BINH ===\n";
                cout << "1. Phan chia theo tung bai do:\n";
                for (int i = 0; i < currentLotCount; ++i) {
                    if (parkingLots[i] == nullptr) continue;
                    int lotCount[3] = {0, 0, 0};
                    double lotFee[3] = {0.0, 0.0, 0.0};
                    int vCount = parkingLots[i]->getCurrentVehicleCount();

                    for (int j = 0; j < vCount; ++j) {
                        const Vehicle* v = parkingLots[i]->getVehicleAt(j);
                        if (v == nullptr) continue;
                        for (int t = 0; t < 3; ++t) {
                            if (v->getVehicleType() == types[t]) {
                                lotCount[t]++;
                                lotFee[t] += v->getParkingFee();
                                sysCount[t]++;
                                sysFee[t] += v->getParkingFee();
                            }
                        }
                    }
                    cout << " * Bai do " << parkingLots[i]->getParkID() << ":\n";
                    for (int t = 0; t < 3; ++t) {
                        if (lotCount[t] > 0) {
                            cout << "   - " << types[t] << ": TB " << (lotFee[t] / lotCount[t])
                                 << " VND (" << lotCount[t] << " xe)\n";
                        } else {
                            cout << "   - " << types[t] << ": 0 VND (0 xe)\n";
                        }
                    }
                }
                cout << "\n2. Trung binh theo loai xe tren toan he thong:\n";
                for (int t = 0; t < 3; ++t) {
                    if (sysCount[t] > 0) {
                        cout << "   - " << types[t] << ": TB " << (sysFee[t] / sysCount[t])
                             << " VND (Tong " << sysCount[t] << " xe)\n";
                    } else {
                        cout << "   - " << types[t] << ": 0 VND (0 xe)\n";
                    }
                }
            }
            else if (chon == 9) { 
                cout << "Dang don dep bo nho Heap va thoat chuong trinh...\n";
                break;
            }
            else {
                cout << "Lua chon khong hop le. Vui long chon tu 1 den 9!\n";
            }
        }
    }
};
int main() {
    srand(static_cast<unsigned int>(time(0)));
    SystemInterface app;
    app.runMenu();
    return 0; 
}
