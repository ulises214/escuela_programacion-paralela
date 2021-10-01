export const getExecuteTime = (fn: () => void): number => {
  const t0 = performance.now();
  fn();
  const t1 = performance.now();
  return t1 - t0;
};
