#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cctype>
using namespace std;

struct KataGame {
    string asli;          
    string tebak;         
    int heart;            
    int level;            
    int hint;             
};

struct Pemain {
    string nama;
    int skor;
};

char tebakanSalah[26];
int jumlahSalah = 0;

Pemain leaderboard[5] = {
    {"-", 0}, {"-", 0}, {"-", 0}, {"-", 0}, {"-", 0}
};

string bankKata[15] = {
    "APEL", "MANGGA", "RAMBUTAN", "JERUK", "PEAR",
    "SEMANGKA", "PEPAYA", "DUKU", "PISANG", "STROBERI",
    "SALAK", "ANGGUR", "NANAS", "ALPUKAT", "MELON"
};

string pilihAcak() {
    int index = rand() % 15;
    return bankKata[index];
}

bool cekDuplikasi(char input, const KataGame* game) {
    for (size_t i = 0; i < game->tebak.length(); i++) {
        if (game->tebak[i] == input) return true;
    }
    for (int i = 0; i < jumlahSalah; i++) {
        if (tebakanSalah[i] == input) return true;
    }
    return false;
}

void gunakanHint(KataGame* game) {
    if (game->hint >= 2) {
        cout << "\n[HINT] Maaf, Anda sudah menggunakan batas maksimal 2 kali hint pada ronde ini!\n";
        cout << "Tekan Enter untuk melanjutkan...";
        cin.ignore(); cin.get();
        return;
    }

    if (game->heart <= 1) {
        cout << "\n[HINT] Nyawa tidak cukup untuk meminta hint (Minimal tersisa 2 nyawa)!\n";
        cout << "Tekan Enter untuk melanjutkan...";
        cin.ignore(); cin.get();
        return;
    }

    int indeksBelumTerbuka[30];
    int countBelumTerbuka = 0;

    for (size_t i = 0; i < game->tebak.length(); i++) {
        if (game->tebak[i] == '_') {
            indeksBelumTerbuka[countBelumTerbuka] = i;
            countBelumTerbuka++;
        }
    }

    if (countBelumTerbuka > 0) {
        int indeksAcak = rand() % countBelumTerbuka;
        int posisiKata = indeksBelumTerbuka[indeksAcak];
        char hurufHint = game->asli[posisiKata];

        for (size_t i = 0; i < game->asli.length(); i++) {
            if (game->asli[i] == hurufHint) {
                game->tebak[i] = hurufHint;
            }
        }

        game->heart--;  
        game->hint++; 

        cout << "\n[HINT] Berhasil membuka huruf '" << hurufHint << "' secara acak! Nyawa berkurang 1.\n";
        cout << "Penggunaan Hint: " << game->hint << "/2\n";
    } else {
        cout << "\n[HINT] Semua huruf sebenarnya sudah terbuka!\n";
    }

    cout << "Tekan Enter untuk melanjutkan...";
    cin.ignore(); cin.get();
}

int hitungSkor(const KataGame* game) {
    int bobotKesulitan = 0;
    if (game->level == 1) bobotKesulitan = 10;      
    else if (game->level == 2) bobotKesulitan = 20; 
    else bobotKesulitan = 30;                                                
    
    return game->heart * bobotKesulitan;
}

void updateLeaderboard(string namaBaru, int skorBaru) {
    if (skorBaru > leaderboard[4].skor) {
        leaderboard[4].nama = namaBaru;
        leaderboard[4].skor = skorBaru;
        
        for (int i = 0; i < 5 - 1; i++) {
            for (int j = 0; j < 5 - i - 1; j++) {
                if (leaderboard[j].skor < leaderboard[j + 1].skor) {
                    Pemain temp = leaderboard[j];
                    leaderboard[j] = leaderboard[j + 1];
                    leaderboard[j + 1] = temp;
                }
            }
        }
    }
}

void tampilkanLeaderboard() {
    cout << "=========================================\n";
    cout << "       LEADERBOARD 5 SKOR TERTINGGI      \n";
    cout << "=========================================\n";
    cout << "Peringkat\tNama\t\tSkor\n";
    cout << "-----------------------------------------\n";
    for (int i = 0; i < 5; i++) {
        cout << i + 1 << ".\t\t" << leaderboard[i].nama << "\t\t" << leaderboard[i].skor << "\n";
    }
    cout << "=========================================\n";
}

void mainGame(KataGame* game) {
    game->asli = pilihAcak();
    game->tebak = string(game->asli.length(), '_');
    game->hint = 0;
    jumlahSalah = 0;      

    cout << "=========================================\n";
    cout << "      SELAMAT DATANG DI GAME HANGMAN     \n";
    cout << "=========================================\n";
    cout << "Pilih Tingkat Kesulitan:\n";
    cout << "1. Easy   (8 kali maksimal kesalahan)\n";
    cout << "2. Medium (6 kali maksimal kesalahan)\n";
    cout << "3. Hard   (4 kali maksimal kesalahan)\n";
    cout << "-----------------------------------------\n";
    cout << "Masukkan pilihan (1-3): ";
    cin >> game->level;
    
    if (game->level == 1) game->heart = 8;
    else if (game->level == 2) game->heart = 6;
    else { game->heart = 4; game->level = 3; }

    while (game->heart > 0 && game->tebak != game->asli) {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
        
        cout << "=========================================\n";
        cout << "               TEBAK KATA                \n";
        cout << "=========================================\n\n";
        cout << "Tebak nama-nama buah!\n";
        cout << "Kata: ";
        for (size_t i = 0; i < game->tebak.length(); i++) {
            cout << game->tebak[i] << " ";
        }
        cout << "\n";
        
        cout << "Sisa Nyawa : " << game->heart << "\n";
        cout << "Sisa Hint  : " << (2 - game->hint) << "/2\n"; 
        
        cout << "Tebakan Salah: ";
        for (int i = 0; i < jumlahSalah; i++) {
            cout << tebakanSalah[i] << " ";
        }
        cout << "\n-----------------------------------------\n";
        cout << "Info: Ketik tombol '?' untuk meminta Hint Acak (-1 Nyawa)\n";
        
        char inputTebakan;
        cout << "Masukkan tebakan huruf Anda: ";
        cin >> inputTebakan;
        
        if (inputTebakan == '?') {
            gunakanHint(game);
            continue;
        }
        
        inputTebakan = toupper(inputTebakan);
        
        if (!isalpha(inputTebakan)) {
            cout << "Peringatan: Tolong masukkan karakter huruf valid!\n";
            cout << "Tekan Enter..."; cin.ignore(); cin.get();
            continue;
        }
        
        if (cekDuplikasi(inputTebakan, game)) {
            cout << "Pesan Peringatan: Huruf sudah pernah ditebak sebelumnya!\n";
            cout << "Sistem meminta huruf lain tanpa mengurangi nyawa.\n";
            cout << "Tekan Enter..."; cin.ignore(); cin.get();
            continue;
        }
        
        bool ditemukan = false;
        for (size_t i = 0; i < game->asli.length(); i++) {
            if (game->asli[i] == inputTebakan) {
                game->tebak[i] = inputTebakan;
                ditemukan = true;
            }
        }
        
        if (!ditemukan) {
            tebakanSalah[jumlahSalah] = inputTebakan;
            jumlahSalah++;
            game->heart--;
        }
    }
    
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
    
    cout << "=========================================\n";
    cout << "             PERMAINAN SELESAI           \n";
    cout << "=========================================\n\n";
    
    if (game->tebak == game->asli) {
        cout << "Selamat! Anda Menang!\n";
        int skorAkhir = hitungSkor(game);
        cout << "Skor Anda pada ronde ini: " << skorAkhir << "\n\n";
        
        string namaPemain;
        cout << "Masukkan nama Anda untuk Leaderboard: ";
        cin >> namaPemain;
        updateLeaderboard(namaPemain, skorAkhir);
    } else {
        cout << "Anda Kalah!\n";
        cout << "Kata rahasia yang sebenarnya adalah: " << game->asli << "\n";
    }
    cout << "-----------------------------------------\n\n";
    
    tampilkanLeaderboard();
}
