#ifndef BIGINTEGER_H
#define BIGINTEGER_H

#include "BigNumber.h"
#include "BigUnsigned.h"  // Se necesita porque usa `BigUnsigned<Base>`

template <unsigned char Base>
class BigInteger { // : public BigNumber<Base> {
  public:
    // Constructores
    BigInteger(int n = 0);
    BigInteger(const BigUnsigned<Base>&);
    BigInteger(const BigInteger<Base>&); // Constructor de copia
    BigInteger(std::string str);
    // Sobrecarga de operadores
    BigInteger<Base>& operator=(const BigInteger<Base>& number_param);
    // Inserción/Extracción
    template <unsigned char B>
    friend std::ostream& operator<<(std::ostream& os, const BigInteger<B>& number_param);
    template <unsigned char B>
    friend std::istream& operator>>(std::istream& is, BigInteger<B>& number_param);
    // Comparación
    bool operator==(const BigInteger<Base>& number_param) const;
    template <unsigned char B>
    friend bool operator<(const BigInteger<B>& number_param1, const BigInteger<B>& number_param2);
    // Incremento/Decremento
    BigInteger<Base>& operator++(); // Pre-incremento
    BigInteger<Base> operator++(int); // Post-incremento
    BigInteger<Base>& operator--(); // Pre-decremento
    BigInteger<Base> operator--(int); // Post-decremento
    // Operadores aritméticos
    template <unsigned char B>
    friend BigInteger<B> operator+(const BigInteger<B>&, const BigInteger<B>&);
    BigInteger<Base> operator-(const BigInteger<Base>&) const;
    BigInteger<Base> operator*(const BigInteger<Base>&) const;
    template <unsigned char B>
    friend BigInteger<B> operator/(const BigInteger<B>&, const BigInteger<B>&);
    BigInteger<Base> operator%(const BigInteger<Base>&) const;
    // Métodos extra
    BigInteger<Base> mcd(BigInteger<Base> a, BigInteger<Base> b);
    bool isZero();
    // Getter
    BigUnsigned<Base> GetNumber() const { return number_; }
    bool GetSigno() const { return sign_; }
    BigUnsigned<Base> GetZero() const { return BigUnsigned<Base>((const unsigned char*)"0"); }
    // Setter
    void SetInmediato(int n) { number_ = BigUnsigned<Base>(n); }
    void SetSigno(bool signo) { sign_ = signo; }
    // // Métodos virtuales
    // BigNumber<Base>* add(const BigNumber<Base>&) const override;
    // BigNumber<Base>* subtract(const BigNumber<Base>&) const override;
    // BigNumber<Base>* multiply(const BigNumber<Base>&) const override;
    // BigNumber<Base>* divide(const BigNumber<Base>&) const override;
    // // Conversión a otros tipos
    // operator BigRational<Base>() const override;
    // operator BigUnsigned<Base>() const override;
    // // Métodos de entrada/salida
    // std::ostream& write(std::ostream&) const override;
    // std::istream& read(std::istream&) override;
  private:
    BigUnsigned<Base> number_;
    bool sign_; // true si es negativo, false si es positivo
};

template <>
class BigInteger<2> {
  public:
    // Constructores
    BigInteger(int n = 0);
    BigInteger(const BigUnsigned<2>&);
    BigInteger(std::string str);
    BigInteger(const BigInteger<2>&); // Constructor de copia
    // Sobrecarga de operadores
    BigInteger<2>& operator=(const BigInteger<2>& number_param);
    // Inserción/Extracción
    friend std::ostream& operator<<(std::ostream& os, const BigInteger<2>& number_param);
    friend std::istream& operator>>(std::istream& is, BigInteger<2>& number_param);
    // Comparación
    bool operator==(const BigInteger<2>& number_param) const;
    friend bool operator<(const BigInteger<2>& number_param1, const BigInteger<2>& number_param2);
    // Incremento/Decremento
    BigInteger<2>& operator++(); // Pre-incremento
    BigInteger<2> operator++(int); // Post-incremento
    BigInteger<2>& operator--(); // Pre-decremento
    BigInteger<2> operator--(int); // Post-decremento
    // Operadores aritméticos
    friend BigInteger<2> operator+(const BigInteger<2>&, const BigInteger<2>&);
    BigInteger<2> operator-(const BigInteger<2>&) const;
    BigInteger<2> operator*(const BigInteger<2>&) const;
    friend BigInteger<2> operator/(const BigInteger<2>&, const BigInteger<2>&);
    BigInteger<2> operator%(const BigInteger<2>&) const;
    // Métodos extra
    BigInteger<2> mcd(BigInteger<2> a, BigInteger<2> b);
    bool isZero();
    // Getter
    BigUnsigned<2> GetNumber() const { return number_; }
    bool GetSigno() const { return sign_; }
    BigUnsigned<2> GetZero() const { return BigUnsigned<2>((const unsigned char*)"0"); }
    // Setter
    void SetInmediato(int n) { number_ = BigUnsigned<2>(n); }
    void SetSigno(bool signo) { sign_ = signo; }
  private:
    BigUnsigned<2> number_;
    bool sign_; // true si es negativo, false si es positivo
};

// Se incluye `BigRational.h` después para evitar dependencia circular
#include "BigRational.h"

/// @brief Constructor a partir de un número entero
/// @param n
template <unsigned char Base>
BigInteger<Base>::BigInteger(int n) {
  if (n == 0) {
    number_ = BigUnsigned<Base>(n = 0);
    sign_ = false;
  }
  else {
    if (n < 0) {
      sign_ = true;
      n = -n;
    }
    else {
      sign_ = false;
    }
    number_ = BigUnsigned<Base>(n);
  }
}

/// @brief Constructor a partir de un BigUnsigned
/// @param number_param
template <unsigned char Base>
BigInteger<Base>::BigInteger(const BigUnsigned<Base>& number_param) {
  number_ = number_param;
  sign_ = false;
}

/// @brief Constructor de copia
/// @param copy
template <unsigned char Base>
BigInteger<Base>::BigInteger(const BigInteger<Base>& copy) : number_(copy.number_), sign_(copy.sign_) {}

/// @brief Sobrecarga de operador de copia
/// @param number_param
/// @return number_result
template <unsigned char Base>
BigInteger<Base>& BigInteger<Base>::operator=(const BigInteger<Base>& number_param) {
  if (this != &number_param) {
    number_ = number_param.number_;
    sign_ = number_param.sign_;
  }
  return *this;
}

template <unsigned char Base>
BigInteger<Base>::BigInteger(std::string str) {
  if (str[0] == '-') {
    sign_ = true;
    str = str.substr(1);
  }
  else {
    sign_ = false;
  }
  number_ = BigUnsigned<Base>((const unsigned char*)str.c_str());
}

/// @brief Sobrecarga de operador de inserción
/// @param os
/// @param number_param
/// @return os
template <unsigned char B>
std::ostream& operator<<(std::ostream& os, const BigInteger<B>& number_param) {
  if (number_param.sign_) {
    os << "-";
  }
  os << number_param.number_;
  return os;
}

/// @brief Sobrecarga de operador de extracción
/// @param is
/// @param number_param
/// @return is
template <unsigned char B>
std::istream& operator>>(std::istream& is, BigInteger<B>& number_param) {
  int user_number;
  is >> user_number;
  if (user_number < 0) {
    number_param.sign_ = true;
    user_number = -user_number;
  }
  else {
    number_param.sign_ = false;
  }
  number_param.number_ = BigUnsigned(user_number);
  return is;
}

/// @brief
/// @param number_param
/// @return
template <unsigned char Base>
bool BigInteger<Base>::operator==(const BigInteger<Base>& number_param) const {
  return (sign_ == number_param.sign_) && (number_ == number_param.number_);
}

/// @brief
/// @param number_param1
/// @param number_param2
/// @return
template <unsigned char Base>
bool operator<(const BigInteger<Base>& number_param1, const BigInteger<Base>& number_param2) {
  if (number_param1.sign_ && !number_param2.sign_) {
    return true;
  }
  else if (!number_param1.sign_ && number_param2.sign_) {
    return false;
  }
  else if (number_param1.sign_ && number_param2.sign_) {
    return number_param2.number_ < number_param1.number_;
  }
  else {
    return number_param1.number_ < number_param2.number_;
  }
}

/// @brief
/// @return
template <unsigned char Base>
BigInteger<Base>& BigInteger<Base>::operator++() {
  *this = *this + 1;
  return *this;
}

/// @brief
/// @return
template <unsigned char Base>
BigInteger<Base> BigInteger<Base>::operator++(int) {
  BigInteger temp = *this;
  *this = *this + 1;
  return temp;
}

/// @brief
/// @return
template <unsigned char Base>
BigInteger<Base>& BigInteger<Base>::operator--() {
  *this = *this - 1;
  return *this;
}

/// @brief
/// @return
template <unsigned char Base>
BigInteger<Base> BigInteger<Base>::operator--(int) {
  BigInteger temp = *this;
  *this = *this - 1;
  return temp;
}

/// @brief
/// @param number_param1
/// @param number_param2
/// @return
template <unsigned char B>
BigInteger<B> operator+(const BigInteger<B>& number_param1, const BigInteger<B>& number_param2) {
  BigInteger<B> number_result;
  if (number_param1.sign_ == number_param2.sign_) {
    // Ambos números tienen el mismo signo
    number_result.number_ = number_param1.number_ + number_param2.number_;
    number_result.sign_ = number_param1.sign_;
  } 
  else {
    // Los números tienen signos diferentes
    if (number_param1.number_ < number_param2.number_) {
      number_result.number_ = number_param2.number_ - number_param1.number_;
      number_result.sign_ = number_param2.sign_;
    } else {
      number_result.number_ = number_param1.number_ - number_param2.number_;
      number_result.sign_ = number_param1.sign_;
    }
  }
  return number_result;
}

/// @brief
/// @param number_param
/// @return
template <unsigned char Base>
BigInteger<Base> BigInteger<Base>::operator-(const BigInteger<Base>& number_param) const {
  BigInteger number_result;
  if (sign_ == number_param.sign_) {
    if (number_ < number_param.number_) {
      number_result.number_ = number_param.number_ - number_;
      number_result.sign_ = !sign_;
    }
    else {
      number_result.number_ = number_ - number_param.number_;
      number_result.sign_ = sign_;
    }
  }
  else {
    number_result.number_ = number_ + number_param.number_;
    number_result.sign_ = sign_;
  }
  return number_result;
}

/// @brief
/// @param number_param
/// @return
template <unsigned char Base>
BigInteger<Base> BigInteger<Base>::operator*(const BigInteger<Base>& number_param) const {
  BigInteger number_result;
  number_result.number_ = number_ * number_param.number_;
  number_result.sign_ = sign_ != number_param.sign_;
  return number_result;
}

/// @brief
/// @param number_param1
/// @param number_param2
/// @return
template <unsigned char B>
BigInteger<B> operator/(const BigInteger<B>& number_param1, const BigInteger<B>& number_param2) {
  BigInteger<B> number_result;
  number_result.number_ = number_param1.number_ / number_param2.number_;
  number_result.sign_ = number_param1.sign_ != number_param2.sign_;
  return number_result;
}

/// @brief
/// @param number_param
/// @return
template <unsigned char Base>
BigInteger<Base> BigInteger<Base>::operator%(const BigInteger<Base>& number_param) const {
  BigInteger number_result;
  number_result.number_ = number_ % number_param.number_;
  number_result.sign_ = false;
  return number_result;
}

/// @brief Algoritmo RECURSIVO de Euclides para calcular el máximo común divisor
/// @param a
/// @param b
/// @return mcd
template <unsigned char Base>
BigInteger<Base> BigInteger<Base>::mcd(BigInteger<Base> a, BigInteger<Base> b) {
  // mcd(a,0) = a
  // mcd(a,b) = mcd(b,a%b)
  if (b.isZero()) {
    return a;
  }
  else {
    BigInteger resto = a % b;
    return mcd(b, resto);
  }
}

/// @brief Comprueba si el número es 0 
/// @return true si es 0, false si no lo es 
template <unsigned char Base>
bool BigInteger<Base>::isZero() {
  std::vector<unsigned char> zero_vec = {0};
  return number_.getDigitsVec() == zero_vec;
}

// Metodos virtuales

// /// @brief
// /// @param number_param
// /// @return
// template <unsigned char Base>
// BigNumber<Base>* BigInteger<Base>::add(const BigNumber<Base>& number_param) const {
//   const BigInteger<Base>& number = dynamic_cast<const BigInteger<Base>&>(number_param);
//   BigInteger<Base>* number_result = new BigInteger<Base>;
//   if (sign_ == number.sign_) {
//     number_result->number_ = number_ + number.number_;
//     number_result->sign_ = sign_;
//   }
//   else {
//     if (number_ < number.number_) {
//       number_result->number_ = number.number_ - number_;
//       number_result->sign_ = !sign_;
//     }
//     else {
//       number_result->number_ = number_ - number.number_;
//       number_result->sign_ = sign_;
//     }
//   }
//   return number_result;
// }
// 
// /// @brief
// /// @param number_param
// /// @return
// template <unsigned char Base>
// BigNumber<Base>* BigInteger<Base>::subtract(const BigNumber<Base>& number_param) const {
//   const BigInteger<Base>& number = dynamic_cast<const BigInteger<Base>&>(number_param);
//   BigInteger<Base>* number_result = new BigInteger<Base>;
//   if (sign_ == number.sign_) {
//     if (number_ < number.number_) {
//       number_result->number_ = number.number_ - number_;
//       number_result->sign_ = !sign_;
//     }
//     else {
//       number_result->number_ = number_ - number.number_;
//       number_result->sign_ = sign_;
//     }
//   }
//   else {
//     number_result->number_ = number_ + number.number_;
//     number_result->sign_ = sign_;
//   }
//   return number_result;
// }
// 
// /// @brief
// /// @param number_param
// /// @return
// template <unsigned char Base>
// BigNumber<Base>* BigInteger<Base>::multiply(const BigNumber<Base>& number_param) const {
//   const BigInteger<Base>& number = dynamic_cast<const BigInteger<Base>&>(number_param);
//   BigInteger<Base>* number_result = new BigInteger<Base>;
//   number_result->number_ = number_ * number.number_;
//   number_result->sign_ = sign_ != number.sign_;
//   return number_result;
// }
// 
// /// @brief
// /// @param number_param
// /// @return
// template <unsigned char Base>
// BigNumber<Base>* BigInteger<Base>::divide(const BigNumber<Base>& number_param) const {
//   const BigInteger<Base>& number = dynamic_cast<const BigInteger<Base>&>(number_param);
//   BigInteger<Base>* number_result = new BigInteger<Base>;
//   number_result->number_ = number_ / number.number_;
//   number_result->sign_ = sign_ != number.sign_;
//   return number_result;
// }
// 
// /// @brief Conversión a BigRational
// /// @return BigRational
// template <unsigned char Base>
// BigInteger<Base>::operator BigRational<Base>() const {
//   return BigRational<Base>(BigInteger<Base>(*this), BigUnsigned<Base>(1));
// }
// 
// /// @brief Conversión a BigUnsigned
// /// @return BigUnsigned
// template <unsigned char Base>
// BigInteger<Base>::operator BigUnsigned<Base>() const {
//   return BigUnsigned<Base>(this->toString());
// }
// 
// /// @brief
// /// @param os
// /// @return
// template <unsigned char Base>
// std::ostream& BigInteger<Base>::write(std::ostream& os) const {
//   if (sign_) {
//     os << "-";
//   }
//   os << number_;
//   return os;
// }
// 
// /// @brief
// /// @param is
// /// @return
// template <unsigned char Base>
// std::istream& BigInteger<Base>::read(std::istream& is) {
//   std::string str;
//   is >> str;
//   if (str[0] == '-') {
//     sign_ = true;
//     str = str.substr(1);
//   }
//   else {
//     sign_ = false;
//   }
//   number_ = BigUnsigned<Base>((const unsigned char*)str.c_str());
//   return is;
// }


//-------------------ESPECIALIZACIÓN PARA BASE 2-------------------

/// @brief Constructor a partir de un número entero
/// @param n
BigInteger<2>::BigInteger(int n) {
  if (n == 0) {
    number_ = BigUnsigned<2>(n = 0);
    sign_ = false;
  }
  else {
    if (n < 0) {
      sign_ = true;
      n = -n;
    }
    else {
      sign_ = false;
    }
    number_ = BigUnsigned<2>(n);
  }
}

/// @brief Constructor a partir de un BigUnsigned
/// @param number_param
BigInteger<2>::BigInteger(const BigUnsigned<2>& number_param) {
  number_ = number_param;
  sign_ = false;
}

/// @brief Constructor de copia
/// @param copy
BigInteger<2>::BigInteger(const BigInteger<2>& copy) : number_(copy.number_), sign_(copy.sign_) {}

/// @brief Sobrecarga de operador de copia
/// @param number_param
/// @return number_result
BigInteger<2>& BigInteger<2>::operator=(const BigInteger<2>& number_param) {
  if (this != &number_param) {
    number_ = number_param.number_;
    sign_ = number_param.sign_;
  }
  return *this;
}

BigInteger<2>::BigInteger(std::string str) {
  if (str[0] == '-') {
    sign_ = true;
    str = str.substr(1);
  }
  else {
    sign_ = false;
  }
  number_ = BigUnsigned<2>((const unsigned char*)str.c_str());
}

/// @brief Sobrecarga de operador de inserción
/// @param os
/// @param number_param
/// @return os
std::ostream& operator<<(std::ostream& os, const BigInteger<2>& number_param) {
  if (number_param.sign_) {
    os << "-";
  }
  os << number_param.number_;
  return os;
}

/// @brief Sobrecarga de operador de extracción
/// @param is
/// @param number_param
/// @return is
std::istream& operator>>(std::istream& is, BigInteger<2>& number_param) {
  int user_number;
  is >> user_number;
  if (user_number < 0) {
    number_param.sign_ = true;
    user_number = -user_number;
  }
  else {
    number_param.sign_ = false;
  }
  number_param.number_ = BigUnsigned<2>(user_number);
  return is;
}

/// @brief
/// @param number_param
/// @return
bool BigInteger<2>::operator==(const BigInteger<2>& number_param) const {
  return (sign_ == number_param.sign_) && (number_ == number_param.number_);
}

/// @brief
/// @param number_param1
/// @param number_param2
/// @return
bool operator<(const BigInteger<2>& number_param1, const BigInteger<2>& number_param2) {
  if (number_param1.sign_ && !number_param2.sign_) {
    return true;
  }
  else if (!number_param1.sign_ && number_param2.sign_) {
    return false;
  }
  else if (number_param1.sign_ && number_param2.sign_) {
    return number_param2.number_ < number_param1.number_;
  }
  else {
    return number_param1.number_ < number_param2.number_;
  }
}

/// @brief
/// @return
BigInteger<2>& BigInteger<2>::operator++() {
  *this = *this + 1;
  return *this;
}

/// @brief
/// @return
BigInteger<2> BigInteger<2>::operator++(int) {
  BigInteger temp = *this;
  *this = *this + 1;
  return temp;
}

/// @brief
/// @return
BigInteger<2>& BigInteger<2>::operator--() {
  *this = *this - 1;
  return *this;
}

/// @brief
/// @return
BigInteger<2> BigInteger<2>::operator--(int) {
  BigInteger temp = *this;
  *this = *this - 1;
  return temp;
}

/// @brief
/// @param number_param1
/// @param number_param2
/// @return
BigInteger<2> operator+(const BigInteger<2>& number_param1, const BigInteger<2>& number_param2) {
  BigInteger<2> number_result;
  if (number_param1.sign_ == number_param2.sign_) {
    // Ambos números tienen el mismo signo
    number_result.number_ = number_param1.number_ + number_param2.number_;
    number_result.sign_ = number_param1.sign_;
  } 
  else {
    // Los números tienen signos diferentes
    if (number_param1.number_ < number_param2.number_) {
      number_result.number_ = number_param2.number_ - number_param1.number_;
      number_result.sign_ = number_param2.sign_;
    } else {
      number_result.number_ = number_param1.number_ - number_param2.number_;
      number_result.sign_ = number_param1.sign_;
    }
  }
  return number_result;
}

/// @brief
/// @param number_param
/// @return
BigInteger<2> BigInteger<2>::operator-(const BigInteger<2>& number_param) const {
  BigInteger<2> number_result;
  if (sign_ == number_param.sign_) {
    if (number_ < number_param.number_) {
      number_result.number_ = number_param.number_ - number_;
      number_result.sign_ = !sign_;
    }
    else {
      number_result.number_ = number_ - number_param.number_;
      number_result.sign_ = sign_;
    }
  }
  else {
    number_result.number_ = number_ + number_param.number_;
    number_result.sign_ = sign_;
  }
  return number_result;
}

/// @brief
/// @param number_param
/// @return
BigInteger<2> BigInteger<2>::operator*(const BigInteger<2>& number_param) const {
  BigInteger<2> number_result;
  number_result.number_ = number_ * number_param.number_;
  number_result.sign_ = sign_ != number_param.sign_;
  return number_result;
}

/// @brief
/// @param number_param1
/// @param number_param2
/// @return
BigInteger<2> operator/(const BigInteger<2>& number_param1, const BigInteger<2>& number_param2) {
  BigInteger<2> number_result;
  number_result.number_ = number_param1.number_ / number_param2.number_;
  number_result.sign_ = number_param1.sign_ != number_param2.sign_;
  return number_result;
}

/// @brief
/// @param number_param
/// @return
BigInteger<2> BigInteger<2>::operator%(const BigInteger<2>& number_param) const {
  BigInteger<2> number_result;
  number_result.number_ = number_ % number_param.number_;
  number_result.sign_ = false;
  return number_result;
}

/// @brief Algoritmo RECURSIVO de Euclides para calcular el máximo común divisor
/// @param a
/// @param b
/// @return mcd
BigInteger<2> BigInteger<2>::mcd(BigInteger<2> a, BigInteger<2> b) {
  // mcd(a,0) = a
  // mcd(a,b) = mcd(b,a%b)
  if (b.isZero()) {
    return a;
  }
  else {
    BigInteger<2> resto = a % b;
    return mcd(b, resto);
  }
}

/// @brief Comprueba si el número es 0
/// @return true si es 0, false si no lo es
bool BigInteger<2>::isZero() {
  std::vector<unsigned char> zero_vec = {0};
  return number_.getDigitsVec() == zero_vec;
}

#endif