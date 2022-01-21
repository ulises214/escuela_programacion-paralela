/**
 * @file extra.cpp
 * @author Ulises Rafael Ramírez Martínez 5G
 * @date 2022-01-21
 *
 */
#include "iostream"
#include "stdlib.h"
#include "time.h"
#include <mpi.h>
using namespace std;
int main(int argc, char **argv) {

  int procsCount, currProc;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &currProc);
  MPI_Comm_size(MPI_COMM_WORLD, &procsCount);

  const float scalarNumber = 5.45;
  const int matrixSize = 200;
  const int rootProc = 0;

  if (!(matrixSize % procsCount == 0)) {
    cout << "El número de procesos no es divisible entre el número de filas"
         << endl;
    MPI_Finalize();
    return -1;
  }

  const int rowsByProc = matrixSize / procsCount;
  int matrix[matrixSize][matrixSize];
  float resultMatrix[matrixSize][matrixSize];
  float localResultMatrix[rowsByProc][matrixSize];
  int localMatrix[rowsByProc][matrixSize];
  double initialTime, finalTime, totalTime;

  if (currProc == rootProc) {
    srand(time(NULL));
    for (int i = 0; i < matrixSize; i++) {
      for (int j = 0; j < matrixSize; j++) {
        matrix[i][j] = rand() % 1000;
      }
    }
    initialTime = MPI_Wtime();
  }

  MPI_Scatter(matrix, rowsByProc * matrixSize, MPI_INT, localMatrix,
              rowsByProc * matrixSize, MPI_INT, rootProc, MPI_COMM_WORLD);

  for (int i = 0; i < rowsByProc; i++) {
    for (int j = 0; j < matrixSize; j++) {
      localResultMatrix[i][j] = localMatrix[i][j] * scalarNumber;
    }
  }

  MPI_Gather(localResultMatrix, rowsByProc * matrixSize, MPI_FLOAT,
             resultMatrix, rowsByProc * matrixSize, MPI_FLOAT, rootProc,
             MPI_COMM_WORLD);

  if (currProc == rootProc) {
    finalTime = MPI_Wtime();
    totalTime = finalTime - initialTime;
    cout << "Tiempo total: " << totalTime << endl;
    // cout << "Resultado: " << globalSum << endl;
  }
  MPI_Finalize();
}