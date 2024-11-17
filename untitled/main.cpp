#include <iostream>
#include <cmath>

const double FACTOR = 2 / sqrt(M_PI);
const double EPSILON = 1e-6;
const int N = 6;

double* tabulate(int a, int b, int n) {
    auto* result = new double[n];
    for (int i = 0; i < n; i++) {
        result[i] = static_cast<double>(b - a) / (n - 1)     * i;
    }

    return result;
}

double q_n(double x, double n) {
    double numerator = x * (2 * n + 1);
    double denominator = (n + 1) * (2 * n + 3);

    return -numerator / denominator;
}

double s_n(double x, double n) {
    double a_i = x;
    double result = a_i;

    for (int i = 1; i <= n; i++) {
        a_i *= q_n(x, i);
        result += a_i;
    }

    return result;
}

double s(double x, const double precision) {
    double prev = s_n(x, 0);
    double result = s_n(x, 1);
    int i = 2;

    while (std::abs(result - prev) > precision) {
        prev = result;
        result = s_n(x, i);
        i += 1;
    }

    return result;
}

int main() {
    auto* x_grid = tabulate(0, 2, N);
    auto* y_grid = new double[N];

    for (int i = 0; i < N; i++) {
        y_grid[i] = s(x_grid[i], EPSILON);
        std::cout << "f(" << x_grid[i] << ")\t=\t" << y_grid[i] << std::endl;
    }

    delete[] x_grid;
    return 0;
}
