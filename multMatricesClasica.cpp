#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <iomanip>

// Función para generar una matriz aleatoria de tamaño n x n
std::vector<std::vector<double>> generateRandomMatrix(int n) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    std::vector<std::vector<double>> matrix(n, std::vector<double>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            matrix[i][j] = dis(gen);
        }
    }
    return matrix;
}

// Función para multiplicar dos matrices
std::vector<std::vector<double>> multiplyMatrices(const std::vector<std::vector<double>>& A, 
                                                  const std::vector<std::vector<double>>& B) {
    int n = A.size();
    std::vector<std::vector<double>> C(n, std::vector<double>(n, 0.0));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

// Función para medir el tiempo de ejecución de la multiplicación de matrices
double measureMultiplicationTime(int size) {
    auto A = generateRandomMatrix(size);
    auto B = generateRandomMatrix(size);

    auto start = std::chrono::high_resolution_clock::now();
    auto C = multiplyMatrices(A, B);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> diff = end - start;
    return diff.count();
}

int main() {
    std::vector<int> sizes = {100, 200, 300, 400, 500};

    std::cout << std::setw(10) << "Size" << std::setw(20) << "Time (seconds)" << std::endl;
    std::cout << std::string(30, '-') << std::endl;

    for (int size : sizes) {
        double time = measureMultiplicationTime(size);
        std::cout << std::setw(10) << size << std::setw(20) << std::fixed << std::setprecision(6) << time << std::endl;
    }

    return 0;
}