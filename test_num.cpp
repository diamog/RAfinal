#include <iostream>
#include <fstream>
#include "my_num.h"

int main() {
  std::string filename = "test_nums.txt";
  std::ofstream out_str(filename.c_str());
  int num1 = 7;
  MyNum n1(num1);
  n1.write(out_str);
  std::cout<<n1.getNum()<<'\n';
  int num2 = 15;
  MyNum n2(num2);
  n2.write(out_str);
  std::cout<<n2.getNum()<<'\n';
  n2.read(std::cin);
  n2.write(out_str);
  std::cout<<n2.getNum()<<'\n';
  out_str.close();
  std::ifstream in_str(filename.c_str());
  while (n2.read(in_str)) {
    std::cout<<n2.getNum()<<'\n';
    n2.write(std::cout);
  }
}
