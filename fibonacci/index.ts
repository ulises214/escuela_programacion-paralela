/**
 * Ulises Rafael Ramírez Martínez
 * Facultad de Telemática: Ingeniería en Software
 */
import { getExecuteTime } from '../utils/getExecTime.ts';
import { writeInFile } from '../utils/writeInFile.ts';

const getFibonacciSequential = (n: number): readonly number[] => {
  // ? Los primeros 2 valores de la serie de fibonacci es 1
  const fibonacci: number[] = [1, 1];
  if (n == 1) return [1];
  if (n == 2) return [1, 1];
  for (let i = 2; i < n; i++) {
    fibonacci[i] = fibonacci[i - 1] + fibonacci[i - 2];
  }
  return fibonacci;
};
const getFibonacciRecursive = (n: number): readonly number[] => {
  const getFibonacciNumber = (n: number): number => {
    if (n < 2) return 1;
    return getFibonacciNumber(n - 1) + getFibonacciNumber(n - 2);
  };
  return Array(n)
    .fill(1)
    .map((_, i) => getFibonacciNumber(i));
};
const main = () => {
  const testN: ReadonlyArray<number> = Array(10)
    .fill(1)
    .map((_, i) => (i + 1) * 4);
  const exec = (
    methodName: string,
    method: (n: number) => readonly number[]
  ) => {
    testN.forEach((i) => {
      writeInFile(
        methodName,
        i,
        getExecuteTime(() => method(i))
      );
    });
  };
  exec('sequential', getFibonacciSequential);
  exec('recursive', getFibonacciRecursive);
};
main();
