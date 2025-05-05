#include <iostream>
#include <vector>
#include <windows.h>
#include <cmath>

using namespace std;

//во-первых, прога написана с учетом того, что в условии очепятка (функция Розенброка не так записана)
//то же самое, что с параболической функцией, но градиент другой, шаги помельче
//итераций нужно больше на порядок
//до N = 6 алгоритм Нолдера-Мида предпочтительнее, градиент не очень хорошо ищет минимум

double rosenbrockBanananana(const vector<double>& x) {
    double sum = 0.0;
    for (size_t i = 0; i < x.size() - 1; ++i) {
        double term1 = 100.0 * pow(x[i + 1] - x[i] * x[i], 2);
        double term2 = pow(1.0 - x[i], 2);
        sum += term1 + term2;
    }
    return sum;
}

vector<double> gradient(const vector<double>& x) {
    int n = x.size();
    vector<double> grad(n, 0.0);
    for (int i = 0; i < n - 1; ++i) {
        grad[i] = -400.0 * x[i] * (x[i + 1] - x[i] * x[i]) + 2.0 * (x[i] - 1.0); //производные, считались ручками
        grad[i + 1] = 200.0 * (x[i + 1] - x[i] * x[i]);
    }
    return grad;
}

int main() {
    SetConsoleOutputCP(CP_UTF8);

    int n, iterat;
    double xMin, xMax, step;
    cout << "введите N (размерность) и область поиска решения (минимальный и максимальный x): " << endl;
    cin >> n >> xMin >> xMax;
    cout << "и еще число итераций алгоритма (от 1000 желательно): " << endl;
    cin >> iterat;
    cout << "и шаг спуска (желательно меньше 0.001): " << endl;
    cin >> step;

    /*
    n = 2;
     xMin = -1; xMax = 1;
     iterat = 10000;
     step = 0.00001;
     */

    if (n <= 1) n = 2; //защита от некорректного ввода
    if (xMin >= xMax) {
        xMin = -2.0;
        xMax = 2.0;
    }
    if (iterat < 100) iterat = 1000;
    if (step <= 0) step = 0.001;

    vector<double> x(n, 0.0);
    double f = rosenbrockBanananana(x);

    for (int iter = 0; iter < iterat; ++iter) {
        vector<double> grad = gradient(x);
        for (int i = 0; i < n; ++i) {
            x[i] -= step * grad[i]; //антиградиент
            if (x[i] < xMin) x[i] = xMin; //не выходим за область поиска
            if (x[i] > xMax) x[i] = xMax;
        }
        f = rosenbrockBanananana(x); //считаем функцию в найденном минимуме
    }

    cout << "Найденный минимум: (";
    for (int i = 0; i < n; ++i) {
        cout << x[i];
        if (i < n - 1) cout << ", ";
    }
    cout << "). " << endl << "Значение функции в минимуме: " << f << endl;

    return 0;
}