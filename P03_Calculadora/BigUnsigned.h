#ifndef BIGUNSIGNED_H
#define BIGUNSIGNED_H

#include "BigNumber.h"
#include <iostream>
#include <vector>

// Forward Declarations de BigInteger y BigRational (NO `#include` aquí)
template <unsigned char Base> class BigInteger;
template <unsigned char Base> class BigRational;

template <unsigned char Base>
class BigUnsigned : public BigNumber<Base> {
  public:
    // Constructores
    BigUnsigned(unsigned n = 0);
    BigUnsigned(const unsigned char*);
    BigUnsigned(std::string str);
    BigUnsigned(const BigUnsigned&); // Constructor de copia

    // Sobrecarga de operadores
    BigUnsigned<Base>& operator=(const BigUnsigned<Base>& number_param);

    // Inserción/Extracción
    template <unsigned char B>
    friend std::ostream& operator<<(std::ostream& os, const BigUnsigned<B>& number_param);
    template <unsigned char B>
    friend std::istream& operator>>(std::istream& is, BigUnsigned<B>& number_param);

    // Comparación
    bool operator==(const BigUnsigned<Base>& number_param) const;
    template <unsigned char B>
    friend bool operator<(const BigUnsigned<B>& number_param1, const BigUnsigned<B>& number_param2);
    bool operator>=(const BigUnsigned<Base>& number_param) { return *this < number_param || *this == number_param; }
    bool operator<=(const BigUnsigned<Base>& number_param) const { return !(*this > number_param); }
    bool operator>(const BigUnsigned<Base>& number_param) const { return !(*this <= number_param) && !(*this == number_param); }

    // Incremento/Decremento
    BigUnsigned& operator++(); // Pre-incremento
    BigUnsigned operator++(int); // Post-incremento
    BigUnsigned& operator--(); // Pre-decremento
    BigUnsigned operator--(int); // Post-decremento

    // Operadores aritméticos
    template <unsigned char B>
    friend BigUnsigned<B> operator+(const BigUnsigned<B>&, const BigUnsigned<B>&);
    BigUnsigned operator-(const BigUnsigned<Base>&) const;
    BigUnsigned operator*(const BigUnsigned<Base>&) const;
    template <unsigned char B>
    friend BigUnsigned<B> operator/(const BigUnsigned<B>&, const BigUnsigned<B>&);
    BigUnsigned operator%(const BigUnsigned<Base>&) const;

    // Getter
    std::vector<unsigned char> getDigitsVec() const { return digits_vec_; }
    BigUnsigned GetZero() const { return BigUnsigned((const unsigned char*)"0"); }
    std::string toString() const;

    // Setter
    void SetInmediato(int n) { digits_vec_ = BigUnsigned(n).digits_vec_; }

    // Implementación de métodos virtuales de BigNumber<Base>
    BigNumber<Base>* add(const BigNumber<Base>&) const override;
    BigNumber<Base>* subtract(const BigNumber<Base>&) const override;
    BigNumber<Base>* multiply(const BigNumber<Base>&) const override;
    BigNumber<Base>* divide(const BigNumber<Base>&) const override;

    // Conversión a otros tipos
    operator BigInteger<Base>() const override;
    operator BigRational<Base>() const override;

    // Métodos de entrada/salida
    std::ostream& write(std::ostream&) const override;
    std::istream& read(std::istream&) override;
  private:
    std::vector<unsigned char> digits_vec_;
};

// Especialización para base 2
template <>
class BigUnsigned<2> {
  public:
    // Constructores
    BigUnsigned(unsigned n = 0);
    BigUnsigned(const unsigned char*);
    BigUnsigned(std::string str);
    BigUnsigned(const BigUnsigned<2>&); // Constructor de copia

    // Sobrecarga de operadores
    BigUnsigned<2>& operator=(const BigUnsigned<2>& number_param);

    // Inserción/Extracción
    friend std::ostream& operator<<(std::ostream& os, const BigUnsigned<2>& number_param);
    friend std::istream& operator>>(std::istream& is, BigUnsigned<2>& number_param);

    // Comparación
    bool operator==(const BigUnsigned<2>& number_param) const;
    friend bool operator<(const BigUnsigned<2>& number_param1, const BigUnsigned<2>& number_param2);
    bool operator>=(const BigUnsigned<2>& number_param) { return *this < number_param || *this == number_param; }
    bool operator<=(const BigUnsigned<2>& number_param) const { return !(*this > number_param); }
    bool operator>(const BigUnsigned<2>& number_param) const { return !(*this <= number_param) && !(*this == number_param); }

    // Incremento/Decremento
    BigUnsigned& operator++(); // Pre-incremento
    BigUnsigned operator++(int); // Post-incremento
    BigUnsigned& operator--(); // Pre-decremento
    BigUnsigned operator--(int); // Post-decremento

    // Operadores aritméticos
    friend BigUnsigned<2> operator+(const BigUnsigned<2>&, const BigUnsigned<2>&);
    BigUnsigned operator-(const BigUnsigned<2>&) const;
    BigUnsigned operator*(const BigUnsigned<2>&) const;
    friend BigUnsigned<2> operator/(const BigUnsigned<2>&, const BigUnsigned<2>&);
    BigUnsigned operator%(const BigUnsigned<2>&) const;
    BigUnsigned<2> complemento_dos() const;

    // Getter
    std::vector<unsigned char> getDigitsVec() const { return digits_vec_; }
    bool isZero() const { return digits_vec_.size() == 1 && digits_vec_[0] == 0; }
    BigUnsigned GetZero() const { return BigUnsigned((const unsigned char*)"0"); }
    std::string toString() const;

    // Setter
    void SetInmediato(int n) { digits_vec_ = BigUnsigned(n).digits_vec_; }

    // // Implementación de métodos virtuales de BigNumber<2>
    // BigNumber<2>* add(const BigNumber<2>&) const;
    // BigNumber<2>* subtract(const BigNumber<2>&) const;
    // BigNumber<2>* multiply(const BigNumber<2>&) const;
    // BigNumber<2>* divide(const BigNumber<2>&) const;
// 
    // // Conversión a otros tipos
    // operator BigInteger<2>() const;
    // operator BigRational<2>() const;
// 
    // // Métodos de entrada/salida
    // std::ostream& write(std::ostream&) const;
    // std::istream& read(std::istream&);
  private:
    std::vector<unsigned char> digits_vec_;
};

// Incluir aquí después de definir la clase (para evitar dependencias circulares)
#include "BigInteger.h"
#include "BigRational.h"

/// @brief Constructor a partir de un número natural
/// @param n
template <unsigned char Base> 
BigUnsigned<Base>::BigUnsigned(unsigned n) {
  if (n == 0) {
    digits_vec_.push_back(0);
    digits_vec_.pop_back();
  }
  else {
    while (n != 0) {
      digits_vec_.push_back(n % 10);
      n /= 10;
    }
  }
}


/// @brief Constructor a partir de una cadena
/// @param numero
template <unsigned char Base>
BigUnsigned<Base>::BigUnsigned(const unsigned char* unprocessed_digits) {
  std::string new_digits = std::string(reinterpret_cast<const char*>(unprocessed_digits));
  if (!new_digits.empty()) {
    for (int i = new_digits.size() - 1; i >= 0; i--) {
      unsigned char digit;
      if (new_digits[i] >= '0' && new_digits[i] <= '9') {
        digit = new_digits[i] - '0';
      } else if (Base > 10 && new_digits[i] >= 'A' && new_digits[i] <= 'F') {
        digit = new_digits[i] - 'A' + 10;
      } else {
        std::cout << new_digits[i] << std::endl;
        throw std::invalid_argument("Dígito inválido para la base dada");
      }
      
      if (digit >= Base) {
        throw std::invalid_argument("Dígito inválido para la base dada");
      }

      digits_vec_.push_back(digit);
    }
  } else {
    digits_vec_.push_back(0); // Si la cadena está vacía, inicializar con 0
  }
}

template <unsigned char Base>
BigUnsigned<Base>::BigUnsigned(std::string str) {
  if (!str.empty()) {
    for (int i = str.size() - 1; i >= 0; i--) {
      unsigned char digit;
      if (str[i] >= '0' && str[i] <= '9') {
        digit = str[i] - '0';
      } else if (Base > 10 && str[i] >= 'A' && str[i] <= 'F') {
        digit = str[i] - 'A' + 10;
      } else {
        std::cout << str[i] << std::endl;
        throw std::invalid_argument("Dígito inválido para la base dada");
      }
      
      if (digit >= Base) {
        throw std::invalid_argument("Dígito inválido para la base dada");
      }

      digits_vec_.push_back(digit);
    }
  } else {
    digits_vec_.push_back(0); // Si la cadena está vacía, inicializar con 0
  }
}



/// @brief Constructor de copia
/// @param BigUnsigned& copy
template <unsigned char Base> 
BigUnsigned<Base>::BigUnsigned(const BigUnsigned<Base>& copy) : digits_vec_(copy.digits_vec_) {} 



/// @brief Sobrecarga de operador de copia
/// @param  number_param
/// @return number_result
template <unsigned char Base> 
BigUnsigned<Base>& BigUnsigned<Base>::operator=(const BigUnsigned<Base>& number_param) {
  if (this != &number_param) {
    digits_vec_ = number_param.digits_vec_;
  }
  return *this;
}



/// @brief Sobrecarga de operador de inserción
/// @param os 
/// @param number_param 
/// @return os
template <unsigned char B> 
std::ostream& operator<<(std::ostream& os, const BigUnsigned<B>& number_param) {
  for (int i = number_param.digits_vec_.size() - 1; i >= 0; i--) {
    unsigned char digit = number_param.digits_vec_[i];
    if (digit < 10) {
      os << static_cast<char>(digit + '0');
    } else if (digit < B) {
      os << static_cast<char>(digit - 10 + 'A');
    } else {
      std::cerr << "Dígito inválido para la base dada." << std::endl;
      exit(EXIT_FAILURE);
    }
  }
  return os;
}



/// @brief Sobrecarga de operador de extracción
/// @param is 
/// @param number_param 
/// @return is
template <unsigned char B> 
std::istream& operator>>(std::istream& is, BigUnsigned<B>& number_param) {
  std::string input;
  is >> input;
  number_param.digits_vec_.clear();
  for (int i = input.size() - 1; i >= 0; i--) {
    if (input[i] >= '0' && input[i] <= '9') {
      number_param.digits_vec_.push_back(input[i] - '0');
    } else {
      std::cerr << "La cadena no es numérica." << std::endl;
      exit(EXIT_FAILURE);
    }
  }
  return is;
}



/// @brief Sobrecarga de operador de igualdad 
/// @param number_param 
/// @return true si son iguales, false si no lo son 
template <unsigned char Base> 
bool BigUnsigned<Base>::operator==(const BigUnsigned<Base>& number_param) const {
  if (digits_vec_.size() != number_param.digits_vec_.size()) {
    return false;
  }
  for (int i = 0; i < digits_vec_.size(); i++) {
    if (digits_vec_[i] != number_param.digits_vec_[i]) {
      return false;
    }
  }
  return true;
}



/// @brief Sobrecarga de operador de menor que 
/// @param number_param1 
/// @param number_param2 
/// @return true si es menor, false si no lo es 
template <unsigned char B> 
bool operator<(const BigUnsigned<B>& number_param1, const BigUnsigned<B>& number_param2) {
  if (number_param1.digits_vec_.size() < number_param2.digits_vec_.size()) {
    return true;
  }
  else if (number_param1.digits_vec_.size() > number_param2.digits_vec_.size()) {
    return false;
  }
  else {
    for (int i = number_param1.digits_vec_.size() - 1; i >= 0; i--) {
      if (number_param1.digits_vec_[i] < number_param2.digits_vec_[i]) {
        return true;
      }
      else if (number_param1.digits_vec_[i] > number_param2.digits_vec_[i]) {
        return false;
      }
    }
  }
  return false;
}


/// @brief Sobrecarga de operador de menor o igual 
/// @param number_param1 
/// @param number_param2 
/// @return true si es menor o igual, false si no lo es
template <unsigned char Base>  
bool operator>=(const BigUnsigned<Base>& number_param1, const BigUnsigned<Base>& number_param2) {
  if (number_param1.getDigitsVec().size() > number_param2.getDigitsVec().size()) {
    return true;
  } 
  else if (number_param1.getDigitsVec().size() < number_param2.getDigitsVec().size()) {
    return false;
  } 
  else {
    for (int i = number_param1.getDigitsVec().size() - 1; i >= 0; i--) {
      if (number_param1.getDigitsVec()[i] > number_param2.getDigitsVec()[i]) {
        return true;
      } 
      else if (number_param1.getDigitsVec()[i] < number_param2.getDigitsVec()[i]) {
        return false;
      }
    }
  }
  return true;  // Si son iguales, retorna true
}



/// @brief Sobrecarga de operador de suma
/// @param number_param1 
/// @param number_param2 
/// @return number_result
template <unsigned char B> 
BigUnsigned<B> operator+(const BigUnsigned<B>& number_param1, const BigUnsigned<B>& number_param2) {
  BigUnsigned<B> resultado;
  unsigned char carry = 0;
  int longer = 0;
  //Obtenemos la longitud del numero mas largo para iterar 
  if (number_param1.digits_vec_.size() >= number_param2.digits_vec_.size()){
    longer = number_param1.digits_vec_.size();
  } else {
    longer = number_param2.digits_vec_.size();
  }
  for (int i = 0; i < longer; i++) {
    //Si alguno de los numeros es mas pequeño que el indice i, su valor es 0
    unsigned char digit1 = (i < number_param1.digits_vec_.size()) ? number_param1.digits_vec_[i] : 0;
    unsigned char digit2 = (i < number_param2.digits_vec_.size()) ? number_param2.digits_vec_[i] : 0;
    //La suma es = a el numero 1 + el numero 2 + el acarreo de la suma anterior
    unsigned char digit_sum = digit1 + digit2 + carry;
    //Se añade al resultado de la suma solo el numero menos significativo
    resultado.digits_vec_.push_back(digit_sum % B );
    //El carry se actualiza siendo el numero mas significativo de la suma
    carry = (digit_sum) / B;
  }
  //Si despues de iterar sobre el numero mas largo sigue habiendo acarreo, se añade el acarreo al resultado
  if (carry != 0) {
    resultado.digits_vec_.push_back(carry);
  }
  //Se actualiza la longitud del resultado
  // resultado.length_ = resultado.digits_vec_.size();
  return resultado;
}



/// @brief Sobrecarga de operador de resta
/// @param number_param 
/// @return number_result
template <unsigned char Base> 
BigUnsigned<Base> BigUnsigned<Base>::operator-(const BigUnsigned<Base>& number_param) const {
  BigUnsigned number_result;
  unsigned borrow = 0;
  unsigned difference = 0;
  // Si A < B, retornar 0 ya que BigUnsigned no admite negativos
  if (*this < number_param) {
    return BigUnsigned((const unsigned char*)"0");
  }
  // Resta de los números
  for (size_t i = 0; i < digits_vec_.size(); i++) { // Recorrer los dígitos de A
    unsigned digitA = digits_vec_[i];  // Dígito actual de A
    unsigned digitB = (i < number_param.digits_vec_.size()) ? number_param.digits_vec_[i] : 0; // Si B es más corto que A
    if (digitA < digitB + borrow) {  // Si necesitamos pedir prestado
      digitA += Base; // Sumamos 10 al dígito actual
      difference = digitA - (digitB + borrow); // Restamos B y el préstamo
      borrow = 1;  // Marcamos que hay préstamo para la siguiente iteración
    } else { // Si no necesitamos pedir prestado
      difference = digitA - (digitB + borrow); // Restamos B y el préstamo
      borrow = 0; // No hay préstamo
    }
    number_result.digits_vec_.push_back(difference);
  }
  // Eliminar ceros a la izquierda correctamente
  while (number_result.digits_vec_.size() > 1 && number_result.digits_vec_.back() == 0) {
    number_result.digits_vec_.pop_back();
  }
  return number_result;
}




/// @brief Sobrecarga de operador de multiplicación 
/// @param number_param 
/// @return number_result 
template <unsigned char Base>
BigUnsigned<Base> BigUnsigned<Base>::operator*(const BigUnsigned<Base>& multiplicador) const {
    BigUnsigned<Base> resultado((const unsigned char*)"0");  // Inicializamos el resultado en 0
    BigUnsigned<Base> primero = *this;
    if (multiplicador == resultado) {  // Si el multiplicador es 0, el resultado también lo será
        return BigUnsigned<Base>((const unsigned char*)"0");
    }
    for (BigUnsigned<Base> i((const unsigned char*)"0"); i < multiplicador; ++i) {
        resultado = resultado + primero;  // Suma iterativa
    }
    return resultado;
}




/// @brief Sobrecarga de operador de división
/// @param number_param1 
/// @param number_param2  
/// @return number_result 
template <unsigned char B> 
BigUnsigned<B> operator/(const BigUnsigned<B>& number_param1, const BigUnsigned<B>& number_param2) {
  BigUnsigned<B> number_result((const unsigned char*)"0");
  BigUnsigned<B> temp = number_param1;
  while (number_param2 < temp ) { // Mientras B sea menor que A
    temp = temp - number_param2; // Restar B a A
    ++number_result; // Incrementar el resultado (cociente)
  }
  if (temp == number_param2) { // Si A es igual a B
    ++number_result; // Incrementar el resultado (cociente)
    temp = temp - number_param2; // Restar B a A
  }
  return number_result;
}



/// @brief 
/// @param number_param 
/// @return 
template <unsigned char Base> 
BigUnsigned<Base> BigUnsigned<Base>::operator%(const BigUnsigned<Base>& number_param) const {
  BigUnsigned c; // Cociente
  c = *this / number_param; // Calcular el cociente
  BigUnsigned r = *this - (c * number_param);  // Calcular el resto
  return r;
}



/// @brief Pre-incremento
/// @return Referencia al objeto incrementado
template <unsigned char Base> 
BigUnsigned<Base>& BigUnsigned<Base>::operator++() {
  *this = *this + BigUnsigned<Base>(1); // Convertimos 1 a BigUnsigned<Base>
  return *this;
}



/// @brief Post-incremento
/// @return Valor antes del incremento
template <unsigned char Base> 
BigUnsigned<Base> BigUnsigned<Base>::operator++(int) {
  BigUnsigned temp = *this;
  *this = *this + BigUnsigned<Base>(1); // Convertimos 1 a BigUnsigned<Base>
  return temp;
}



/// @brief
/// @return
template <unsigned char Base> 
BigUnsigned<Base>& BigUnsigned<Base>::operator--() {
  *this = *this - 1;
  return *this;
}



/// @brief
/// @return
template <unsigned char Base> 
BigUnsigned<Base> BigUnsigned<Base>::operator--(int) {
  BigUnsigned temp = *this;
  *this = *this - 1;
  return temp;
}

template <unsigned char Base>
std::string BigUnsigned<Base>::toString() const {
  std::string str;
  for (int i = digits_vec_.size() - 1; i >= 0; i--) {
    if (digits_vec_[i] < 10) {
      str += static_cast<char>(digits_vec_[i] + '0');
    } else if (digits_vec_[i] < Base) {
      str += static_cast<char>(digits_vec_[i] - 10 + 'A');
    } else {
      std::cerr << "Dígito inválido para la base dada." << std::endl;
      exit(EXIT_FAILURE);
    }
  }
  return str;
}




// ----------------------------------------PRACTICA 3----------------------------------------



// Implementación de add
template <unsigned char Base>
BigNumber<Base>* BigUnsigned<Base>::add(const BigNumber<Base>& other) const {
    // Convertimos `other` a `BigUnsigned<Base>`
    const BigUnsigned<Base>& num = dynamic_cast<const BigUnsigned<Base>&>(other);

    // Usamos el operador sobrecargado `+` para la suma
    BigUnsigned<Base> resultado = (*this) + num;

    // Devolvemos un puntero a un nuevo objeto `BigUnsigned<Base>`
    return new BigUnsigned<Base>(resultado);
}

// Implementación de subtract
template <unsigned char Base>
BigNumber<Base>* BigUnsigned<Base>::subtract(const BigNumber<Base>& other) const {
    const BigUnsigned<Base>& num = dynamic_cast<const BigUnsigned<Base>&>(other);
    if (*this < num) throw std::invalid_argument("Resultado negativo en BigUnsigned");
    return new BigUnsigned<Base>((*this) - num);
}

// Implementación de multiply
template <unsigned char Base>
BigNumber<Base>* BigUnsigned<Base>::multiply(const BigNumber<Base>& other) const {
    const BigUnsigned<Base>& num = dynamic_cast<const BigUnsigned<Base>&>(other);
    return new BigUnsigned<Base>((*this) * num);
}

// Implementación de divide
template <unsigned char Base>
BigNumber<Base>* BigUnsigned<Base>::divide(const BigNumber<Base>& other) const {
    const BigUnsigned<Base>& num = dynamic_cast<const BigUnsigned<Base>&>(other);
    if (num == BigUnsigned<Base>("0")) throw std::invalid_argument("División por cero");
    return new BigUnsigned<Base>((*this) / num);
}

// Implementación de conversión a BigInteger
template <unsigned char Base>
BigUnsigned<Base>::operator BigInteger<Base>() const {
    return BigInteger<Base>(this->toString());
}

// Implementación de conversión a BigRational
template <unsigned char Base>
BigUnsigned<Base>::operator BigRational<Base>() const {
  return BigRational<Base>(BigInteger<Base>(*this), BigUnsigned<Base>(1));
}

// Implementación de write
template <unsigned char Base>
std::ostream& BigUnsigned<Base>::write(std::ostream& os) const {
    for (int i = digits_vec_.size() - 1; i >= 0; i--) {
        unsigned char digit = digits_vec_[i];
        if (digit < 10) {
            os << static_cast<char>(digit + '0');
        } else if (digit < Base) {
            os << static_cast<char>(digit - 10 + 'A');
        } else {
            std::cerr << "Dígito inválido para la base dada." << std::endl;
            exit(EXIT_FAILURE);
        }
    }
    return os;
}

// Implementación de read
template <unsigned char Base>
std::istream& BigUnsigned<Base>::read(std::istream& is) {
    std::string input;
    is >> input;
    *this = BigUnsigned<Base>(input);
    return is;
}

// -------------------ESPECIALIZACIÓN PARA BASE 2-------------------

// Constructor para números enteros
BigUnsigned<2>::BigUnsigned(unsigned num) {
  std::string numero = std::to_string(num);
  for (int i = numero.length() - 1; i >= 0; i--) {
    if (numero[i] < '0' || numero[i] > '1') {
      std::cerr << "Error, el número " << numero[i] << " debe ser 0 o 1" << std::endl;
      std::exit(EXIT_FAILURE);
    }
    digits_vec_.push_back(numero[i] - '0');
  }
}

// Constructor a partir de un string de caracteres
BigUnsigned<2>::BigUnsigned(const unsigned char* unprocessed_digits) {
  std::string new_digits = std::string(reinterpret_cast<const char*>(unprocessed_digits));
  for (int i = new_digits.length() - 1; i >= 0; i--) {
    if (new_digits[i] < '0' || new_digits[i] > '1') {
      std::cerr << "Error, el número " << new_digits[i] << " debe ser 0 o 1" << std::endl;
      std::exit(EXIT_FAILURE);
    }
    digits_vec_.push_back(new_digits[i] - '0');
  }
}

// Constructor de copia
BigUnsigned<2>::BigUnsigned(const BigUnsigned<2>& other) {
  digits_vec_ = other.digits_vec_;  // Copiamos los dígitos
}

// Sobrecarga del operador de asignación
BigUnsigned<2>& BigUnsigned<2>::operator=(const BigUnsigned<2>& other) {
  if (this != &other) {
    digits_vec_ = other.digits_vec_;
  }
  return *this;
}

// Sobrecarga de igualdad
bool BigUnsigned<2>::operator==(const BigUnsigned<2>& other) const {
  if (digits_vec_.size() != other.digits_vec_.size()) {
    return false;
  }
  for (size_t i = 0; i < digits_vec_.size(); i++) {
    if (digits_vec_[i] != other.digits_vec_[i]) {
      return false;
    }
  }
  return true;
}

// Sobrecarga del operador menor que
bool operator<(const BigUnsigned<2>& number1, const BigUnsigned<2>& number2) {
  if (number1.digits_vec_.size() < number2.digits_vec_.size()) {
    return true;
  }
  if (number1.digits_vec_.size() > number2.digits_vec_.size()) {
    return false;
  }
  for (int i = number1.digits_vec_.size() - 1; i >= 0; i--) {
    if (number1.digits_vec_[i] < number2.digits_vec_[i]) {
      return true;
    }
    if (number1.digits_vec_[i] > number2.digits_vec_[i]) {
      return false;
    }
  }
  return false;
}

// Incremento pre-fijo
BigUnsigned<2>& BigUnsigned<2>::operator++() {
  BigUnsigned<2> uno((const unsigned char *)"1");
  *this = *this + uno;
  return *this;
}

// Incremento post-fijo
BigUnsigned<2> BigUnsigned<2>::operator++(int) {
  BigUnsigned<2> temp = *this;
  BigUnsigned<2> uno((const unsigned char *)"1");
  *this = *this + uno;
  return temp;
}

// Decremento pre-fijo
BigUnsigned<2>& BigUnsigned<2>::operator--() {
  BigUnsigned<2> uno((const unsigned char *)"1");
  *this = *this - uno;
  return *this;
}

// Decremento post-fijo
BigUnsigned<2> BigUnsigned<2>::operator--(int) {
  BigUnsigned<2> temp = *this;
  BigUnsigned<2> uno((const unsigned char *)"1");
  *this = *this - uno;
  return temp;
}

// Operador de suma
BigUnsigned<2> operator+(const BigUnsigned<2>& number_one, const BigUnsigned<2>& number_two) {
  BigUnsigned<2> suma ((const unsigned char *)"");
  unsigned char carry = 0;
  unsigned char uno = 1;
  unsigned char cero = 0;

  int longer = 0;
  if (number_one.digits_vec_.size() >= number_two.digits_vec_.size()){
    longer = number_one.digits_vec_.size();
  } else {
    longer = number_two.digits_vec_.size();
  }
  for (int i = 0; i < longer; i++) {
    unsigned char digit_sum = 0;
    unsigned char digit1 = (i < number_one.digits_vec_.size()) ? number_one.digits_vec_[i] : 0;
    unsigned char digit2 = (i < number_two.digits_vec_.size()) ? number_two.digits_vec_[i] : 0;
    //La suma es = a el numero 1 + el numero 2 + el acarreo de la suma anterior
  
    if (digit1 == 1 && digit2 == 1 && carry == 1) {
      digit_sum = digit1; // si 1 + 1 + 1, result = 1 y carry = 1
      carry = 1;
    } else if ((digit1 == 1 && digit2 == 1 && carry == 0) || (digit1 == 1 && digit2 == 0 && carry == 1) || (digit1 == 0 && digit2 == 1 && carry == 1)){
      digit_sum = cero; // si 1 + 1 + 0, result = 0 y carry = 1
      carry = 1;
    } else if (digit1 == 0 && digit2 == 0 && carry == 0){
      digit_sum = cero; //si 0 + 0 + 0, result = 0 y carry = 0
      carry = 0;
    } else {
      digit_sum = uno; // en cualquier otro caso, result = 1, carry = 0
      carry = 0;
    }
    suma.digits_vec_.push_back(digit_sum);
  }
  //Si aun queda carry, se añade 
  if (carry != 0) {
    suma.digits_vec_.push_back(uno);
  }
  return suma;
}

// Operador de resta
BigUnsigned<2> BigUnsigned<2>::operator-(const BigUnsigned<2>& number) const {
  BigUnsigned<2> complemento((unsigned char *)"");  // El complemento a dos del número que estamos restando
  BigUnsigned<2> resta((unsigned char *)"");        // El resultado de la resta
  unsigned char cero = 0;
  unsigned char uno = 1;
  // Si el número que estamos restando es mayor que el actual, el resultado es 0
  if (*this < number) {
    resta.digits_vec_.push_back(cero);  // Guardamos 0 como resultado
    return resta;
  }
  // Obtenemos el complemento a dos del número que estamos restando
  complemento = number.complemento_dos();
  // Hacemos que el complemento a dos tenga la misma longitud que el número original
  while (this->digits_vec_.size() != complemento.digits_vec_.size()) {
    complemento.digits_vec_.push_back(uno);  // Rellenamos con 1
  }
  // Sumamos el complemento a dos al número original
  resta = *this + complemento;
  // Eliminamos el acarreo final si existe
  if (resta.digits_vec_.back() == 1) {
    resta.digits_vec_.pop_back();
  }
  // Eliminamos los ceros a la izquierda
  while (resta.digits_vec_.size() > 1 && resta.digits_vec_.back() == 0) {
    resta.digits_vec_.pop_back();
  }
  return resta;
}

// Método para obtener el complemento a dos de un número binario
BigUnsigned<2> BigUnsigned<2>::complemento_dos() const {
  BigUnsigned<2> complemento((unsigned char *)"");
  unsigned char uno = 1;
  
  // Primero, obtenemos el complemento a uno (invertimos todos los dígitos)
  for (size_t i = 0; i < digits_vec_.size(); i++) {
    complemento.digits_vec_.push_back(digits_vec_[i] == 0 ? 1 : 0);  // Complemento a uno
  }

  // Sumamos 1 al complemento a uno para obtener el complemento a dos
  BigUnsigned<2> uno_obj((unsigned char *)"1");
  complemento = complemento + uno_obj;

  return complemento;
}

// Operador de multiplicación (sumas sucesivas)
BigUnsigned<2> BigUnsigned<2>::operator*(const BigUnsigned<2>& number) const {
  BigUnsigned<2> multiplicacion((unsigned char *)"0");
  BigUnsigned<2> uno = BigUnsigned<2>((unsigned char *)"1");
  BigUnsigned<2> cero = BigUnsigned<2>((unsigned char *)"0");
  BigUnsigned<2> multiplicando = number;
  while (!multiplicando.isZero()) {
    multiplicacion = multiplicacion + *this;
    multiplicando = multiplicando - uno;
  }
  return multiplicacion;
}

// Operador de división
BigUnsigned<2> operator/(const BigUnsigned<2>& dividend, const BigUnsigned<2>& divisor) {
  BigUnsigned<2> resto = dividend;
  BigUnsigned<2> cociente((unsigned char *)"0");
  BigUnsigned<2> uno((unsigned char *)"1");
  if (dividend < divisor) {
    return BigUnsigned<2>((unsigned char *)"0");
  }
  while (divisor < resto) {
    cociente = cociente + uno;
    resto = resto - divisor;
  }
  if (resto == divisor) {
    cociente = cociente + uno;
    resto = resto - divisor;
  }
  return cociente;
}

// Operador de módulo
BigUnsigned<2> BigUnsigned<2>::operator%(const BigUnsigned<2>& divisor) const {
  BigUnsigned<2> quotient = *this / divisor;
  BigUnsigned<2> remainder = *this - (quotient * divisor);
  return remainder;
}


// Sobrecarga del operador << para mostrar en flujo
std::ostream& operator<<(std::ostream& os, const BigUnsigned<2>& number) {
  for (int i = number.digits_vec_.size() - 1; i >= 0; i--) {
    os << static_cast<char>(number.digits_vec_[i] + '0');
  }
  return os;
}

// Sobrecarga del operador >> para leer de flujo
std::istream& operator>>(std::istream& is, BigUnsigned<2>& number) {
  std::string input;
  is >> input;
  number.digits_vec_.clear();
  for (int i = input.size() - 1; i >= 0; i--) {
    if (input[i] < '0' || input[i] > '1') {
      std::cerr << "Error, el número " << input[i] << " debe ser 0 o 1" << std::endl;
      std::exit(EXIT_FAILURE);
    }
    number.digits_vec_.push_back(input[i] - '0');
  }
  return is;
}

//--------------------------------------------------PRACTICA 3--------------------------------------------------

// // Implementación de add
// BigNumber<2>* BigUnsigned<2>::add(const BigNumber<2>& other) const {
//     const BigUnsigned<2>& num = dynamic_cast<const BigUnsigned<2>&>(other);
//     BigUnsigned<2> resultado = (*this) + num;
//     return new BigUnsigned<2>(resultado);
// }
// 
// // Implementación de subtract
// BigNumber<2>* BigUnsigned<2>::subtract(const BigNumber<2>& other) const {
//     const BigUnsigned<2>& num = dynamic_cast<const BigUnsigned<2>&>(other);
//     if (*this < num) throw std::invalid_argument("Resultado negativo en BigUnsigned<2>");
//     return new BigUnsigned<2>((*this) - num);
// }
// 
// // Implementación de multiply
// BigNumber<2>* BigUnsigned<2>::multiply(const BigNumber<2>& other) const {
//     const BigUnsigned<2>& num = dynamic_cast<const BigUnsigned<2>&>(other);
//     return new BigUnsigned<2>((*this) * num);
// }
// 
// // Implementación de divide
// BigNumber<2>* BigUnsigned<2>::divide(const BigNumber<2>& other) const {
//     const BigUnsigned<2>& num = dynamic_cast<const BigUnsigned<2>&>(other);
//     if (num == BigUnsigned<2>("0")) throw std::invalid_argument("División por cero");
//     return new BigUnsigned<2>((*this) / num);
// }
// 
// // Implementación de conversión a BigInteger<2>
// BigUnsigned<2>::operator BigInteger<2>() const {
//     return BigInteger<2>(this->toString());
// }
// 
// // Implementación de conversión a BigRational<2>
// BigUnsigned<2>::operator BigRational<2>() const {
//     return BigRational<2>(BigInteger<2>(*this), BigUnsigned<2>(1));
// }
// 
// // Implementación de write
// std::ostream& BigUnsigned<2>::write(std::ostream& os) const {
//     for (int i = digits_vec_.size() - 1; i >= 0; i--) {
//         os << static_cast<char>(digits_vec_[i] + '0');
//     }
//     return os;
// }
// 
// // Implementación de read
// std::istream& BigUnsigned<2>::read(std::istream& is) {
//     std::string input;
//     is >> input;
//     *this = BigUnsigned<2>(input);
//     return is;
// }
// 
#endif 