#ifndef __MY_NUM_H__
#define __MY_NUM_H__
#include <vector>
#include <iostream>
typedef unsigned long long int s_t;

class MyNum {
 public:
  MyNum();
  MyNum(s_t);
  unsigned int size() const  {return s;}
  const char &operator[](int i) const;

  s_t getNum() const;
  void setNum(s_t);
  bool read(std::istream&);
  void write(std::ostream&);


 private:
  char value[6];
  char s;
};

inline bool operator<=(const MyNum& n1, const MyNum& n2) {
  if (n1.size()>n2.size())
    return false;
  if (n1.size()<n2.size()) 
    return true;
  for (unsigned int i=n1.size();i>0;i--) {
    if (n2[i-1]<n1[i-1])
      return false;
  }
  return true;
}

char checkSize(s_t);

#endif
