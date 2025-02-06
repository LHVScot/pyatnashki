#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

const int SIZE = 3; // Размер игрового поля
int board[SIZE][SIZE]; // Игровое поле

// Функция для инициализации игрового поля
void initBoard() {
    int num = 1;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            board[i][j] = num++;
        }
    }
    board[SIZE - 1][SIZE - 1] = 0; // Пустая ячейка
}

// Функция для отображения игрового поля
void printBoard() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] == 0) {
                cout << "   "; 
            }
            else {
                cout << board[i][j] << " ";
            }
        }
        cout << endl;
    }
}

// Функция для нахождения позиции пустой ячейки
void findEmptyPosition(int& emptyRow, int& emptyCol) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] == 0) {
                emptyRow = i;
                emptyCol = j;
                return;
            }
        }
    }
}

// Функция для перемещения плитки
bool moveTile(int tile) {
    int emptyRow, emptyCol;
    findEmptyPosition(emptyRow, emptyCol);

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] == tile) {
                // Проверяем, можно ли переместить плитку
                if ((i == emptyRow && abs(j - emptyCol) == 1) || (j == emptyCol && abs(i - emptyRow) == 1)) {
                    swap(board[i][j], board[emptyRow][emptyCol]);
                    return true;
                }
            }
        }
    }
    return false;
}

// Функция для проверки, завершена ли игра
bool isSolved() {
    int num = 1;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (i == SIZE - 1 && j == SIZE - 1) {
                return board[i][j] == 0; // Последняя ячейка должна быть пустой
            }
            if (board[i][j] != num++) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    setlocale(LC_ALL, "ru");
    initBoard();
    srand(time(0));

    // Перемешиваем плитки
    for (int i = 0; i < 100; ++i) {
        int tile = rand() % (SIZE * SIZE);
        moveTile(tile);
    }

    while (true) {
        printBoard();
        if (isSolved()) {
            cout << "Поздравляем! Вы выиграли!" << endl;
            break;
        }

        cout << "Введите номер плитки для перемещения (0 для выхода): ";
        int tile;
        cin >> tile;

        if (tile == 0) {
            break;
        }

        if (!moveTile(tile)) {
            cout << "Невозможно переместить плитку!" << endl;
        }
    }

    return 0;
}