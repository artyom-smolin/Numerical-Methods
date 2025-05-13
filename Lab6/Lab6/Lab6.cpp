#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;

// для циклов
size_t i;
// точность - 31 знак после запятой
#define M_PI 3.1415926535897932384626433832795
// точное значение интеграла ~ 9.3626268488594224051769831309335
long double exact_value = 1 + 3 * log(2) + 2 * M_PI;
// f(x) - подынтегральная функция
double f(double x)
{
	return pow(x, 2) / (pow(x, 2) - 6 * x + 10);
}
// погрешность
double inaccuracy(long double approximate)
{
	return abs(exact_value - approximate);
}

// метод прямоугольников (левых)
long double method_rectangle_left(double n, vector<double>& x)
{
	double result = 0;

	for (i = 0; i < n - 1; ++i)
	{
		result += f(x[i]) * (x[i + 1] - x[i]);
	}

	return result;
}
// метод прямоугольников (правых)
long double method_rectangle_right(double n, vector<double>& x)
{
	double result = 0;

	for (i = 0; i < n - 1; ++i)
	{
		result += f(x[i + 1]) * (x[i + 1] - x[i]);
	}

	return result;
}
// метод прямоугольников (центральных)
long double method_rectangle_central(double n, vector<double>& x)
{
	double result = 0;

	for (i = 0; i < n - 1; ++i)
	{
		result += f((x[i] + x[i + 1]) / 2) * (x[i + 1] - x[i]);
	}

	return result;
}
// метод трапеций
long double method_trapezoid(double n, vector<double>& x)
{
	double result = 0;

	for (i = 0; i < n - 1; ++i)
	{
		result += (f(x[i]) + f(x[i + 1])) / 2 * (x[i + 1] - x[i]);
	}

	return result;
}
// метод парабол
long double method_parabola(double n, vector<double>& x)
{
	double result = 0;

	for (i = 0; i < n - 1; ++i)
	{
		result += (f(x[i]) + 4 * f((x[i] + x[i + 1]) / 2) + f(x[i + 1])) * (x[i + 1] - x[i]);
	}

	return result/6;
}

int main()
{
	setlocale(LC_ALL, "rus");
	cout.precision(6);

	cout << "\033[92m" "Лабораторная работа №6: \"Численное интегрирование\"\n\n" "\033[97m";
	
	// интервал определённого интеграла
	double a = 3;
	double b = 4;

	// число точек
	long long n;
	cout << "\033[94m" "Введите число точек: " "\033[97m";
	try 
	{
		cin >> n;
		if (n < 2) throw runtime_error("Число точек не может быть меньше 2!\n");
	}
	catch (const runtime_error& error)
	{
		cout << "\033[91m" "\nОшибка: " "\033[97m" <<  error.what();
		return 0;
	}
	
	--n; // с учётом того, что на плоскости должно быть n точек включая концы интервала
	double h = (b - a) / n; // шаг разбиения (равномерного)
	++n; // возвращение числа точек к валидному состоянию

	cout << "\033[94m" "Шаг разбиения: " "\033[97m" << h << '\n';

	// создание отрезков 
	vector<double> x;
	double temp = a;
	x.push_back(a); // x_0
	for (i = 0; i < n - 2; ++i)
	{
		temp += h;
		x.push_back(temp); // x_i
	}
	x.push_back(b); // x_n
	
	// вывод точек
	cout << "\033[94m" "Точки на интервале: " "\033[97m";
	for (const auto& item : x)
	{
		cout << item << " ";
	}
	cout << '\n';

	cout << "\033[94m" "\nТочное значение:\t\t" "\033[96m" << exact_value << "\033[97m" << '\n';
	cout << "Левые прямоугольники:\t\t" << method_rectangle_left(n, x) << "\tПогрешность:\t" << inaccuracy(method_rectangle_left(n, x)) << '\n';
	cout << "Правые прямоугольники:\t\t" << method_rectangle_right(n, x) << "\tПогрешность:\t" << inaccuracy(method_rectangle_right(n, x)) << '\n';
	cout << "Центральные прямоугольники:\t" << method_rectangle_central(n, x) << "\tПогрешность:\t" << inaccuracy(method_rectangle_central(n, x)) << '\n';
	cout << "Трапеции:\t\t\t" << method_trapezoid(n, x) << "\tПогрешность:\t" << inaccuracy(method_trapezoid(n, x)) << '\n';
	cout << "Параболы:\t\t\t" << method_parabola(n, x) << "\tПогрешность:\t" << inaccuracy(method_parabola(n, x)) << '\n';

	cout << '\n' << "\033[92m" "Выполнил: Смолин Артём Максимович\nГруппа: ИВТ2-Б22\n" "\033[97m";

	return 0;
}