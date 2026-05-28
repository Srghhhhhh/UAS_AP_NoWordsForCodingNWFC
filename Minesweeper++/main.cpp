#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class Minesweeper {
private:
    int boardSize;
    int totalMines;
    
    bool isMine[10][10];
    bool isRevealed[10][10];
    bool isFlagged[10][10];
    int mineCount[10][10];
    
    time_t startTime;
    bool gameOver;
    bool gameWon;

    bool isValid(int r, int c) {
        return (r >= 0 && r < boardSize && c >= 0 && c < boardSize);
    }

    void calculateNeighbors() {
        int dr[] = {-1, -1, -1, 0, 0, 1, 1, 1};
        int dc[] = {-1, 0, 1, -1, 1, -1, 0, 1};

        for (int r = 0; r < boardSize; r++) {
            for (int c = 0; c < boardSize; c++) {
                if (isMine[r][c]) continue;
                
                int count = 0;
                for (int i = 0; i < 8; i++) {
                    int nr = r + dr[i];
                    int nc = c + dc[i];
                    if (isValid(nr, nc) && isMine[nr][nc]) {
                        count++;
                    }
                }
                mineCount[r][c] = count;
            }
        }
    }

    void floodFill(int r, int c) {
        if (!isValid(r, c) || isRevealed[r][c] || isFlagged[r][c]) return;

        isRevealed[r][c] = true;

        if (mineCount[r][c] == 0) {
            int dr[] = {-1, -1, -1, 0, 0, 1, 1, 1};
            int dc[] = {-1, 0, 1, -1, 1, -1, 0, 1};
            for (int i = 0; i < 8; i++) {
                floodFill(r + dr[i], c + dc[i]);
            }
        }
    }

    void checkWinCondition() {
        for (int r = 0; r < boardSize; r++) {
            for (int c = 0; c < boardSize; c++) {
                if (isMine[r][c] && !isFlagged[r][c]) return;
                if (!isMine[r][c] && isFlagged[r][c]) return;
            }
        }
        gameOver = true;
        gameWon = true;
    }

    int countCurrentFlags() {
        int flags = 0;
        for (int r = 0; r < boardSize; r++) {
            for (int c = 0; c < boardSize; c++) {
                if (isFlagged[r][c]) flags++;
            }
        }
        return flags;
    }

public:
    void initGame() {
        gameOver = false;
        gameWon = false;

        do {
            cout << "Masukkan ukuran papan (N x N, minimal 4, maksimal 10): ";
            cin >> boardSize;
            if (boardSize < 4 || boardSize > 10) {
                cout << "Ukuran tidak valid!\n";
            }
        } while (boardSize < 4 || boardSize > 10);

        int maxMines = (boardSize * boardSize) - 1;
        do {
            cout << "Masukkan jumlah bom (1 - " << maxMines << "): ";
            cin >> totalMines;
            if (totalMines < 1 || totalMines > maxMines) {
                cout << "Jumlah bom tidak valid untuk ukuran papan ini!\n";
            }
        } while (totalMines < 1 || totalMines > maxMines);

        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                isMine[i][j] = false;
                isRevealed[i][j] = false;
                isFlagged[i][j] = false;
                mineCount[i][j] = 0;
            }
        }

        int plantedMines = 0;
        while (plantedMines < totalMines) {
            int r = rand() % boardSize;
            int c = rand() % boardSize;
            if (!isMine[r][c]) {
                isMine[r][c] = true;
                plantedMines++;
            }
        }

        calculateNeighbors();
        startTime = time(0); 
    }

    void displayBoard() {
        system("clear || cls"); 
        time_t currentTime = time(0);
        int elapsedSeconds = difftime(currentTime, startTime);

        cout << "==== MINESWEEPER++ ====\n";
        cout << "Sisa Bom Belum Ditandai: " << (totalMines - countCurrentFlags()) << "\n";
        cout << "Waktu Berjalan         : " << elapsedSeconds << " detik\n\n";

        cout << "    ";
        for (int c = 1; c <= boardSize; c++) {
            cout << c << "   ";
        }
        cout << "\n  +";
        for (int i = 0; i < boardSize * 4; i++) cout << '-';
        cout << "\n";

        for (int r = 0; r < boardSize; r++) {
            if (r + 1 < 10) cout << " " << (r + 1) << " | ";
            else cout << (r + 1) << " | ";

            for (int c = 0; c < boardSize; c++) {
                if (gameOver && isMine[r][c]) {
                    cout << "* ";
                } else if (isFlagged[r][c]) {
                    cout << "F   ";
                } else if (!isRevealed[r][c]) {
                    cout << ".   ";
                } else {
                    if (mineCount[r][c] == 0) cout << "0   ";
                    else cout << mineCount[r][c] << "   ";
                }
            }
            cout << "\n";
        }
        cout << "\n";
    }

    void play() {
        initGame();

        while (!gameOver) {
            displayBoard();
            
            int inputRow, inputCol, action;
            cout << "Aksi Pemain:\n";
            cout << "1. Buka Kotak\n";
            cout << "2. Tandai / Hapus Tanda Bom (Flag)\n";
            cout << "Pilih aksi (1-2): ";
            cin >> action;

            if (action != 1 && action != 2) {
                cout << "Aksi tidak valid! Tekan Enter untuk mencoba lagi...";
                cin.ignore(); cin.get();
                continue;
            }

            cout << "Masukkan koordinat Baris dan Kolom (contoh: 1 3): ";
            cin >> inputRow >> inputCol;

            int r = inputRow - 1;
            int c = inputCol - 1;

            if (!isValid(r, c)) {
                cout << "Koordinat di luar jangkauan papan! Tekan Enter...";
                cin.ignore(); cin.get();
                continue;
            }

            if (action == 1) { 
                if (isFlagged[r][c]) {
                    cout << "Kotak sedang ditandai (Flag)! Hapus tanda terlebih dahulu.\n";
                    cin.ignore(); cin.get();
                    continue;
                }
                if (isMine[r][c]) {
                    gameOver = true; 
                } else {
                    floodFill(r, c);
                    checkWinCondition();
                }
            } 
            else if (action == 2) { 
                if (isRevealed[r][c]) {
                    cout << "Kotak sudah terbuka, tidak bisa ditandai!\n";
                    cin.ignore(); cin.get();
                    continue;
                }
                isFlagged[r][c] = !isFlagged[r][c]; 
                checkWinCondition();
            }
        }

        displayBoard();
        time_t endTime = time(0);
        int totalTime = difftime(endTime, startTime);

        if (gameWon) {
            cout << "Selamat! Kamu Berhasil Menang Menandai Semua Bom!\n";
        } else {
            cout << "BOOM! Kamu menginjak bom. Game Over!\n";
        }
        cout << "Total Waktu Bermain: " << totalTime << " detik.\n\n";
    }
};

int main() {
    srand(time(0));
    Minesweeper game;
    int choice;

    do {
        cout << "=== MENU UTAMA ===\n";
        cout << "1. Mulai Permainan Baru\n";
        cout << "2. Keluar\n";
        cout << "Pilihan Anda: ";
        cin >> choice;

        if (choice == 1) {
            game.play();
        }
    } while (choice != 2);

    cout << "Terima kasih telah bermain!\n";
    return 0;
}