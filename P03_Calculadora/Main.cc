// Cambiar numeradores a BigInteger pq no pilla el - HECHO
// Optimizar la escritura en ficheros - HECHO

#include "Funciones.h"

int main() {
  // Crear dos números grandes en base 10
  BigUnsigned<10> num1("100");
  BigUnsigned<10> num2("25");
  std::cout << num1 + num2 << std::endl;
  std::cout << num1 - num2 << std::endl;
  std::cout << num1 * num2 << std::endl;
  std::cout << num1 / num2 << std::endl;

  // Realizar la suma utilizando `add`
  BigNumber<10>* resultado = num1.add(num2);
  BigNumber<10>* resultado2 = num1.subtract(num2);
  BigNumber<10>* resultado3 = num1.multiply(num2);
  BigNumber<10>* resultado4 = num1.divide(num2);

  // Mostrar el resultado en pantalla
  std::cout << "Resultado de la suma: " << *resultado << std::endl;
  std::cout << "Resultado de la resta: " << *resultado2 << std::endl;
  std::cout << "Resultado de la multiplicación: " << *resultado3 << std::endl;
  std::cout << "Resultado de la división: " << *resultado4 << std::endl;

  // Liberar memoria (si `add` devuelve un puntero dinámico)
  delete resultado;
  delete resultado2;
  delete resultado3;
  delete resultado4;

  return 0;
}






  