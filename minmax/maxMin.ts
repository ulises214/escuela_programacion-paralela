/**
 * Ulises Rafael Ramírez Martínez
 * Facultad de Telematica: Ingeniería en Software
 */

import { getExecuteTime } from '../utils/getExecTime.ts';
import { writeInFile } from '../utils/writeInFile.ts';

// ? Usamos esta función para saber el tiempo que pasa al ejecutar una función
type MethodFunction = (numbers: ReadonlyArray<number>) => {
  min: number;
  max: number;
};
type SortFunction = (
  numbers: ReadonlyArray<number>
) => ReadonlyArray<number>;

// ? Usa el metodo de iterar el array y comprobar el elemento con variables de control
const getMinMaxByIterations: MethodFunction = (numbers) => {
  let min = numbers[0];
  let max = numbers[0];
  for (const actual of numbers) {
    if (min > actual) min = actual;
    if (max < actual) max = actual;
  }
  return { min, max };
};

/// Usa el metodo de ordenamiento burble sort
const getMinMaxByBurbleSort: MethodFunction = (numbers) => {
  const sortedNumbers = burbleSort(numbers);
  const min = sortedNumbers[0];
  const max = sortedNumbers[sortedNumbers.length - 1];
  return { min, max };
};
/// Usa el metodo de ordenamiento quicksort
const getMinMaxByQuickSort: MethodFunction = (numbers) => {
  const sortedNumbers = quickSort(numbers);
  const min = sortedNumbers[0];
  const max = sortedNumbers[sortedNumbers.length - 1];
  return { min, max };
};
/// Ordena un array usando el metodo sort pro defecto
const quickSort: SortFunction = (numbers) => {
  return [...numbers].sort();
};
/// Ordena un array usando el metodo burbuja
const burbleSort: SortFunction = (numbers) => {
  const copyNumbers = [...numbers];
  let aux: number;
  for (let i = 0; i < copyNumbers.length; i++) {
    for (let j = 0; j < copyNumbers.length - 1; j++) {
      if (copyNumbers[j] > copyNumbers[j + 1]) {
        aux = copyNumbers[j];
        copyNumbers[j] = copyNumbers[j + 1];
        copyNumbers[j + 1] = aux;
      }
    }
  }
  return copyNumbers;
};
/// Genera un numero random a partir de un minimo y un maximo
const getRandomNumber = (min: number, max: number): number => {
  return Math.floor(Math.random() * (max - min) + min);
};

/// Genera los numeros aleatorios y genera los resultados
const main = (numberCount: number): void => {
  const randomNumbers: ReadonlyArray<number> = Array.from(
    { length: numberCount },
    () => getRandomNumber(1, 1000)
  );
  writeInFile(
    'iterations',
    numberCount,
    getExecuteTime(() => getMinMaxByIterations(randomNumbers))
  );
  writeInFile(
    'burble',
    numberCount,
    getExecuteTime(() => getMinMaxByBurbleSort(randomNumbers))
  );
  writeInFile(
    'quickSort',
    numberCount,
    getExecuteTime(() => getMinMaxByQuickSort(randomNumbers))
  );
};
/// Inicia todo el programa usando los valores 10000,20000,....,100000
const numberCountList = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10];
numberCountList.forEach((x) => main(x * 10000));
