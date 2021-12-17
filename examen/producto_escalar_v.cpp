/**
 * @file producto_escalar_v.cpp
 * @author Ulises Rafael Ramírez Martínez 5G
 * @date 2021-12-17
 *
 */
#include "iostream"
#include "stdlib.h"
#include "time.h"
#include <cstdlib>
#include <mpi.h>
using namespace std;
int main(int argc, char **argv) {
  const int N = 100000;
  const int rootProc = 0;

  int procsCount, currProc;
  // Se definen la versión global y local de cada vector
  int globalData1[N], localData1[N], globalData2[N], localData2[N];

  int blockSize;

  int globalSum = 0, localSum = 0;

  double initialTime, finalTime, totalTime;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &currProc);
  MPI_Comm_size(MPI_COMM_WORLD, &procsCount);

  // Si el proceso que está corriendo es el root se inicializan los valores para
  // los array globales
  if (currProc == rootProc) {
    // Se inicializa una semilla para generar los números aleatorios
    srand(time(NULL));
    for (int i = 0; i < N; i++) {
      globalData1[i] = rand() % 50;
      globalData2[i] = rand() % 50;
    }
    initialTime = MPI_Wtime();
  }

  blockSize = N / procsCount;
  // Se dividen los 2 array entre cada uno de los procesos
  MPI_Scatter(globalData1, blockSize, MPI_INT, localData1, blockSize, MPI_INT,
              rootProc, MPI_COMM_WORLD);
  MPI_Scatter(globalData2, blockSize, MPI_INT, localData2, blockSize, MPI_INT,
              rootProc, MPI_COMM_WORLD);
  // Se realiza el producto escalar de cada uno de los vectores locales
  for (int i = 0; i < blockSize; i++) {
    localSum += localData1[i] * localData2[i];
  }
  cout << "Proceso " << currProc << " suma: " << localSum << endl;
  // Se suman los resultados de cada proceso, para obtener el resultado global
  MPI_Reduce(&localSum, &globalSum, 1, MPI_INT, MPI_SUM, rootProc,
             MPI_COMM_WORLD);
  // Se imprimen los timepos de ejecución
  if (currProc == rootProc) {
    finalTime = MPI_Wtime();
    totalTime = finalTime - initialTime;
    cout << "Tiempo total: " << totalTime << endl;
    cout << "Resultado: " << globalSum << endl;
  }
  MPI_Finalize();
}