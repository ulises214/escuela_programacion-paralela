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

  // Se inicializan las variables relacionadas con el MPI
  const int rootProc = 0;
  int procsCount, currProc;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &currProc);
  MPI_Comm_size(MPI_COMM_WORLD, &procsCount);

  // Se definen las contantes que se utilizarán en el programa
  const float scalarNumber = 5.45;
  const int matrixSize = 200;
  // Se realiza una clausura para evitar que el programa se detenga
  // en caso de que el numero de fuilas dee la matriz no sea divisible
  //  entre el numero de procesos
  if (!(matrixSize % procsCount == 0)) {
    cout << "El número de procesos no es divisible entre el número de filas"
         << endl;
    MPI_Finalize();
    return -1;
  }

  // Se definen las variables que se utilizarán en el programa
  const int rowsByProc = matrixSize / procsCount;
  int matrix[matrixSize][matrixSize];
  float resultMatrix[matrixSize][matrixSize];
  float localResultMatrix[rowsByProc][matrixSize];
  int localMatrix[rowsByProc][matrixSize];

  // Se inicializan las variables de control para el tiempo
  double initialTime, finalTime, totalTime;

  // En caso de ser el proceso raíz se rellana la matriz con números aleatorios
  if (currProc == rootProc) {
    srand(time(NULL));
    for (int i = 0; i < matrixSize; i++) {
      for (int j = 0; j < matrixSize; j++) {
        matrix[i][j] = rand() % 1000;
      }
    }
    initialTime = MPI_Wtime();
  }

  // Se divide la matriz entre los procesos
  MPI_Scatter(matrix, rowsByProc * matrixSize, MPI_INT, localMatrix,
              rowsByProc * matrixSize, MPI_INT, rootProc, MPI_COMM_WORLD);

  // Se realiza el producto escalar de cada uno de los vectores locales
  for (int i = 0; i < rowsByProc; i++) {
    for (int j = 0; j < matrixSize; j++) {
      localResultMatrix[i][j] = localMatrix[i][j] * scalarNumber;
    }
  }
  // Se junta la matriz resultante de cada proceso
  MPI_Gather(localResultMatrix, rowsByProc * matrixSize, MPI_FLOAT,
             resultMatrix, rowsByProc * matrixSize, MPI_FLOAT, rootProc,
             MPI_COMM_WORLD);
  // Se imprime el tiempo total de ejecución
  if (currProc == rootProc) {
    finalTime = MPI_Wtime();
    totalTime = finalTime - initialTime;
    cout << "Tiempo total: " << totalTime << endl;
  }
  MPI_Finalize();
}