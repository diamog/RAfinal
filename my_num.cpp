#include "my_num.h"
#include <cmath>
MyNum::MyNum() {setNum(0);}

MyNum::MyNum(s_t num) {
  setNum(num);
}

const char &MyNum::operator[](int i) const{
  return value[i];
}

s_t MyNum::getNum() const {
  s_t acc=0;
  for (unsigned int i=0;i<value.size();i++) 
    acc+=pow(256,i)*value[i];
  return acc;
}
void MyNum::setNum(s_t num) {
  value.clear();
  while (num>0) {
    value.push_back((char)(num%256));
    num/=256;
  }
}

bool MyNum::read(std::istream& in_str) {
  value.clear();
  std::string a="";
  getline(in_str,a,'\n');
  if (a=="")
    return false;
  for (unsigned int i=0;i<a.size();i++) {
    value.push_back(a[i]);
  }
  return true;
}

void MyNum::write(std::ostream& out_str) {
  for (unsigned int i=0;i<value.size();i++) {
    out_str<<value[i];
  }
  out_str<<"\n";
}
