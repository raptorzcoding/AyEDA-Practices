#include "BigRational.h"



// Constructor
template <unsigned char Base>
BigRational<Base>::BigRational(const BigInteger<Base>& entero, const BigUnsigned<Base>& natural) {
  numerador_ = entero;
  denominador_ = natural;
}


// Extracción 
template <unsigned char B>
std::istream& operator>>(std::istream& in, BigRational<B>& racional) {
  return in;
}


// Inserción
template <unsigned char B>
std::ostream& operator<<(std::ostream& os, const BigRational<B>& num) {
  BigRational<B> aux = num;
  // if (B != 2) aux.Simplificar();
  os << aux.GetNumerador() << " / " << aux.GetDenominador();
  return os;
}


// Comparación
template <unsigned char Base>
bool BigRational<Base>::operator==(const BigRational<Base>& num) const {
  if((this->GetNumerador().GetNumber() == num.GetNumerador().GetNumber())
  && (this->GetNumerador().GetSigno() == num.GetNumerador().GetSigno()) 
  && (this->GetDenominador() == num.GetDenominador())) {
    return true;
  }
  return false;
}



// SmallerThan
template <unsigned char Base>
bool operator<(const BigRational<Base>& primero, const BigRational<Base>& segundo) {
    // Convertimos las fracciones a un denominador común
    BigInteger<Base> denominador_comun = primero.GetDenominador() * segundo.GetDenominador();
    BigInteger<Base> numerador_primero = primero.GetNumerador() * segundo.GetDenominador();
    BigInteger<Base> numerador_segundo = segundo.GetNumerador() * primero.GetDenominador();
    
    // Comparamos los numeradores con el mismo denominador común
    if (numerador_primero < numerador_segundo) {
        return true;  // El primero es menor
    } else {
        return false;  // El primero no es menor
    }
}



// Resta
template <unsigned char Base>
BigRational<Base> BigRational<Base>::operator-(const BigRational<Base>& num) const {
  // a/b - c/d == ((a*d) - (b*c)) / (b*d)
  BigInteger<Base> a = this->GetNumerador();
  BigInteger<Base> b(this->GetDenominador());
  BigInteger<Base> c = num.GetNumerador();
  BigInteger<Base> d(num.GetDenominador());
  // (a*d)
  BigInteger<Base> primer = a * d;
  // (b*c)
  BigInteger<Base> segundo = b * c;
  // (b*d)
  BigInteger<Base> tercero = b * d;
  BigRational<Base> resultado;
  resultado.SetNumerador((primer - segundo));
  resultado.SetDenominador(tercero.GetNumber());
  return resultado;
}



// Suma
template <unsigned char Base>
BigRational<Base> BigRational<Base>::operator+(const BigRational<Base>& num) const {
  // a/b + c/d == ((a*d) + (b*c)) / (b*d)
  BigInteger<Base> a = this->GetNumerador();
  BigInteger<Base> b(this->GetDenominador());
  BigInteger<Base> c = num.GetNumerador();
  BigInteger<Base> d(num.GetDenominador());
  // (a*d)
  BigInteger<Base> primer = a * d;
  // (b*c)
  BigInteger<Base> segundo = b * c;
  // (b*d)
  BigInteger<Base> tercero = b * d;
  BigRational<Base> resultado;
  resultado.SetNumerador((primer + segundo));
  resultado.SetDenominador(tercero.GetNumber());
  return resultado;
}


// División
template <unsigned char Base>
BigRational<Base> BigRational<Base>::operator/(const BigRational<Base>& num) const {
  // a/b + c/d == (a*d) / (b*c)
  BigInteger<Base> a = this->GetNumerador();
  BigInteger<Base> b(this->GetDenominador());
  BigInteger<Base> c = num.GetNumerador();
  BigInteger<Base> d(num.GetDenominador());
  // (a*d)
  BigInteger<Base> primer = a * d;
  // (b*c)
  BigInteger<Base> segundo = b * c;
  if(primer.GetSigno() != segundo.GetSigno()) {
    primer.SetSigno(false);
    segundo.SetSigno(true);
  }
  else {
    primer.SetSigno(true);
    segundo.SetSigno(true);
  }
  BigRational<Base> resultado;
  resultado.SetNumerador(primer);
  resultado.SetDenominador(segundo.GetNumber());
  return resultado;
}


// Multiplicación
template <unsigned char Base>
BigRational<Base> BigRational<Base>::operator*(const BigRational<Base>& num) const {
  // a/b + c/d == (a*c) / (b*d)
  BigInteger<Base> a = this->GetNumerador();
  BigInteger<Base> b(this->GetDenominador());
  BigInteger<Base> c = num.GetNumerador();
  BigInteger<Base> d(num.GetDenominador());
  // (a*c) 
  BigInteger<Base> primer = a * c;
  // (b*d)
  BigInteger<Base> segundo = b * d;
  BigRational<Base> resultado;
  resultado.SetNumerador(primer);
  resultado.SetDenominador(segundo.GetNumber());
  return resultado;
}


// Solve
template <unsigned char Base>
BigInteger<Base> BigRational<Base>::GetResult() const {
  BigInteger<Base> aux(this->GetNumerador().GetNumber() / this->GetDenominador());
  if(this->GetNumerador().GetSigno() == false) {
    aux.SetSigno(false);
  }
  return aux;
}


// Simplificación
template <unsigned char Base>
BigRational<Base> BigRational<Base>::Simplificar() {
  BigInteger<Base> numerador = this->GetNumerador();
  BigUnsigned<Base> denominador = this->GetDenominador();

  BigUnsigned<Base> dos_aux;
  dos_aux.SetInmediato(2);
  BigInteger<Base> dos(dos_aux);

  BigUnsigned<Base> uno_aux;
  uno_aux.SetInmediato(1);
  BigInteger<Base> uno(uno_aux);


  for(BigInteger<Base> i = dos; i.GetNumber() < numerador.GetNumber(); i = i + uno) {
    while(((numerador.GetNumber() % i.GetNumber()) == denominador.GetZero()) &&
           ((denominador % i.GetNumber()) == denominador.GetZero())) {
      // Si ambos números son divisibles por i, se dividen
      numerador = numerador / i;
      denominador = denominador / i.GetNumber();
    }
  }


  if(numerador.GetNumber() == denominador) {
    denominador.SetInmediato(1);
    if(numerador.GetSigno() == false) {
      uno.SetSigno(false);
      numerador = uno;
    }
    else {
      numerador = uno;
    }
  }
  this->SetNumerador(numerador);
  this->SetDenominador(denominador);
  return *this;
}

