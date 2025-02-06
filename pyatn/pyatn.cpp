#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

const int SIZE = 3; // Размер игрового поля
int doska1[SIZE][SIZE]; // Игровое поле

// Функция для инициализации игрового поля
void doska() {
    int num = 1;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            doska1[i][j] = num++;
        }
    }
    doska1[SIZE - 1][SIZE - 1] = 0; // Пустая ячейка
}

// Функция для отображения игрового поля
void printdoska() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (doska1[i][j] == 0) {
                cout << "   "; 
            }
            else {
                cout << doska1[i][j] << " ";
            }
        }
        cout << endl;
    }
}

// Функция для нахождения позиции пустой ячейки
void ifpusto(int& emptyRow, int& emptyCol) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (doska1[i][j] == 0) {
                emptyRow = i;
                emptyCol = j;
                return;
            }
        }
    }
}

// Функция для перемещения плитки
bool sdvigPlitki(int tile) {
    int pustotaRow, pustotaCol;
    ifpusto(pustotaRow, pustotaCol);

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (doska1[i][j] == tile) {
                // Проверяем, можно ли переместить плитку
                if ((i == pustotaRow && abs(j - pustotaCol) == 1) || (j == pustotaCol && abs(i - pustotaRow) == 1)) {
                    swap(doska1[i][j], doska1[pustotaRow][pustotaCol]);
                    return true;
                }
            }
        }
    }
    return false;
}

// Функция для проверки, завершена ли игра
bool pobeda() {
    int num = 1;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (i == SIZE - 1 && j == SIZE - 1) {
                return doska1[i][j] == 0; 
            }
            if (doska1[i][j] != num++) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    setlocale(LC_ALL, "ru");
    doska();
    srand(time(0));

    // Перемешиваем плитки
    for (int i = 0; i < 100; ++i) {
        int tile = rand() % (SIZE * SIZE);
        sdvigPlitki(tile);
    }

    while (true) {
        printdoska();
        if (pobeda()) {
            cout << "АЛЛИЛУЯ, АЛЛИЛУЯ, АЛЛИЛУЯ!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
            break;
        }

        cout << "Введите номер плитки(0 для выхода): ";
        int plitka;
        cin >> plitka;

        if (plitka == 0) {
            break;
        }

        if (!sdvigPlitki(plitka)) {
            cout << "фиг тебе!" << endl;
        }
    }

    return 0;
}
