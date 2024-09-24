#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>

const int MAX = 1000; // Tamaño de la matriz y vectores

void firstPairOfLoops(const std::vector<std::vector<int>>& A, const std::vector<int>& x, std::vector<int>& y) {
    for (int i = 0; i < MAX; ++i)
        for (int j = 0; j < MAX; ++j)
            y[i] += A[i][j] * x[j];
}

void secondPairOfLoops(const std::vector<std::vector<int>>& A, const std::vector<int>& x, std::vector<int>& y) {
    for (int j = 0; j < MAX; ++j)
        for (int i = 0; i < MAX; ++i)
            y[i] += A[i][j] * x[j];
}

int main() {
    std::vector<std::vector<int>> A(MAX, std::vector<int>(MAX, 1));
    std::vector<int> x(MAX, 1), y1(MAX, 0), y2(MAX, 0);

    auto start = std::chrono::high_resolution_clock::now();
    firstPairOfLoops(A, x, y1);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration1 = std::chrono::duration<double, std::milli>(end - start);

    start = std::chrono::high_resolution_clock::now();
    secondPairOfLoops(A, x, y2);
    end = std::chrono::high_resolution_clock::now();
    auto duration2 = std::chrono::duration<double, std::milli>(end - start);

    std::cout << std::fixed << std::setprecision(3);
    std::cout << "Tiempo del primer par de bucles: " << duration1.count() << " ms\n";
    std::cout << "Tiempo del segundo par de bucles: " << duration2.count() << " ms\n";


    return 0;
}