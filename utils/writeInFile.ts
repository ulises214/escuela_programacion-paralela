// ? Se usa para guardar el resultado obtenido en archivos
// ? independientes dependiendo del metodo usado
export const writeInFile = (
  methodName: string,
  numberCount: number,
  timeSpent: number
): void => {
  Deno.writeTextFileSync(
    `${methodName}Result.csv`,
    // ? Se reemplaza los puntos con comas en los decimales
    // ? por compatibilidad con google docs
    // ? Por el mismo motivo se usa $ en lugar de , para la separación
    `\n${numberCount}$${timeSpent.toFixed(4).replaceAll('.', ',')}`,
    { append: true }
  );
};
