#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

struct Barang{
    string kodeBarang;
    string namaBarang;
    double harga;
    int stok;
};

void tambahBarang(vector<Barang>& inventaris){
    Barang baru;
    cout << "\n --- TAMBAH BARANG BARU ---\n";
    cout << "Masukkan kode barang : ";
    cin >> baru.kodeBarang;

    for(int i = 0; i < inventaris.size(); i++){
        if (inventaris[i].kodeBarang == baru.kodeBarang){
            cout << "ERROR!!! Kode barang sudah ada, tidak bisa menambahkan lagi!\n";
        }
    }

    cout << "Masukkan nama barang : ";
    cin.ignore();
    getline(cin, baru.namaBarang);

    while(true){
        cout << "Masukkan Harga (Rp) : ";
        cin >> baru.harga;
        if (baru.harga >= 0){
            break;
        }
        cout << "ERROR!!! Harga tidak boleh negatif, silahkan masukkan ulang!\n";
    }

    while(true){
        cout << "Masukkan stok : ";
        cin >> baru.stok;
        if (baru.stok >= 0){
            break;
        }
        cout << "ERROR!!! Stok tidak boleh negatif, silahkan masukkan ulang!\n ";
    }

    inventaris.push_back(baru);
    cout << "BERHASIL!!! Yey Barang berhasil ditambahkan!\n";
}
void tampilkanSemuaBarang(vector<Barang>& inventaris){
    cout << "\n--- DAFTAR INVETARIS BARANG ---\n";

    if (inventaris.empty()){
        cout << "Invetaris masih kosong nih\n";    
    }

   cout << left
     << setw(8)  << "Kode"
     << setw(20) << "Nama Barang"
     << setw(15) << "Harga"
     << setw(6)  << "Stok" << "\n";

    cout << "----------------------------------------------------\n";
    for (int i = 0; i < inventaris.size(); i++) {
    cout << left
         << setw(8)  << inventaris[i].kodeBarang
         << setw(20) << inventaris[i].namaBarang
         << "Rp " << setw(12) << inventaris[i].harga
         << setw(6)  << inventaris[i].stok << "\n";
}
}

void cariBarangTermahal(vector<Barang>& inventaris) {
    cout << "\n--- CARI BARANG TERMAHAL ---\n";

    if (inventaris.empty()) {
        cout << "Inventaris masih kosong nih\n";
        return;
    }

    Barang termahal = inventaris[0];

    for (int i = 1; i < inventaris.size(); i++) {
        if (inventaris[i].harga > termahal.harga) {
            termahal = inventaris[i]; 
        }
    }

    cout << "Barang Termahal Saat Ini:\n";
    cout << "Kode: " << termahal.kodeBarang << " | Nama: " << termahal.namaBarang 
         << " | Harga: Rp " << termahal.harga << " | Stok: " << termahal.stok << "\n";
}

void hitungTotalNilaiInventaris(vector<Barang>& inventaris) {
    cout << "\n--- TOTAL NILAI INVENTARIS ---\n";

    long long totalNilai = 0;
    for (int i = 0; i < inventaris.size(); i++) {
        totalNilai += inventaris[i].harga * inventaris[i].stok;
    }

    cout << "Total aset uang dari seluruh barang di gudang : Rp " << totalNilai << "\n";
}

void cekRestock(vector<Barang>& inventaris) {
    cout << "\n--- BARANG YANG PERLU RESTOCK (STOK < 5) ---\n";

    bool adaBarangKritis = false;
    for (int i = 0; i < inventaris.size(); i++) {
        if (inventaris[i].stok < 5) {
            cout << "- Kode: " << inventaris[i].kodeBarang 
                 << " | Nama: " << inventaris[i].namaBarang 
                 << " (Stok sisa: " << inventaris[i].stok << ")\n";
            adaBarangKritis = true;
        }
    }

    if (!adaBarangKritis) {
        cout << "Aman Sekalii! Semua barang memiliki stok >= 5\n";
    }
}

void updateStok(vector<Barang>& inventaris) {
    cout << "\n--- UPDATE STOK BARANG ---\n";

    string kode;
    cout << "Masukkan kode barang yang dicari: ";
    cin >> kode;

    
    int* ptrStok = nullptr; 
    int indeksBarang = -1;

    for (int i = 0; i < inventaris.size(); i++) {
        if (inventaris[i].kodeBarang == kode) {
            ptrStok = &inventaris[i].stok; 
            indeksBarang = i;
            break;
        }
    }

    if (ptrStok == nullptr) {
        cout << "ERROR!!! Barang dengan kode tersebut tidak ditemukan\n";
        return;
    }

    cout << "Barang Ditemukan: " << inventaris[indeksBarang].namaBarang << "\n";
    cout << "Stok Saat Ini   : " << *ptrStok << "\n"; 

    cout << "Pilih :\n";
    cout << "  1. Tambah Stok (Barang Masuk)\n";
    cout << "  2. Kurangi Stok (Barang Keluar/Transaksi)\n";
    cout << "Pilihan: ";
    int pilihanOperasi;
    cin >> pilihanOperasi;

    int jumlah;
    cout << "Masukkan jumlah stok : ";
    cin >> jumlah;

    if (jumlah < 0) {
        cout << "ERROR!!! Jumlah tidak boleh negatif!\n";
        return;
    }

    if (pilihanOperasi == 1) {
        *ptrStok += jumlah; 
        cout << "BERHASIL!!! Stok berhasil ditambah. Stok baru : " << *ptrStok << "\n";
    } 
    else if (pilihanOperasi == 2) {
        if (jumlah > *ptrStok) {
            cout << "ERROR!!! Transaksi gagal! Stok tidak mencukupi\n";
        } else {
            *ptrStok -= jumlah; // Mengubah nilai stok asli melalui pointer
            cout << "BERHASIL!!! Stok berhasil dikurangi. Stok baru : " << *ptrStok << "\n";
        }
    } 
    else {
        cout << "ERROR!!! Pilihan operasi salah\n";
    }
}

int main() {
    vector<Barang> inventaris;
    int pilihanMenu = 0;

    inventaris.push_back({"B01", "Beras Merah 5kg", 75000, 12});
    inventaris.push_back({"B02", "Minyak 2L", 34000, 3}); 
    inventaris.push_back({"B03", "Tepung 1kg ", 16000, 20});

    do {
        cout << "\n=======================================\n";
        cout << "   SISTEM MANAJEMEN INVENTARIS TOKO   \n";
        cout << "=======================================\n";
        cout << "1. Tambah Barang\n";
        cout << "2. Tampilkan Semua Barang\n";
        cout << "3. Cari Barang Termahal\n";
        cout << "4. Hitung Total Nilai Inventaris\n";
        cout << "5. Cek Restock (Stok < 5)\n";
        cout << "6. Update Stok\n";
        cout << "7. Keluar\n";
        cout << "=======================================\n";
        cout << "Pilih Menu [1-7]: ";
        cin >> pilihanMenu;

        switch (pilihanMenu) {
            case 1: tambahBarang(inventaris); break;
            case 2: tampilkanSemuaBarang(inventaris); break;
            case 3: cariBarangTermahal(inventaris); break;
            case 4: hitungTotalNilaiInventaris(inventaris); break;
            case 5: cekRestock(inventaris); break;
            case 6: updateStok(inventaris); break;
            case 7: cout << "\nKeluar dari program. Terima kasih Banyak ya!\n"; break;
            default: cout << "ERROR!!! Pilihan tidak valid! Silakan pilih 1-7.\n"; break;
        }

    } while (pilihanMenu != 7);

    return 0;

}