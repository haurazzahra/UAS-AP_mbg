#include <iostream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

struct Mobil {
    string plat;
    string merk;
    string warna;
    time_t waktuMasuk;
};

struct Petugas {
    string nama;
    string id;
};

vector<Mobil> daftarMobil;

const int Max_Mobil = 20;

void garis() {
    cout << "============================================================\n";
}

void tampilanAwal() {
    garis();
    cout << "----------------S E L A M A T   D A T A N G-----------------\n";
    cout << "               DI PORTAL PARKIR KHUSUS MOBIL\n";
    cout << "                        MALL PRIENAL\n";
    garis();

    cout << "\nKami senang Anda telah hadir.\n";
    cout << "Sebelum melanjutkan, silahkan masukkan informasi Anda yang akan bertugas hari ini.\n";
}

void menu() {
    cout << "\nSilahkan input opsi berikut dalam bentuk angka.\n";
    cout << "1. Tambahkan Daftar Kendaraan\n";
    cout << "2. Tampilkan Daftar Kendaraan\n";
    cout << "3. Pembayaran\n";
    cout << "4. Keluar Program\n";
    cout << "Masukkan opsi : ";
}

void tambahMobil() {
    int jumlah;

    cout << "\nMasukkan jumlah mobil yang akan diparkirkan : ";
    cin >> jumlah;
    cin.ignore();

    if (daftarMobil.size() + jumlah > Max_Mobil) {
        cout << "\nMaaf, parkiran hanya dapat memuat "
             << Max_Mobil << " mobil !\n";
        return;
    }

    for (int i = 0; i < jumlah; i++) {
        Mobil m;

        cout << "\nMobil ke " << i + 1 << endl;

        cout << "Masukkan plat mobil  : ";
        getline(cin, m.plat);

        cout << "Masukkan merk mobil  : ";
        getline(cin, m.merk);

        cout << "Masukkan warna mobil : ";
        getline(cin, m.warna);

        m.waktuMasuk = time(0);

        daftarMobil.push_back(m);
    }

    cout << "\nData kendaraan berhasil ditambahkan.\n";
}

void tampilkanMobil() {
    if (daftarMobil.empty()) {
        cout << "\nBelum ada mobil yang terparkir.\n";
        return;
    }

    cout << "\nDAFTAR MOBIL YANG SUDAH TERPARKIR :\n";
    garis();

    for (int i = 0; i < daftarMobil.size(); i++) {

        time_t sekarang = time(0);
        int durasi = difftime(sekarang, daftarMobil[i].waktuMasuk);

        int jam = durasi / 3600;
        int menit = (durasi % 3600) / 60;
        int detik = durasi % 60;

        cout << "\nMobil ke-" << i + 1 << endl;
        cout << "Plat mobil  : " << daftarMobil[i].plat << endl;
        cout << "Merk mobil  : " << daftarMobil[i].merk << endl;
        cout << "Warna mobil : " << daftarMobil[i].warna << endl;

        cout << "Waktu parkir : " << jam << " jam " << menit << " menit " << detik << " detik\n";

        garis();
    }
}

void pembayaran() {

    if (daftarMobil.empty()) {
        cout << "\nTidak ada kendaraan di parkiran.\n";
        return;
    }

    string cariPlat;
    bool ditemukan = false;

    cin.ignore();

    cout << "\nMasukkan plat mobil yang ingin dibayar : ";
    getline(cin, cariPlat);

    for (int i = 0; i < daftarMobil.size(); i++) {

        if (daftarMobil[i].plat == cariPlat) {

            ditemukan = true;

            time_t sekarang = time(0);
            int durasi = difftime(sekarang, daftarMobil[i].waktuMasuk);

            int jam = durasi / 3600;

            if (jam == 0)
                jam = 1;

            int biaya = jam * 4000;

            cout << "\nPLAT DITEMUKAN\n";

            cout << "\nB I A Y A   P A R K I R : Rp " << biaya << endl;

            daftarMobil.erase(daftarMobil.begin() + i);

            break;
        }
    }

    if (ditemukan == false) {
        cout << "\nPLAT TIDAK DITEMUKAN !\n";
    }
}

int main() {

    Petugas petugas;

    tampilanAwal();

    cout << "\nMasukkan nama : ";
    getline(cin, petugas.nama);

    cout << "Masukkan ID   : ";
    getline(cin, petugas.id);

    int opsi;

    cout << "Nama Petugas : " << petugas.nama << endl;
    cout << "ID Petugas   : " << petugas.id << endl;

    cout << "\n";
    cout << "              TERIMA KASIH ATAS KERJASAMANYA !\n";
    cout << "---------------S E L A M A T  B E R T U G A S---------------\n";

    do {
        garis();

        menu();

        cin >> opsi;

        switch (opsi) {

        case 1:
            tambahMobil();
            break;

        case 2:
            tampilkanMobil();
            break;

        case 3:
            pembayaran();
            break;

        case 4:
            cout << "\nProgram selesai...\n";
            break;

        default:
            cout << "\nOpsi tidak tersedia.\n";
        }

    } while (opsi != 4);

    return 0;
}