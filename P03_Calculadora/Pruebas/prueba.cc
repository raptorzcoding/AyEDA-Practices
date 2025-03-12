#include <iostream>
#include <vector>

int main() {
  std::vector<unsigned char> digits_vec1 = {2, 0, 0, 4};
  std::vector<unsigned char> digits_vec2 = {3, 2, 1};
  // Sumar teniendo en cuenta que los vectores no tienen la misma longitud
  std::vector<unsigned char> digits_vec_result;
  int carry = 0;
  for (int i = 0; i < digits_vec1.size(); i++) {
    int sum = carry;
    if (i < digits_vec1.size()) {
      sum += digits_vec1[i];
    }
    if (i < digits_vec2.size()) {
      sum += digits_vec2[i];
    }
    if (sum >= 10) {
      sum -= 10;
      carry = 1;
    }
    else {
      carry = 0;
    }
    digits_vec_result.push_back(sum);
  }
  // Imprimir el resultado
  for (int i = digits_vec_result.size() - 1; i >= 0; i--) {
    std::cout << static_cast<int>(digits_vec_result[i]) << " ";
  }
  std::cout << std::endl;
  return 0;
}