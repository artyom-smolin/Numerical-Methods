#include <iostream>
#include <vector>
#include <set>
using namespace std;

typedef vector<double> One_Double;

// f(x)
double Function(double x)
{
    return double(pow(x, 5) + pow((6 - x), 5) - 1056);
}
// f'(x)
double Function_(double x)
{
    return double(5 * pow(x, 4) - 5 * pow((6 - x), 4));
}
// phi'(x)
double Phi_(double x)
{
    return double(pow((6 - x), 4) / pow(1056 - pow(6 - x, 5), 4.0 / 5.0));
}

// первый корень найден
bool first_root_found = false;

// метод Ньютона для одного уравнения
void newton_Method_one_equation(double a, double b, double eps, One_Double& res)
{
    // x_k, x_k+1
    double x_0, x_k;
    cout << "Введите начальное приближение: ";
    cin >> x_0;

    // число итераций
    int count = 0;

    // cout << "Начальное (x_0): " << x_0 << '\n';
    
    // сам метод
    while (true)
    {
        count++;

        x_k = x_0 - Function(x_0) / Function_(x_0);

        // cout << "Промежуточное (x_k): " << x_k << '\n';

        if (abs(x_k - x_0) < eps)
        {
            // проверка принадлежности корня к интервалу
            if (x_k >= a && x_k <= b)
            {
                // cout << "Итоговое (x_k): " << x_k << "\n\n";
                res.push_back(x_k);

                if (!first_root_found)
                {
                    // первый корень найден
                    first_root_found = true;

                    // смена начального приближения
                    if (res[0] < x_0 || res[0] == 4)
                        x_0 = a;
                    else if (x_0 <= res[0])
                        x_0 = b;

                    // пропуск текущей итерации
                    continue;
                }
                if (res.size() == 2) break;
            }
        }
        x_0 = x_k;
    }

    cout << "\033[94m" "Количество итераций: " "\033[97m" << count << "\n";
}

// вывод решения для ч1
void print_Solution_One(One_Double& result)
{
    cout << "\033[94m" "Корни: " "\033[97m" "(";
    for (size_t i = 0; i < result.size(); i++)
    {
        if (i != result.size() - 1)
            cout << result[i] << "; ";
        else
            cout << result[i];

    }
    cout << ")\n";
}
// вывод решения для ч2
void print_Solution_Two(set<One_Double>& results)
{
    cout << "\033[94m" "Корни: " "\033[97m";
    int i = 0;
    for (const auto& result : results) 
    {
        if(i!=3)
            cout << "(" << result[0] << "; " << result[1] << "), ";
        if(i==3)
            cout << "(" << result[0] << "; " << result[1] << ")\n";
        i++;
    }
}

// ч1п1
void First_Part()
{
    cout << "\033[95m" "Часть 1. Пункт 1.\n\n" "\033[97m";

    cout << "\033[94m" "phi(x)" "\033[97m" " = ((1056-(6-x)^5))^(1/5)\n";
    cout << "\033[94m" "phi'(x)" "\033[97m" " = (6-x)^4 / ((1056-(6-x)^5))^(4/5)\n\n";

    long long count = 0;
    long long count_reverse = 0;
    for (int i = 0; i <= 1000000; i++)
    {
        if (abs(Phi_(double(i))) < 1.0)
            count++;
        else
            count_reverse++;
    }
    cout << "0 <= x <= 1.000.000\n";
    cout << "\033[94m" "phi'(x)" "\033[97m" " >= 1: " << count_reverse << endl << "\033[94m" "phi'(x)" "\033[97m" " < 1: " << count << "\n";

    count = 0;
    count_reverse = 0;
    for (int i = -1000000; i <= 1000000; i++)
    {
        if (abs(Phi_(double(i))) < 1.0)
            count++;
        else
            count_reverse++;
    }
    cout << "\n-1000000 <= x <= 1.000.000\n";
    cout << "\033[94m" "phi'(x)" "\033[97m" " >= 1: " << count_reverse << endl << "\033[94m" "phi'(x)" "\033[97m" " < 1: " << count << "\n";

    cout << "\n";
    system("pause");
    cout << "\n";
}

// f(x,y)
double f_xy(double& x, double& y)
{
    return pow(x, 2) + pow(y, 4) - 20;
}
// g(x,y)
double g_xy(double& x, double& y)
{
    return pow(x, 4) + pow(y, 2) - 20;
}

// ∂f/∂x
double df_dx(double& x, double& y)
{
    return 2 * x;
}
// ∂f/∂y
double df_dy(double& x, double& y)
{
    return 4 * pow(y, 3);
}
// ∂g/∂x
double dg_dx(double& x, double& y)
{
    return 4 * pow(x, 3);
}
// ∂g/∂y
double dg_dy(double& x, double& y)
{
    return 2 * y;
}

// коэффициенты поиска корней системы
double b_1_k(double& x_k, double& y_k)
{
    return -f_xy(x_k, y_k) + df_dx(x_k, y_k) * x_k + df_dy(x_k, y_k) * y_k;
}
double b_2_k(double& x_k, double& y_k)
{
    return -g_xy(x_k, y_k) + dg_dx(x_k, y_k) * x_k + dg_dy(x_k, y_k) * y_k;
}
double a_11_k(double& x_k, double& y_k)
{
    return df_dx(x_k, y_k);
}
double a_12_k(double& x_k, double& y_k)
{
    return df_dy(x_k, y_k);
}
double a_21_k(double& x_k, double& y_k)
{
    return dg_dx(x_k, y_k);
}
double a_22_k(double& x_k, double& y_k)
{
    return dg_dy(x_k, y_k);
}

// проверка условия существования решения системы
bool existence_of_system(double& x_0, double& y_0)
{
    return a_11_k(x_0, y_0) * a_22_k(x_0, y_0) - a_21_k(x_0, y_0) * a_12_k(x_0, y_0) != 0;
}

// равенства для поиска корней
double Kramer_x_k(double& x_0, double& y_0)
{
    return (double(b_1_k(x_0, y_0) * a_22_k(x_0, y_0) - b_2_k(x_0, y_0) * a_12_k(x_0, y_0)) / double(a_11_k(x_0, y_0) * a_22_k(x_0, y_0) - a_21_k(x_0, y_0) * a_12_k(x_0, y_0)));
}
double Kramer_y_k(double& x_0, double& y_0)
{
    return (double(b_2_k(x_0, y_0) * a_11_k(x_0, y_0) - b_1_k(x_0, y_0) * a_21_k(x_0, y_0)) / double(a_11_k(x_0, y_0) * a_22_k(x_0, y_0) - a_21_k(x_0, y_0) * a_12_k(x_0, y_0)));
}

// метод Ньютона для системы двух уравнений
set<One_Double> newton_Method_two_equation(double epsilon) 
{
    // множество корней
    set<One_Double> results;

    // набор начальных приближений
    vector<pair<double, double>> initial_approximations = { {1, 1}, {-1, 1}, {1, -1}, {-1, -1} };

    // счётчик итераций
    int count = 0;

    // начальное приближение
    double x_0, y_0;

    // цикл выполнится 4 раза
    for (const auto& approximation : initial_approximations)
    {
        // присваивание очередного начального приближения
        x_0 = approximation.first;
        y_0 = approximation.second;

        // проверка существования системы
        if (existence_of_system(x_0, y_0))
        {
            // использование формул для поиска корня
            double x_k = Kramer_x_k(x_0, y_0);
            double y_k = Kramer_y_k(x_0, y_0);

            // cout << "Начальные (x_0, y_0): " << x_0 << ", " << y_0 << '\n';

            // поиск корня до заданной точности
            while (sqrt(pow(x_k - x_0, 2) + pow(y_k - y_0, 2)) >= epsilon)
            {
 
                // cout << "Промежуточные (x_k, y_k): " << x_k << ", " << y_k << '\n';
                x_0 = x_k;
                y_0 = y_k;

                x_k = Kramer_x_k(x_0, y_0);
                y_k = Kramer_y_k(x_0, y_0);

                count++;
            }
 
            // cout << "Итоговые (x_k, y_k): " << x_k << ", " << y_k << "\n\n";

            // Добавление корня в результаты
            results.insert({ x_k, y_k });
        }
        else
        {
            // если начальное приближение не подошло для существования системы
            abort();
        }
        
    }

    cout << "\033[94m" "Количество итераций: " "\033[97m" << ++count << "\n"; // ибо одна итерация опущена в цикле
    return results;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ГЛАВНАЯ ФУНКЦИЯ ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int main()
{
    setlocale(LC_ALL, "rus");

    cout << "\033[92m" "Лабораторная работа №3: \"Численное решение нелинейных уравнений\"\n\n" "\033[97m";

    // ч1п1
    First_Part(); // ещё в тетради + эксель-файле

    // ч1п2
    cout << "\033[95m" "Часть 1. Пункт 2.\n\n" "\033[97m";

    cout << "\033[94m" "f(x)" "\033[97m" " = x^5 + (6-x)^5 - 1056\n\n";

    // диапазон поиска корней
    double a = -1000000;
    double b = 1000000;

    // точность
    double eps = 1e-4;

    // решение
    One_Double result_one;

    // поиск корней 
    newton_Method_one_equation(a, b, eps, result_one);
    // вывод корней
    print_Solution_One(result_one);

    cout << "\n";
    system("pause");
    cout << "\n";

    // ч1п3 
    cout << "\033[95m" "\033[1m" "Часть 1. Пункт 3.\n\n" "\033[97m";

    cout << "Путём варьирования начального приближения было установлено:\n";
    cout << "Диапазон допустимого начального приближения: (-inf;3)+(3;+inf)\n";
    cout << "При x_0 = 3 знаменатель формулы корня равен нулю: ";
    cout << "Function_(3) = " << Function_(3) << "\n";

    cout << "\n";
    system("pause");
    cout << "\n";

    // ч2
    cout << "\033[95m" "\033[1m" "Часть 2.\n\n" "\033[97m";

    // решение
    set<One_Double> result_two;
    result_two = newton_Method_two_equation(eps);
    print_Solution_Two(result_two);

    cout << "\n";
    system("pause");
    cout << "\n";

    cout << "\033[92m" "Выполнил: Смолин Артём Максимович\nГруппа: ИВТ2-Б22\n" "\033[97m";

    return 0;
}