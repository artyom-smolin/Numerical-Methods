#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

typedef vector<double> Double;

// заполнение массивов
void Fill_vectors(Double& vec_X, Double& vec_Y)
{
    vec_X[0] = 0.251;
    vec_X[1] = 0.254;
    vec_X[2] = 0.257;
    vec_X[3] = 0.260;
    vec_X[4] = 0.263;

    vec_Y[0] = 0.24837;
    vec_Y[1] = 0.25128;
    vec_Y[2] = 0.25418;
    vec_Y[3] = 0.25708;
    vec_Y[4] = 0.25718;
}
// вывод массива
void Print_vector(Double& vec, string name)
{
    cout << "\033[95m" "Массив " << name << "\033[37m" ":";
    for (size_t i = 0; i < vec.size(); ++i)
    {
        cout << '\t' << vec[i];
    }
    cout << '\n';
}

// первая производная (правая разность)
double first_derivative_right_difference(Double& vec_X, Double& vec_Y, size_t index)
{
    double result = (vec_Y[index + 1] - vec_Y[index]) / (vec_X[index + 1] - vec_X[index]);
    return result;
}
// первая производная (трёхточечная разность, обычная)
double first_derivative_threepoint_difference(Double& vec_X, Double& vec_Y, size_t index)
{
    double result = 0;

    if (index == 3)
    {
        result = (vec_Y[index - 2] - 4 * vec_Y[index - 1] + 3 * vec_Y[index]) / (2 * (vec_X[index + 1] - vec_X[index]));
    }
    else if (index < 0 || index > 3)
    {
        cerr << "Введён неверный индекс узла";
        abort();
    }
    else
    {
        result = (-3 * vec_Y[index] + 4 * vec_Y[index + 1] - vec_Y[index + 2]) / (2 * (vec_X[index + 1] - vec_X[index]));
    }

    return result;
}
// вторая производная
double second_derivative(Double& vec_X, Double& vec_Y, size_t index)
{
    double result = 0;

    if (index == 1)
    {
        double y_1 = static_cast<int>(vec_Y[index] * 10000) / 10000.0;
        double y_2 = static_cast<int>(vec_Y[index + 1] * 10000) / 10000.0;
        double y_3 = static_cast<int>(vec_Y[index + 2] * 10000) / 10000.0;
        result = (y_1 - 2 * y_2 + y_3) / (pow((vec_X[index + 1] - vec_X[index]), 2));
    }
    else if (index == 3)
    {
        result = (vec_Y[index - 1] - 2 * vec_Y[index] + vec_Y[index + 1]) / (pow(vec_X[index + 1] - vec_X[index], 2));
    }
    else if (index < 0 || index > 3)
    {
        cerr << "Введён неверный индекс узла";
        abort();
    }
    else
    {
        result = (vec_Y[index] - 2 * vec_Y[index + 1] + vec_Y[index + 2]) / (pow((vec_X[index + 1] - vec_X[index]), 2));
    }
    
    return result;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ГЛАВНАЯ ФУНКЦИЯ ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int main()
{
    setlocale(LC_ALL, "rus");
    cout.precision(5);

    cout << "\033[92m" "Лабораторная работа №5: \"Численное дифференцирование\"\n\n" "\033[97m";

    // наборы данных
    Double X(5);
    Double Y(5);
    Fill_vectors(X, Y);
    Print_vector(X, "X");
    Print_vector(Y, "Y");

    cout << '\n';
    cout << "\033[91m";
    system("pause");
    cout << "\033[97m";
    cout << '\n';

    // первая производная
    cout << "\033[94m" "Первая производная (двухточечная):\n" "\033[97m";
    for (size_t i = 0; i < X.size() - 1; i++)
    {
        cout << "f'(x_" << i << ") = " << first_derivative_right_difference(X, Y, i) << '\n';

    }
    cout << "\n\033[94m" "Первая производная (трёхточечная):\n" "\033[97m";
    for (size_t i = 0; i < X.size() - 1; i++)
    {
        cout << "f'(x_" << i << ") = " << first_derivative_threepoint_difference(X, Y, i) << '\n';
    }
    cout << '\n';

    // вторая производная
    cout << "\033[94m" "Вторая производная:\n" "\033[97m";
    for (size_t i = 0; i < X.size() - 1; i++)
    {
        cout << "f''(x_" << i << ") = " << second_derivative(X, Y, i) << '\n';
    }

    cout << "\n";
    cout << "\033[91m";
    system("pause");
    cout << "\033[97m";
    cout << "\n";

    cout << "\033[92m" "Выполнил: Смолин Артём Максимович\nГруппа: ИВТ2-Б22\n" "\033[97m";

    return 0;
}