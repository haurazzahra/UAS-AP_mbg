#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class Minesweeper {
private:
    int size, totalBombs;
    char board[10][10];
    bool bombs[10][10], opened[10][10], flagged[10][10];
    bool gameOver = false, win = false;
    time_t startTime;

public:
    void startGame() {
        inputSettings();
        initializeBoard();
        placeBombs();
        calculateNumbers();

        startTime = time(0);

        while (!gameOver && !win) {
            displayBoard();

            int choice, row, col;

            cout << "\n=== PILIH AKSI ===\n";
            cout << "1. buka Kotak\n";
            cout << "2. tandai / hapus tanda\n";
            cout << "pilihan: ";
            cin >> choice;

            if (choice != 1 && choice != 2) {
            cout << "inputan tidak valid\n";
            continue;
            }
            
            cout << "masukkan baris (1-" << size << "): ";
            cin >> row;
            cout << "masukkan kolom (1-" << size << "): ";
            cin >> col;

            if (row < 1 || row > size ||
               col < 1 || col > size) {
                
               cout << "jumlah inputan tidak valid !\n";
               continue;
               }

                row--; col--;

            if (!isValid(row, col)) {
                cout << "koordinat tidak valid!\n";
                continue;
            }

            if (choice == 1) openCell(row, col);
            else if (choice == 2) toggleFlag(row, col);
            else cout << "pilihan tidak valid!\n";

            checkWin();
        }

        displayBoard(true);

        cout << (win ?
            "\nYAAAY! kamu menang!\n" :
            "\nBOOM! kamu kalah, wlee :P\n");

        cout << "lama waktu bermain: "
             << time(0) - startTime
             << " detik\n";
    }

private:
    void inputSettings() {
        do {
            cout << "masukkan ukuran papan (4-10): ";
            cin >> size;

            if (size < 4 || size > 10) {
                cout << "jumlah tidak valid !\n";
            }

} while (size < 4 || size > 10);

        do {
            cout << "masukkan jumlah bom (1-" 
            << size * size - 1 << "): ";
            cin >> totalBombs; 

             if (totalBombs < 1 || totalBombs >= size * size) {
        cout << "jumlah tidak valid !\n";
    }

        } while (totalBombs < 1 || totalBombs >= size * size);
    }

    void initializeBoard() {
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++) {
                board[i][j] = '0';
                bombs[i][j] = opened[i][j] = flagged[i][j] = false;
            }
    }

    void placeBombs() {
        int count = 0;

        while (count < totalBombs) {
            int r = rand() % size, c = rand() % size;

            if (!bombs[r][c]) {
                bombs[r][c] = true;
                count++;
            }
        }
    }

    void calculateNumbers() {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {

                if (bombs[i][j]) {
                    board[i][j] = '*';
                    continue;
                }

                int count = 0;

                for (int x = -1; x <= 1; x++)
                    for (int y = -1; y <= 1; y++) {
                        int ni = i + x, nj = j + y;

                        if (isValid(ni, nj) && bombs[ni][nj])
                            count++;
                    }

                board[i][j] = count + '0';
            }
        }
    }

    void displayBoard(bool reveal = false) {
        system("cls");

        int flagCount = 0;

        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                if (flagged[i][j]) flagCount++;

        cout << "bom belum ditandai: "
             << totalBombs - flagCount << endl;

        cout << "waktu : "
             << time(0) - startTime
             << " detik\n\n   ";

        for (int i = 0; i < size; i++) cout << i + 1 << " ";
        cout << endl;

        for (int i = 0; i < size; i++) {
            cout << i + 1 << "  ";

            for (int j = 0; j < size; j++) {

                if (reveal && bombs[i][j]) cout << "* ";
                else if (flagged[i][j]) cout << "F ";
                else if (!opened[i][j]) cout << "# ";
                else cout << board[i][j] << " ";
            }

            cout << endl;
        }
    }

    bool isValid(int r, int c) {
        return r >= 0 && r < size && c >= 0 && c < size;
    }

    void openCell(int r, int c) {
        if (opened[r][c] || flagged[r][c]) return;

        opened[r][c] = true;

        if (bombs[r][c]) {
            gameOver = true;
            return;
        }

        if (board[r][c] == '0')
            floodFill(r, c);
    }

    void floodFill(int r, int c) {
        for (int x = -1; x <= 1; x++) {
            for (int y = -1; y <= 1; y++) {

                int nr = r + x, nc = c + y;

                if (isValid(nr, nc) &&
                    !opened[nr][nc] &&
                    !bombs[nr][nc] &&
                    !flagged[nr][nc]) {

                    opened[nr][nc] = true;

                    if (board[nr][nc] == '0')
                        floodFill(nr, nc);
                }
            }
        }
    }

    void toggleFlag(int r, int c) {
        if (opened[r][c]) {
            cout << "kotak ini sudah dibuka\n";
            return;
        }

        flagged[r][c] = !flagged[r][c];
    }

    void checkWin() {
        int correct = 0, total = 0;

        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                if (flagged[i][j]) {
                    total++;
                    if (bombs[i][j]) correct++;
                }

        if (correct == totalBombs &&
            total == totalBombs)
            win = true;
    }
};

int main() {
    srand(time(0));

    int menu;

    do {
        cout << "=========================\n";
        cout << "    ! MINESWEEPER !\n";
        cout << "=========================\n";
        cout << "1. ayo mulai main\n";
        cout << "2. gak mau main\n";
        cout << "pilihan: ";
        cin >> menu;

        if (menu != 1 && menu != 2){
            cout << "pilihannya tidak valid, silakan input antara 1 atau 2 yaa\n";
            continue;
        }

        if (menu == 1) {
            Minesweeper game;
            game.startGame();

            cout << "\ntekan enter untuk kembali ke menu";
            cin.ignore();
            cin.get();
        }

    } while (menu != 2);

    cout << "yahh.. semoga di lain waktu kamu mau bermain yaa :>\n";

    return 0;
}