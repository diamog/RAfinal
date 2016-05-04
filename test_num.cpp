#include <iostream>
#include <fstream>
#include <cmath>
#include <cassert>
#include "my_num.h"

int main(int argc, char* argv[]) {


  std::string filename = "test_nums.txt";
  std::ofstream out_str(filename.c_str());
  s_t num1 = pow(2,39)-1;
  MyNum n1(num1);
  n1.write(out_str);
  MyNum n2(pow(2,39));
  n2.write(out_str);
  out_str.close();

  assert(n2<=n1);
  std::cout<<"Reading those back in\n";
  std::ifstream in_str(filename.c_str());
  while (n1.read(in_str)) {
    std::cout<<"NUM:\n";
    std::cout<<n1.size()<<' '<<n1.getNum()<<'\n';
  }
  
  if (argc>1) {
    std::ifstream in_str(argv[1]);
    s_t past=0;
    while (n1.read(in_str)) {
      if (n1.getNum()<past) {
        std::cout<<n1.getNum()<<" Out of order\n";
        return 0;
      }
      else
        past = n1.getNum();
    }
    std::cout<<"Rest is in order\n";
  }
}
