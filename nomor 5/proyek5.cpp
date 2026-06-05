#include <iostream>
#include <string>
#include <cstdlib> 
#include <ctime>

using namespace std;
string negara_asli, negara_sensor, jawab;
int jlhNegara, skor, acak;
char opsi;
string sensor(string negara) {
    string hasil = negara;
    for (int i = 0; i < hasil.length(); i++) {
        if (rand() % 2 == 0) { 
            hasil[i] = '_';
        }
    }
    return hasil; 
}

int main() {
    srand(time(0)); 
    string soal[5] = {"norway", "oman", "brunei", "indonesia", "malaysia"};
    jlhNegara = 5;
    skor = 0;

    do {
        acak = rand() % jlhNegara; 
        string negara_asli = soal[acak];
        string negara_sensor = sensor(negara_asli);

        cout << "Tebak negara: " << negara_sensor << endl;
        cout << "Negara apakah yang dimaksud? "; cin >> jawab;

        for (int i = 0; i < jawab.length(); i++) {
            jawab[i] = tolower(jawab[i]);
        }

        if (jawab == negara_asli) {
            cout << "Selamat! Anda benar." << endl;
            skor++;
        } else {
            cout << "Maaf, jawaban Anda salah. Coba lagi." << endl;
        }

        cout << "Skor Anda: " << skor << endl;
        cout << "Ingin bermain lagi? (y/n): ";
        cin >> opsi;
        cout << endl;

    } while (opsi == 'y' || opsi == 'Y');

    cout << "Game Selesai!";
}
