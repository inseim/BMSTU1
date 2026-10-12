// Лабораторная работа №1, часть 2. Вариант 13.
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cmath>
#include <windows.h>

#define _USE_MATH_DEFINES // Необходимо для использования константы M_PI

using namespace std;

int main(int argc, char* argv[])
{
    SetConsoleOutputCP(CP_UTF8);
    setlocale(LC_ALL,"RU");
    // Массив заданных в условии точностей
    double t[3] = {1e-2, 1e-4, 1e-6};
    cout << "  точность E   -  число членов" << endl;

    // Цикл по всем трем заданным точностям
    for (int i = 0; i < 3; i++)
    {
        double e = t[i];
        double sum = 0.0;
        double pi_calc = 0.0;
        double k = 1.0;
        int n = 0;

        do
        {
            sum += 1.0 / (k * k);       // Очередное слагаемое ряда
            pi_calc = sqrt(6.0 * sum);  // Текущее значение ПИ

            k++;
            n++;                        // Счетчик слагаемых
        }
        while (abs(pi_calc - M_PI) >= e); // Пока не достигнута заданная точность
        cout << "  " <<  e << " - " <<  n <<  endl;
    }
    return 0;
}