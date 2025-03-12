#ifndef BIGNUMBER_H
#define BIGNUMBER_H

#include <iostream>
#include <string>

// Forward Declarations para evitar dependencias circulares
template <unsigned char Base> class BigUnsigned;
template <unsigned char Base> class BigInteger;
template <unsigned char Base> class BigRational;

template <unsigned char Base>
class BigNumber {
public:
    virtual ~BigNumber() {}  // Destructor virtual

    // Métodos virtuales puros para las operaciones aritméticas
    virtual BigNumber<Base>* add(const BigNumber<Base>&) const = 0;
    virtual BigNumber<Base>* subtract(const BigNumber<Base>&) const = 0;
    virtual BigNumber<Base>* multiply(const BigNumber<Base>&) const = 0;
    virtual BigNumber<Base>* divide(const BigNumber<Base>&) const = 0;

    // Conversión a otros tipos
    virtual operator BigInteger<Base>() const = 0;
    virtual operator BigRational<Base>() const = 0;

    // Métodos de entrada/salida
    virtual std::ostream& write(std::ostream&) const = 0;
    virtual std::istream& read(std::istream&) = 0;
};


// Definición de operadores de flujo
template <unsigned char Base>
std::ostream& operator<<(std::ostream& os, const BigNumber<Base>& bn) {
    return bn.write(os);
}

template <unsigned char Base>
std::istream& operator>>(std::istream& is, BigNumber<Base>& bn) {
    return bn.read(is);
}

#endif // BIGNUMBER_H