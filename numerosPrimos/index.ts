/**
 * Ulises Rafael Ramírez Martínez
 * Facultad de Telemática: Ingeniería en Software
 */
import { getExecuteTime } from '../utils/getExecTime.ts';
import { writeInFile } from '../utils/writeInFile.ts';

const isPrime = (n: number): boolean => {
  let dividerCount = 0;
  for (let i = 1; i <= n; i++) if (n % i == 0) dividerCount++;
  return dividerCount == 2;
};
const getPrimesLessThanN = (n: number): readonly number[] => {
  const primes: number[] = [];
  for (let i = 1; i < n; i++) if (isPrime(i)) primes.push(i);
  return primes;
};

const main = () => {
  const testN: ReadonlyArray<number> = Array(10)
    .fill(1)
    .map((_, i) => (i + 1) * 1000);
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
  exec('primesLessN', getPrimesLessThanN);
};
main();
