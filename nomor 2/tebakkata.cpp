#include "TebakKata.h"

int main() {
    srand(static_cast<unsigned int>(time(0)));
    
    char opsiReplay;
    do {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
        
        KataGame game; 
        
        mainGame(&game);
        
        cout << "\nApakah Anda ingin bermain lagi? (Y/N): ";
        cin >> opsiReplay;
        opsiReplay = toupper(opsiReplay);
        
    } while (opsiReplay == 'Y');
    
    cout << "\nTerima kasih telah menggunakan program game ini! Sampai jumpa.\n";
    return 0;
}
