#include <iostream>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Función para la multiplicación de matrices clásica (tres bucles anidados)
void matrixMultiplyClassic(const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>& C, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            C[i][j] = 0;
            for (int k = 0; k < n; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Función para la multiplicación de matrices por bloques (seis bucles anidados)
void matrixMultiplyBlock(const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>& C, int n, int blockSize) {
    for (int i = 0; i < n; i += blockSize) {
        for (int j = 0; j < n; j += blockSize) {
            for (int k = 0; k < n; k += blockSize) {
                // Multiplica los bloques
                for (int ii = i; ii < min(i + blockSize, n); ++ii) {
                    for (int jj = j; jj < min(j + blockSize, n); ++jj) {
                        for (int kk = k; kk < min(k + blockSize, n); ++kk) {
                            C[ii][jj] += A[ii][kk] * B[kk][jj];
                        }
                    }
                }
            }
        }
    }
}

int main() {
    // Tamaño de la matriz (n x n)
    int n = 512;
    int blockSize = 64; // Tamaño de bloque

    // Inicialización de matrices
    vector<vector<int>> A(n, vector<int>(n, 1));
    vector<vector<int>> B(n, vector<int>(n, 1));
    vector<vector<int>> C_classic(n, vector<int>(n, 0));
    vector<vector<int>> C_block(n, vector<int>(n, 0));

    // Multiplicación clásica
    auto startClassic = high_resolution_clock::now();
    matrixMultiplyClassic(A, B, C_classic, n);
    auto endClassic = high_resolution_clock::now();
    auto durationClassic = duration_cast<milliseconds>(endClassic - startClassic).count();

    // Multiplicación por bloques
    auto startBlock = high_resolution_clock::now();
    matrixMultiplyBlock(A, B, C_block, n, blockSize);
    auto endBlock = high_resolution_clock::now();
    auto durationBlock = duration_cast<milliseconds>(endBlock - startBlock).count();

    // Comparar tiempos
    cout << "Tiempo de multiplicacion clasica: " << durationClassic << " ms" << endl;
    cout << "Tiempo de multiplicacion por bloques: " << durationBlock << " ms" << endl;

    return 0;
}
