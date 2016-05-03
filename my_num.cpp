#include "my_num.h"
#include <cmath>
#include <iostream>
#include <string>
MyNum::MyNum() {
}

MyNum::MyNum(s_t num) {
  setNum(num);
}

const char &MyNum::operator[](int i) const{
  return value[i];
}

s_t MyNum::getNum() const {
  s_t acc=0;
  for (unsigned int i=0;i<s;i++) 
    acc+=(s_t)ceil(pow(256,i))*value[i];
  return acc;
}
void MyNum::setNum(s_t num) {
  s = checkSize(num);
  int i=0;
  while (num>0) {
    value[i] = (char)(num%256);
    num/=256;
    i++;
  }
}

bool MyNum::read(std::istream& in_str) {
  std::string a="";
  getline(in_str,a,'\n');
  if (a=="")
    return false;
  s = a.size();
  for (unsigned int i=0;i<a.size();i++) {
    value[i] = a[i];
  }
  return true;
}

void MyNum::write(std::ostream& out_str) {
  for (unsigned int i=0;i<s;i++) {
    out_str<<value[i];
  }
  out_str<<std::endl;
}

char checkSize(s_t num) {
  s_t val = 256;
  int i=1;
  while(val>num) {
    val*=256;
    i++;
  }
  return i;
}
