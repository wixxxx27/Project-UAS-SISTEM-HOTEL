#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <ctime>
#include <sstream>

using namespace std;

// Struktur untuk Kamar
struct Kamar {
    int nomor;
    string tipe;
    int harga;
    bool tersedia;
};

// Struktur untuk Menu
struct Menu {
    string nama;
    int harga;
};

// Struktur untuk Customer
struct Customer {
    string nama;
    string noTelepon;
};

// Struktur untuk Hotel
struct Hotel {
    vector<Kamar> kamarList;
    vector<Menu> menuList;
    vector<Customer> customerList;
    int totalPesananKamar;
    int totalPesananMakanan;
};

// Fungsi untuk inisialisasi data hotel
void inisialisasiHotel(Hotel &hotel) {
    hotel.totalPesananKamar = 0;
    hotel.totalPesananMakanan = 0;

    // Inisialisasi kamar
    for (int i = 100; i <= 120; i++) {
        if (i <= 110) {
            hotel.kamarList.push_back({i, "Regular", 550000, true});
        } else {
            hotel.kamarList.push_back({i, "Family", 800000, true});
        }
    }

    for (int i = 200; i <= 220; i++) {
        if (i <= 210) {
            hotel.kamarList.push_back({i, "Regular", 550000, true});
        } else {
            hotel.kamarList.push_back({i, "Family", 800000, true});
        }
    }

    // Inisialisasi menu makanan & minuman
    hotel.menuList.push_back({"Nasi Goreng", 50000});
    hotel.menuList.push_back({"Mie Goreng", 45000});
    hotel.menuList.push_back({"Ayam Goreng", 60000});
    hotel.menuList.push_back({"Jus Jeruk", 25000});
    hotel.menuList.push_back({"Teh Manis", 15000});
}

// Fungsi untuk menampilkan kamar yang tersedia
void tampilkanKamar(Hotel &hotel) {
    cout << "\n===========================================" << endl;
    cout << setw(10) << "No Kamar" << setw(15) << "Tipe" << setw(15) << "Harga (Rp)" << endl;
    cout << "===========================================" << endl;
    for (auto &k : hotel.kamarList) {
        if (k.tersedia) {
            cout << setw(10) << k.nomor << setw(15) << k.tipe << setw(15) << k.harga << endl;
        }
    }
    cout << "===========================================" << endl;
}

// Fungsi untuk pesan makanan
void pesanMakanan(Hotel &hotel, int pilihan, int jumlah) {
    if (pilihan > 0 && pilihan <= hotel.menuList.size()) {
        int hargaPesanan = hotel.menuList[pilihan - 1].harga * jumlah;
        hotel.totalPesananMakanan += hargaPesanan;
        cout << jumlah << " x " << hotel.menuList[pilihan - 1].nama << " berhasil dipesan. Total: Rp " << hargaPesanan << endl;
    } else {
        cout << "Pilihan menu tidak valid!" << endl;
    }
}

// Fungsi untuk menghitung lama menginap
int hitungLamaMenginap(const string &checkIn, const string &checkOut) {
    struct tm t1 = {}, t2 = {};
    istringstream ss1(checkIn), ss2(checkOut);
    ss1 >> get_time(&t1, "%d/%m/%Y");
    ss2 >> get_time(&t2, "%d/%m/%Y");

    time_t timeIn = mktime(&t1);
    time_t timeOut = mktime(&t2);

    double seconds = difftime(timeOut, timeIn);
    return seconds / (60 * 60 * 24); // Mengonversi detik ke hari
}

// Fungsi untuk booking kamar
void bookingKamar(Hotel &hotel, int nomor, const string &checkIn, const string &checkOut) {
    int lamaMenginap = hitungLamaMenginap(checkIn, checkOut);
    if (lamaMenginap <= 0) {
        cout << "Tanggal check-out harus setelah tanggal check-in!" << endl;
        return;
    }

    bool found = false;
    for (auto &k : hotel.kamarList) {
        if (k.nomor == nomor && k.tersedia) {
            found = true;
            k.tersedia = false;

            Customer customer;
            cout << "Masukkan Nama Customer: ";
            cin.ignore();
            getline(cin, customer.nama);
            cout << "Masukkan No. Telepon Customer: ";
            getline(cin, customer.noTelepon);
            hotel.customerList.push_back(customer);

            int hargaKamar = lamaMenginap * k.harga;
            hotel.totalPesananKamar += hargaKamar;

            cout << "\n===========================================" << endl;
            cout << "             Pemesanan Berhasil            " << endl;
            cout << "===========================================" << endl;
            cout << "Nama Customer: " << customer.nama << endl;
            cout << "No. Telepon: " << customer.noTelepon << endl;
            cout << "Kamar No: " << k.nomor << " | Tipe: " << k.tipe << endl;
            cout << "Tanggal Check-in: " << checkIn << endl;
            cout << "Tanggal Check-out: " << checkOut << endl;
            cout << "Lama Menginap: " << lamaMenginap << " malam" << endl;
            cout << "Total Harga Kamar: Rp " << hargaKamar << endl;
            cout << "===========================================" << endl;
            break;
        }
    }
    if (!found) {
        cout << "Kamar tidak tersedia atau nomor kamar salah." << endl;
    }
}

// Fungsi untuk menampilkan struk
void tampilkanStruk(Hotel &hotel) {
    cout << "\n===========================================" << endl;
    cout << "              Struk Pemesanan              " << endl;
    cout << "===========================================" << endl;
    if (!hotel.customerList.empty()) {
        cout << "Nama Customer: " << hotel.customerList.back().nama << endl;
        cout << "No. Telepon: " << hotel.customerList.back().noTelepon << endl;
    } else {
        cout << "Belum ada data customer." << endl;
    }
    cout << "-------------------------------------------" << endl;
    cout << "Total Harga Kamar: Rp " << hotel.totalPesananKamar << endl;
    cout << "Total Harga Makanan & Minuman: Rp " << hotel.totalPesananMakanan << endl;
    cout << "-------------------------------------------" << endl;
    cout << "Grand Total: Rp " << hotel.totalPesananKamar + hotel.totalPesananMakanan << endl;
    cout << "===========================================" << endl;
}

int main() {
    Hotel hotel;
    inisialisasiHotel(hotel);

    int pilihan, nomorKamar, menuPilihan, jumlahPesanan;
    string checkIn, checkOut;

    while (true) {
        cout << "\n===========================================" << endl;
        cout << "  SELAMAT DATANG DI HOTEL LABA LABA SUNDA      " << endl;
        cout << "===========================================" << endl;
        cout << "1. Booking Kamar" << endl;
        cout << "2. Pesan Makanan & Minuman" << endl;
        cout << "3. Tampilkan Struk Pemesanan" << endl;
        cout << "4. Keluar" << endl;
        cout << "===========================================" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tampilkanKamar(hotel);
                cout << "Masukkan Nomor Kamar yang ingin dipesan: ";
                cin >> nomorKamar;
                cout << "Tanggal Check-in (DD/MM/YYYY): ";
                cin >> checkIn;
                cout << "Tanggal Check-out (DD/MM/YYYY): ";
                cin >> checkOut;
                bookingKamar(hotel, nomorKamar, checkIn, checkOut);
                break;
            case 2:
                cout << "Menu Makanan & Minuman" << endl;
                for (int i = 0; i < hotel.menuList.size(); i++) {
                    cout << (i + 1) << ". " << hotel.menuList[i].nama << " | Rp " << hotel.menuList[i].harga << endl;
                }
                cout << "Masukkan nomor menu: ";
                cin >> menuPilihan;
                cout << "Masukkan jumlah pesanan: ";
                cin >> jumlahPesanan;
                pesanMakanan(hotel, menuPilihan, jumlahPesanan);
                break;
            case 3:
                tampilkanStruk(hotel);
                break;
            case 4:
                cout << "Terima kasih telah mengunjungi hotel kami!" << endl;
                return 0;
            default:
                cout << "Pilihan tidak valid!" << endl;
        }
    }
}
