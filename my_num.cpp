#include "my_num.h"
#include <cmath>
#include <iostream>
#include <string>
MyNum::MyNum() {s=0;}

MyNum::MyNum(s_t num) {
  s=0;
  setNum(num);
}

const store_t &MyNum::operator[](int i) const{
  return value[i];
}

s_t MyNum::getNum() const {
  s_t acc=0;
  for (unsigned short i=0;i<s;i++) 
    acc+=(s_t)ceil(pow(65536,i))*value[i];
  return acc;
}

void MyNum::setNum(s_t num) {
  s = checkSize(num);
  unsigned short i=0;
  while (num>0) {
    value[i] = (num%65536);
    num/=65536;
    i++;
  }
}

bool MyNum::read(std::istream& in_str) {
  in_str>>s;
  if (in_str.eof()) {
    s=0;
    return false;
  }
  for (unsigned short i=0;i<s;i++) {
    in_str>>(value[i]);
  }
  return true;
}

void MyNum::write(std::ostream& out_str) {
  out_str<<s<<' ';
  for (unsigned short i=0;i<s;i++) {
    out_str<<value[i]<<' ';
  }
}

char checkSize(s_t num) {
  s_t val = 65536;
  int i=1;
  while(val<=num) {
    val*=65536;
    i++;
  }
  return i;
}
