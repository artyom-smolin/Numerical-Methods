#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

using vec = vector<double>;
// точность - 31 знак после запятой
#define M_PI 3.1415926535897932384626433832795
// длина всего отрезка
const double length_of_segment = 2 * M_PI;

// исходная функция
double Function(double x)
{
	return sqrt(2) - 2 * sin(x);
}

// создание узлов
void nodes(vec& X, vec& Y, int number_of_nodes)
{
	// число отрезков
	double number_of_segments = number_of_nodes - 1;

	// шаг отрезка
	double step = length_of_segment / number_of_segments;

	// формирование узлов и значений функции в узлах
	X[0] = -M_PI;
	Y[0] = Function(X[0]);
	for (size_t i = 1; i < number_of_nodes; ++i)
	{
		X[i] = X[i - 1] + step;
		Y[i] = Function(X[i]);
	}

	if (number_of_nodes == 7) X[3] = 0; // из-за неточности double выходит очень маленькое число, а должно 0

	cout << "Количество узлов: " "\033[94m" << number_of_nodes << "\033[97m\n";
	for (size_t i = 0; i < number_of_nodes; ++i)
	{
		cout << "x[" << i << "] = " << X[i] << '\t' << "y[" << i << "] = " << Y[i] << '\n';
	}
	cout << '\n';
}

// полином Лагранжа
double polinom_Lagrange(double x, vec& X, vec& Y, int number_of_nodes)
{
	double result = 0.0;

	for (size_t i = 0; i < number_of_nodes; ++i)
	{
		double P = 1.0;
		for (size_t j = 0; j < number_of_nodes; ++j)
		{
			if (i != j)
			{
				P *= (x - X[j]) / (X[i] - X[j]);
			}
		}
		result = result + Y[i] * P;
	}

	return result;
}

// вывод Полинома
void polinom_Lagrange_print(vec& X, vec& Y, int number_of_nodes, vec& L)
{
	// число отрезков
	double number_of_segments = number_of_nodes - 1;

	// шаг отрезка
	double step = length_of_segment / number_of_segments;

	vec X_local(number_of_nodes);
	// формирование узлов
	X_local[0] = -M_PI;
	for (size_t i = 1; i < number_of_nodes; ++i)
	{
		X_local[i] = X_local[i - 1] + step;
	}

	cout << "Количество узлов: " "\033[94m" << number_of_nodes << "\033[97m\n";
	for (size_t i = 0; i < number_of_nodes; ++i)
	{
		L[i] = polinom_Lagrange(X_local[i], X, Y, X.size());
		cout << "L_" << i << "(x[" << i << "]) = " << L[i] << '\n';
	}
	cout << '\n';
}

// кусочно-линейная функция
void KLF(vec& X, vec& Y, int number_of_nodes, vec& a, vec& b, vec& Y_other)
{
	double a_i, b_i;

	// решение системы двух уравнений
	for (size_t  i = 0; i < number_of_nodes - 1; ++i)
	{
		a[i] = (Y[i + 1] - Y[i]) / (X[i + 1] - X[i]);
		b[i] = Y[i] - a[i] * X[i];
	}

	/*cout << "Количество узлов: " "\033[94m" << number_of_nodes << "\033[97m\n";
	for (i = 0; i < number_of_nodes-1; ++i)
	{
		cout << "a[" << i << "] = " << a[i] << '\t' << "b[" << i << "] = " << b[i] << '\n';
	}
	cout << '\n';*/

	for (size_t i = 0; i < number_of_nodes; ++i)
	{
		if (i == 0)
			Y_other[i] = a[i] * X[i] + b[i];
		else
			Y_other[i] = a[i - 1] * X[i] + b[i - 1];
		cout << "x[" << i << "] = " << X[i] << '\t' << "y[" << i << "] = " << Y_other[i] << '\n';
	}
	cout << '\n';

}

// функция для генерации случайных чисел в диапазоне [min, max]
double random_double(double min, double max)
{
	return min + static_cast<double>(rand()) / RAND_MAX * (max - min);
}

// погрешности
void inaccuracy(vec& X, vec& Y, vec& a, vec& b, int number_of_nodes)
{
	cout << "Количество узлов: " "\033[94m" << number_of_nodes << "\033[97m\n";
	vec random_X(number_of_nodes); // Случайные x
	vec random_Y(number_of_nodes); // Значения функции в случайных точках
	vec random_L(number_of_nodes); // Значения полинома в случайных точках
	vec random_KLF(number_of_nodes); // Значения кусочно-линейной функции в случайных точках

	// Генерация случайных x, значений функции и КЛФ в 'x'
	for (size_t i = 0; i < number_of_nodes; ++i)
	{
		random_X[i] = random_double(-M_PI, M_PI);
		random_Y[i] = Function(random_X[i]);
		random_L[i] = polinom_Lagrange(random_X[i], X, Y, number_of_nodes);
		for (size_t j = 0; j < X.size() - 1; ++j)
		{
			if (random_X[i] >= X[j] && random_X[i] <= X[j + 1])
			{
				random_KLF[i] = a[j] * random_X[i] + b[j];
				break;
			}
		}
	}

	// Вывод погрешностей
	for (size_t i = 0; i < number_of_nodes; ++i)
	{
		cout << "в точке x[" << i << "] = " << random_X[i] << '\n';
		cout << "|f(x_" << i << ") - L_" << i << "(x[" << i << "])| = " << abs(random_Y[i] - random_L[i]) << '\n';
		cout << "|f(x_" << i << ") - KLF_" << i << "(x[" << i << "])| = " << abs(random_Y[i] - random_KLF[i]) << "\n\n";
	}
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ГЛАВНАЯ ФУНКЦИЯ ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int main()
{
	setlocale(LC_ALL, "rus");
	cout.precision(5);

	cout << "\033[92m" "Лабораторная работа №4: \"Интерполяция\"\n\n" "\033[97m";
	cout << "\033[94m" "f(x)" "\033[97m" " = sqrt(2) - 2 * sin(x)" << "\033[94m" "\t[-pi; pi]\n" "\033[97m";

	cout << '\n';
	cout << "\033[91m";
	system("pause");
	cout << "\033[97m";
	cout << '\n';

	// узлы и значения функции в узлах
	cout << "\033[94m" << "Исходные узлы:\n" << "\033[97m";
	vec x_5(5), x_7(7), x_10(10);
	vec y_5(5), y_7(7), y_10(10);
	nodes(x_5, y_5, 5);
	nodes(x_7, y_7, 7);
	nodes(x_10, y_10, 10);

	cout << "\033[91m";
	system("pause");
	cout << "\033[97m";
	cout << '\n';

	// значения Полинома в узлах
	cout << "\033[94m" << "Полином Лагранжа:\n" << "\033[97m";
	vec L_10(10), L_14(14), L_20(20);
	polinom_Lagrange_print(x_5, y_5, 10, L_10);
	polinom_Lagrange_print(x_7, y_7, 14, L_14);
	polinom_Lagrange_print(x_10, y_10, 20, L_20);

	cout << "\033[91m";
	system("pause");
	cout << "\033[97m";
	cout << '\n';

	// значения КЛФ
	cout << "\033[94m" << "Кусочно-линейная функция:\n" << "\033[97m";
	vec a_5(4), a_7(6), a_10(9);
	vec b_5(4), b_7(6), b_10(9);
	vec Y_other_5(5), Y_other_7(7), Y_other_10(10);
	KLF(x_5, y_5, 5, a_5, b_5, Y_other_5);
	KLF(x_7, y_7, 7, a_7, b_7, Y_other_7);
	KLF(x_10, y_10, 10, a_10, b_10, Y_other_10);

	cout << "\033[91m";
	system("pause");
	cout << "\033[97m";
	cout << '\n';

	// погрешности 
	cout << "\033[94m" << "Оценка погрешности:\n" << "\033[97m";
	inaccuracy(x_5, y_5, a_5, b_5, 5);
	inaccuracy(x_7, y_7, a_7, b_7, 7);
	inaccuracy(x_10, y_10, a_10, b_10, 10);

	cout << "\033[91m";
	system("pause");
	cout << "\033[97m";
	cout << '\n';

	cout << "\033[92m" "Выполнил: Смолин Артём Максимович\nГруппа: ИВТ2-Б22\n" "\033[97m";

	return 0;
}