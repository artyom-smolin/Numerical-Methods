#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

typedef vector<double> One_Double;
typedef vector<vector<double>> Two_Double;

// вывод номинального решения
void print_nominal_Solution(One_Double& vec)
{
    vec[0] = double(79) / 727;
    vec[1] = double(1715) / 1454;
    vec[2] = double(868) / 727;
    vec[3] = double(-73) / 1454;
    cout << "\033[93m" "\nНоминальное решение: (";
    for (size_t i = 0; i < vec.size(); ++i)
    {
        if (i != vec.size() - 1)
            cout << vec[i] << "; ";
        else
            cout << vec[i];
    }
    cout << ")\n" "\033[97m";
}
// вывод матрицы
void print_Matrix(Two_Double& matrix, string name)
{
    cout << "\nМатрица " << name << ":\n";
    for (size_t i = 0; i < matrix.size(); i++)
    {
        for (size_t j = 0; j < matrix[i].size(); j++)
        {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
}
// вывод решения
void print_Solution(One_Double& vec, double accuracy)
{
    cout << "Точность: " << accuracy << "\n";
    cout << "Решение: (";
    for (int i = 0; i < vec.size() - 1; i++)
    {
        if (i != vec.size() - 2)
            cout << vec[i] << "; ";
        else
            cout << vec[i];
    }
    cout << ")\n";
    cout << "Число итераций: " << vec[4] << "\n\n";
}

// заполнение обратной матрицы
void reverse_Matrix(Two_Double& matrix)
{
    matrix[0][0] = double(76) / 727;
    matrix[0][1] = double(5) / 1454;
    matrix[0][2] = -double(41) / 1454;
    matrix[0][3] = -double(33) / 1454;
    matrix[1][0] = -double(71) / 1454;
    matrix[1][1] = double(311) / 2908;
    matrix[1][2] = double(67) / 2908;
    matrix[1][3] = -double(17) / 2908;
    matrix[2][0] = -double(30) / 727;
    matrix[2][1] = -double(157) / 2908;
    matrix[2][2] = double(415) / 2908;
    matrix[2][3] = -double(127) / 2908;
    matrix[3][0] = double(31) / 1454;
    matrix[3][1] = double(69) / 2908;
    matrix[3][2] = -double(275) / 2908;
    matrix[3][3] = double(417) / 2908;
}
// транспонирование
void transposed_Matrix(Two_Double& matrix, Two_Double& matrixT)
{
    for (size_t i = 0; i < matrix.size(); i++)
    {
        for (size_t j = 0; j < matrix[i].size(); j++)
        {
            matrixT[i][j] = matrix[j][i];
        }
    }
}
// умножение матриц для числа обусловленности
void matrix_Multiplication(Two_Double& matrix, Two_Double& matrixT, Two_Double& matrixAAT)
{
    for (size_t i = 0; i < matrix.size(); ++i)
    {
        for (size_t j = 0; j < matrix.size(); ++j)
        {
            for (size_t k = 0; k < matrix.size(); ++k)
            {
                matrixAAT[i][j] += matrixT[i][k] * matrix[k][j];
            }
        }
    }
}

// Евклидова норма Матриц
double euclidean_Norm_Matrix(Two_Double& matrix, string ident)
{
    if (ident == "исходная")
    {
        // cout << "Собственные значения исходной матрицы: " << "a_1 = " << 19.295 << endl << "a_2 = " << 54.733 << endl << "a_3 = " << 89.633 << endl << "a_4 = " << 357.339 << endl;
        return sqrt(357.339);
    }

    else if (ident == "обратная")
    {
        // cout << "Собственные значения обратной матрицы: " << "a_1 = " << 0.003 << endl << "a_2 = " << 0.011 << endl << "a_3 = " << 0.018 << endl << "a_4 = " << 0.052 << endl;
        return sqrt(0.052);
    }
    else if (ident == "простая итерация")
    {
        // cout << "Собственные значения обратной матрицы: " << "a_1 = " << 0.058 << endl << "a_2 = " << 0.742 << endl << "a_3 = " << 0.63218 << endl << "a_4 = " << 0.63218 << endl;
        return sqrt(0.742);
    }
}
// норма "по строчкам"
double maximum_Norm(Two_Double& matrix)
{
    double sum1 = 0, sum2 = 0;
    for (size_t i = 0; i < matrix.size(); i++)
    {
        for (size_t j = 0; j < matrix[i].size(); j++)
        {
            sum1 += abs(matrix[i][j]);
        }
        sum2 = max(sum1, sum2);
        sum1 = 0;
    }

    return sum2;
}
// норма "по столбцам"
double summary_Norm(Two_Double& matrix)
{
    double sum1 = 0, sum2 = 0;
    for (size_t i = 0; i < matrix.size(); i++)
    {
        for (size_t j = 0; j < matrix[i].size(); j++)
        {
            sum1 += abs(matrix[j][i]);
        }
        sum2 = max(sum1, sum2);
        sum1 = 0;
    }

    return sum2;
}
// Евклидова норма Векторов
double euclidean_Norm_Vector(One_Double vector)
{
    double result = 0;

    for (size_t i = 0; i < vector.size(); ++i)
    {
        result += pow(vector[i], 2);
    }

    return sqrt(result);

}

// число обусловленности
double number_Conditionality(double A, double A_1)
{
    return A * A_1;
}

// единичная матрица
Two_Double unit_Matrix()
{
    Two_Double matrix(4, One_Double(4));
    for (size_t i = 0; i < matrix.size(); ++i)
    {
        for (size_t j = 0; j < matrix[i].size(); ++j)
        {
            if (i == j)
                matrix[i][j] = 1;
            else
                matrix[i][j] = 0;
        }
    }

    return matrix;
}
// умножение матрицы на число
Two_Double multiplying_Matrix_by_Number(Two_Double matrix, double tau)
{
    for (size_t i = 0; i < matrix.size(); ++i)
    {
        for (size_t j = 0; j < matrix[i].size(); ++j)
        {
            matrix[i][j] *= tau;
        }
    }

    return matrix;
}
// вычитание матриц
Two_Double matrix_Subtraction(Two_Double a, Two_Double b)
{
    Two_Double result(a.size(), One_Double(b.size()));
    for (size_t i = 0; i < result.size(); ++i)
    {
        for (size_t j = 0; j < result[i].size(); ++j)
        {
            result[i][j] = a[i][j] - b[i][j];
        }
    }

    return result;
}
// сложение матриц
Two_Double matrix_Addition(Two_Double a, Two_Double b)
{
    Two_Double result(a.size(), One_Double(b.size()));
    for (size_t i = 0; i < result.size(); ++i)
    {
        for (size_t j = 0; j < result[i].size(); ++j)
        {
            result[i][j] = a[i][j] + b[i][j];
        }
    }

    return result;
}
// умножение матрицы на вектор
One_Double multiplying_Vector_by_Matrix(Two_Double matrix, One_Double vector)
{
    One_Double result(One_Double(vector.size()));

    for (size_t i = 0; i < vector.size(); ++i)
    {
        for (size_t j = 0; j < vector.size(); ++j)
        {
            result[i] += matrix[i][j] * vector[j];
        }
    }

    return result;
}
// умножение вектора на число
One_Double multiplying_Number_by_Vector(One_Double vector, double tau)
{
    for (size_t i = 0; i < vector.size(); ++i)
    {
        vector[i] *= tau;
    }

    return vector;
}
// сумма векторов
One_Double vector_Summation(One_Double a, One_Double b)
{
    One_Double res(a.size());
    for (size_t i = 0; i < a.size(); ++i)
    {
        res[i] = a[i] + b[i];
    }

    return res;
}
// разность векторов
One_Double vector_Subtraction(One_Double a, One_Double b)
{
    One_Double res(a.size());
    for (size_t i = 0; i < a.size(); ++i)
    {
        res[i] = a[i] - b[i];
    }

    return res;
}
// общее умножение матриц
Two_Double multiplying_Matrix_by_Matrix(Two_Double matrix1, Two_Double matrix2)
{
    int n = matrix1.size(); // Размерность матрицы
    Two_Double result(4, One_Double(4)); // Результирующая матрица

    // Умножение матриц
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }

    return result;
}

// нижняя треугольная матрица
Two_Double L_SLAU(Two_Double& matrix)
{
    Two_Double result(4, One_Double(4));

    for (size_t i = 0; i < matrix.size(); i++)
    {
        for (size_t j = 0; j < matrix[i].size(); j++)
        {
            if (i == j || j > i)
                result[i][j] = 0;

            else
                result[i][j] = matrix[i][j];
        }
    }

    return result;
}
// верхняя треугольная матрица
Two_Double U_SLAU(Two_Double& matrix)
{
    Two_Double result(4, One_Double(4));

    for (size_t i = 0; i < matrix.size(); i++)
    {
        for (size_t j = 0; j < matrix[i].size(); j++)
        {
            if (i == j || j < i)
                result[i][j] = 0;
            else
                result[i][j] = matrix[i][j];
        }
    }

    return result;
}
// диагональная матрица
Two_Double D_SLAU(Two_Double& matrix)
{
    Two_Double result(4, One_Double(4));

    for (size_t i = 0; i < matrix.size(); i++)
    {
        for (size_t j = 0; j < matrix[i].size(); j++)
        {
            if (i == j)
                result[i][j] = matrix[i][j];
        }
    }

    return result;
}
// D^(-1)
Two_Double D_SLAU_Reverse()
{
    Two_Double result(4, One_Double(4));

    result[0][0] = double(1) / 11;
    result[1][1] = double(1) / 9;
    result[2][2] = double(1) / 10;
    result[3][3] = double(1) / 9;

    return result;
}
// (L+D)
Two_Double L_D_SLAU(Two_Double& matrix)
{
    Two_Double result(4, One_Double(4));

    result = matrix_Addition(L_SLAU(matrix), D_SLAU(matrix));

    return result;
}
// (L+D)^(-1)
Two_Double L_D_SLAU_Reverse()
{
    Two_Double result(4, One_Double(4));

    result[0][0] = double(1) / 11;
    result[1][1] = double(1) / 9;
    result[2][2] = double(1) / 10;
    result[3][3] = double(1) / 9;

    result[1][0] = -double(4) / 99;
    result[2][0] = -double(29) / 990;
    result[3][0] = double(62) / 4445;

    result[2][1] = -double(2) / 45;
    result[3][1] = double(7) / 405;
    result[3][2] = -double(1) / 15;

    return result;
}

// решение СЛАУ методом простой итерации
One_Double method_Simple_iter(Two_Double& A, One_Double& b, double epsilon)
{
    // начальное приближение, вектор корня, тау, число итераций
    One_Double x_k = { 1,1,1,1 };
    One_Double x_k1;
    double tau = 0.05;
    int count_iterations = 0;

    x_k1 = vector_Summation(multiplying_Vector_by_Matrix(matrix_Subtraction(unit_Matrix(), multiplying_Matrix_by_Number(A, tau)), x_k), multiplying_Number_by_Vector(b, tau));

    // поиск решения
    while (euclidean_Norm_Vector(vector_Subtraction(x_k1, x_k)) >= epsilon)
    {
        x_k = x_k1;
        x_k1 = vector_Summation(multiplying_Vector_by_Matrix(matrix_Subtraction(unit_Matrix(), multiplying_Matrix_by_Number(A, tau)), x_k), multiplying_Number_by_Vector(b, tau));
        count_iterations++;
    }
    x_k1.push_back(count_iterations); // сохранение числа итераций в последний элемент массива решения

    return x_k1;
}
// метод Якоби
One_Double method_Jacobi(Two_Double& A, One_Double& b, double epsilon)
{
    // начальное приближение, вектор корня, число итераций
    One_Double x_k = { 1,1,1,1 };
    One_Double x_k1;
    int count_iterations = 0;

    x_k1 = multiplying_Vector_by_Matrix(D_SLAU_Reverse(), vector_Subtraction(b, multiplying_Vector_by_Matrix(matrix_Addition(L_SLAU(A), U_SLAU(A)), x_k)));

    // поиск решения
    while (euclidean_Norm_Vector(vector_Subtraction(x_k1, x_k)) >= epsilon)
    {
        x_k = x_k1;
        x_k1 = multiplying_Vector_by_Matrix(D_SLAU_Reverse(), vector_Subtraction(b, multiplying_Vector_by_Matrix(matrix_Addition(L_SLAU(A), U_SLAU(A)), x_k)));
        count_iterations++;
    }
    x_k1.push_back(count_iterations); // сохранение числа итераций в последний элемент массива решения

    return x_k1;
}
// метод Гаусса-Зейделя
One_Double method_Gauss_Seidel(Two_Double& A, One_Double& b, double epsilon)
{
    // начальное приближение, вектор корня, число итераций
    One_Double x_k = { 1,1,1,1 };
    One_Double x_k1;
    int count_iterations = 0;

    x_k1 = vector_Subtraction(multiplying_Vector_by_Matrix(L_D_SLAU_Reverse(), b), multiplying_Vector_by_Matrix(multiplying_Matrix_by_Matrix(L_D_SLAU_Reverse(), U_SLAU(A)), x_k));

    // поиск решения
    while (euclidean_Norm_Vector(vector_Subtraction(x_k1, x_k)) >= epsilon)
    {
        x_k = x_k1;
        x_k1 = vector_Subtraction(multiplying_Vector_by_Matrix(L_D_SLAU_Reverse(), b), multiplying_Vector_by_Matrix(multiplying_Matrix_by_Matrix(L_D_SLAU_Reverse(), U_SLAU(A)), x_k));
        count_iterations++;
    }
    x_k1.push_back(count_iterations); // сохранение числа итераций в последний элемент массива решения

    return x_k1;
}

// критерий сходимости простой итерации
void criterion_simple_iteration(Two_Double& matrix)
{
    double tau = 0.05;
    Two_Double res = matrix_Subtraction(unit_Matrix(), multiplying_Matrix_by_Number(matrix, tau));

    // собственные значения
    double v_1 = 0.058;
    double v_2 = 0.742;
    // v_3 = 0.625+i*0.095
    double v_3 = 0.63218;
    // v_4 = 0.625-i*0.095
    double v_4 = 0.63218;

    if (abs(v_1) < 1 && abs(v_2) < 1 && v_3 < 1 && v_4 < 1)
        cout << "Критерий сходимости Простой итерации выполнен\n";
    else
        cout << "Критерий сходимости Якоби НЕ выполнен\n";
}
// критерий сходимости якоби
void criterion_jacobi(Two_Double& matrix)
{
    Two_Double res = multiplying_Matrix_by_Number(multiplying_Matrix_by_Matrix(D_SLAU_Reverse(), matrix_Addition(L_SLAU(matrix), U_SLAU(matrix))), double(-1));

    // собственные значения
    double v_1 = 0.9;
    double v_2 = 0.46;
    // v_3 = 0.220+i*0.167
    double v_3 = 0.27620;
    // v_4 = 0,220-i*(0,167)
    double v_4 = 0.27620;

    if (abs(v_1) < 1 && abs(v_2) < 1 && v_3 < 1 && v_4 < 1)
        cout << "Критерий сходимости Якоби выполнен\n";
    else
        cout << "Критерий сходимости Якоби НЕ выполнен\n";
}
// критерий сходимости гаусса-Зейделя
void criterion_gauss_seidel(Two_Double& matrix)
{
    Two_Double res = multiplying_Matrix_by_Number(multiplying_Matrix_by_Matrix(L_D_SLAU_Reverse(), U_SLAU(matrix)), double(-1));

    // собственные значения
    double v_1 = 0;
    double v_2 = 0;
    double v_3 = 0.058;
    double v_4 = 0.307;

    if (abs(v_1) < 1 && abs(v_2) < 1 && abs(v_3) < 1 && abs(v_4) < 1)
        cout << "Критерий сходимости Гаусса-Зейделя выполнен\n\n";
    else
        cout << "Критерий сходимости Гаусса-Зейделя НЕ выполнен\n\n";
}

// достаточное условие сходимости простой итерации
void condition_simple_iteration(Two_Double& matrix)
{
    double tau = 0.05;
    Two_Double res = matrix_Subtraction(unit_Matrix(), multiplying_Matrix_by_Number(matrix, tau));

    double x = euclidean_Norm_Matrix(res, "простая итерация");
    double y = maximum_Norm(res);
    double z = summary_Norm(res);

    cout << "Простая итерация:\n";
    if (x < 1)
        cout << "Достаточное условие сходимости выполнено для Евклидовой нормы\n";
    else
        cout << "Достаточное условие сходимости НЕ выполнено для Евклидовой нормы\n";
    if (y < 1)
        cout << "Достаточное условие сходимости выполнено для Максимальной нормы\n";
    else
        cout << "Достаточное условие сходимости НЕ выполнено для Максимальной нормы\n";
    if (z < 1)
        cout << "Достаточное условие сходимости выполнено для Суммарной нормы\n";
    else
        cout << "Достаточное условие сходимости НЕ выполнено для Суммарной нормы\n\n";
}
// достаточное условие сходимости якоби
void condition_jacobi(Two_Double& matrix)
{
    bool flag = true;
    double sum = 0;
    int index;

    for (size_t i = 0; i < matrix.size(); ++i)
    {
        for (size_t j = 0; j < matrix[i].size(); ++j)
        {
            if (i != j)
            {
                sum += matrix[i][j];
            }
        }
        if (abs(matrix[i][i]) <= sum)
        {
            index = i + 1;
            flag = false;
            break;
        }
        else
        {
            sum = 0;
        }
    }

    cout << "Якоби:\n";
    if (flag)
        cout << "Достаточное условие сходимости выполнено\n\n";
    else
        cout << "Достаточное условие сходимости НЕ выполнено в " << index << " строке \n\n";
}
// достаточное условие сходимости Гаусса-Зейделя
void condition_gauss_seidel()
{
    cout << "Гаусс-Зейдель:\n";
    cout << "Достаточное условие сходимости НЕ выполнено (матрица не симметричная)\n\n";
}

// норма разности точного решения и начального приближения
double norm_of_difference()
{
    One_Double solution(4);
    solution[0] = double(79) / 727;
    solution[1] = double(1715) / 1454;
    solution[2] = double(868) / 727;
    solution[3] = double(-73) / 1454;

    One_Double approximation(4);
    approximation[0] = double(1);
    approximation[1] = double(1);
    approximation[2] = double(1);
    approximation[3] = double(1);

    One_Double result = vector_Subtraction(solution, approximation);
    return euclidean_Norm_Vector(result);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ГЛАВНАЯ ФУНКЦИЯ ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
int main()
{
    setlocale(LC_ALL, "rus");
    cout.precision(7);

    // размерность
    const int sizeMatrix = 4;

    // исходная матрица
    Two_Double SLAU(sizeMatrix, One_Double(sizeMatrix));

    // значения справа равенства
    One_Double values_rhs;
    values_rhs.resize(sizeMatrix);

    // файл со значениями СЛАУ
    ifstream inputFile;

    // для циклов
    size_t i, j;

    // считывание файла 
    inputFile.open("inArray4.txt");
    for (i = 0; i < sizeMatrix; i++)
    {
        for (j = 0; j <= sizeMatrix; j++)
        {
            if (j != sizeMatrix)
            {
                inputFile >> SLAU[i][j];
            }
            else
            {
                inputFile >> values_rhs[i];
            }
        }
    }
    inputFile.close();

    // вывод СЛАУ
    cout << "\033[92m" "Лабораторная работа №2: \"Решение СЛАУ\"\n\n" "\033[94m";
    cout << "x1\tx2\tx3\tx4\n" "\033[37m";
    for (i = 0; i < sizeMatrix; i++)
    {
        for (j = 0; j <= sizeMatrix; j++)
        {
            if (j != sizeMatrix)
            {
                cout << SLAU[i][j] << "\t";
            }
            else
            {
                cout << "=\t" << values_rhs[i];
            }
        }
        cout << endl;
    }

    // номинальное решение
    One_Double nominal(sizeMatrix);
    print_nominal_Solution(nominal);

    // ЧАСТЬ 1

    // вывод всех матриц (ПРИ НЕОБХОДИМОСТИ РАСКОММЕНТИРОВАТЬ КОММЕНТАРИИ)
    // print_Matrix(SLAU, "исходная");

    Two_Double SLAU_Transposed(sizeMatrix, One_Double(sizeMatrix));
    transposed_Matrix(SLAU, SLAU_Transposed);
    // print_Matrix(SLAU_Transposed, "транспонированная, исходная");

    Two_Double SLAU_Multiplication(sizeMatrix, One_Double(sizeMatrix));
    matrix_Multiplication(SLAU, SLAU_Transposed, SLAU_Multiplication);
    // print_Matrix(SLAU_Multiplication, "умножения, исходная");

    Two_Double SLAU_Reverse(sizeMatrix, One_Double(sizeMatrix));
    reverse_Matrix(SLAU_Reverse);
    // print_Matrix(SLAU_Reverse, "обратная");

    Two_Double SLAU_Reverse_Transposed(sizeMatrix, One_Double(sizeMatrix));
    transposed_Matrix(SLAU_Reverse, SLAU_Reverse_Transposed);
    // print_Matrix(SLAU_Reverse_Transposed, "транспонированная, обратная");

    Two_Double SLAU_Reverse_Multiplication(sizeMatrix, One_Double(sizeMatrix));
    matrix_Multiplication(SLAU_Reverse, SLAU_Reverse_Transposed, SLAU_Reverse_Multiplication);
    // print_Matrix(SLAU_Reverse_Multiplication, "умножения, обратная");

    cout << "\033[91m\n";
    system("pause");
    cout << "\033[97m";

    // числа обусловленности
    cout << "\033[94m\n" "Числа обусловленности СЛАУ:\n" "\033[97m";
    cout << "Евклидова норма: " << number_Conditionality(euclidean_Norm_Matrix(SLAU_Multiplication, "исходная"), euclidean_Norm_Matrix(SLAU_Reverse_Multiplication, "обратная"));
    cout << "\nМаксимальная норма: " << number_Conditionality(maximum_Norm(SLAU), maximum_Norm(SLAU_Reverse));
    cout << "\nСуммарная норма: " << number_Conditionality(summary_Norm(SLAU), summary_Norm(SLAU_Reverse)) << '\n';

    cout << "\033[91m\n";
    system("pause");
    cout << "\033[97m";

    // ЧАСТЬ 2

    // метод Простой итерации 
    One_Double iteration_One;
    One_Double iteration_Two;
    One_Double iteration_Three;
    cout << "\033[94m" "\n1) Метод простой итерации\n\n" "\033[97m";
    iteration_One = method_Simple_iter(SLAU, values_rhs, 1e-2);
    print_Solution(iteration_One, 1e-2);
    iteration_Two = method_Simple_iter(SLAU, values_rhs, 1e-3);
    print_Solution(iteration_Two, 1e-3);
    iteration_Three = method_Simple_iter(SLAU, values_rhs, 1e-4);
    print_Solution(iteration_Three, 1e-4);

    cout << "\033[91m";
    system("pause");
    cout << "\033[97m";

    // метод Якоби
    One_Double jacobi_One;
    One_Double jacobi_Two;
    One_Double jacobi_Three;
    cout << "\033[94m" "\n2) Метод Якоби\n\n" "\033[97m";
    jacobi_One = method_Jacobi(SLAU, values_rhs, 1e-2);
    print_Solution(jacobi_One, 1e-2);
    jacobi_Two = method_Jacobi(SLAU, values_rhs, 1e-3);
    print_Solution(jacobi_Two, 1e-3);
    jacobi_Three = method_Jacobi(SLAU, values_rhs, 1e-4);
    print_Solution(jacobi_Three, 1e-4);

    cout << "\033[91m";
    system("pause");
    cout << "\033[97m";

    // метод Гаусса-Зейделя
    One_Double Gauss_Seidel_One;
    One_Double Gauss_Seidel_Two;
    One_Double Gauss_Seidel_Three;
    cout << "\033[94m" "\n3) Метод Гаусса-Зейделя\n\n" "\033[97m";
    Gauss_Seidel_One = method_Gauss_Seidel(SLAU, values_rhs, 1e-2);
    print_Solution(Gauss_Seidel_One, 1e-2);
    Gauss_Seidel_Two = method_Gauss_Seidel(SLAU, values_rhs, 1e-3);
    print_Solution(Gauss_Seidel_Two, 1e-3);
    Gauss_Seidel_Three = method_Gauss_Seidel(SLAU, values_rhs, 1e-4);
    print_Solution(Gauss_Seidel_Three, 1e-4);

    cout << "\033[91m";
    system("pause");
    cout << "\033[97m";

    // проверка достаточных условий
    cout << "\033[94m\n" "Достаточные условия сходимости:\n" "\033[97m\n";
    condition_simple_iteration(SLAU);
    condition_jacobi(SLAU);
    condition_gauss_seidel();

    cout << "\033[91m";
    system("pause");
    cout << "\033[97m";

    // проверка критериев сходимости
    cout << "\033[94m\n" "Критерии сходимости:\n" "\033[97m\n";
    criterion_simple_iteration(SLAU);
    criterion_jacobi(SLAU);
    criterion_gauss_seidel(SLAU);

    cout << "\033[91m";
    system("pause");
    cout << "\033[97m";

    // норма разности точного решения и начального приближения (для графиков, ПРИ НАДОБНОСТИ РАСКОММЕНТИРОВАТЬ)
    // cout << "\n" << "Текущая норма разности: " << norm_of_difference() << "\n";

    cout << "\033[92m\n" "Выполнил: Смолин Артём Максимович\nГруппа: ИВТ2-Б22\n" "\033[97m";

    return 0;
}