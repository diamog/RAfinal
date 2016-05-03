#ifndef __MY_NUM_H__
#define __MY_NUM_H__
#include <vector>
#include <iostream>
typedef unsigned long long int s_t;

class MyNum {
 public:
  MyNum();
  MyNum(s_t);
  unsigned int size() const  {return value.size();}
  const char &operator[](int i) const;

  s_t getNum() const;
  void setNum(s_t);
  bool read(std::istream&);
  void write(std::ostream&);


 private:
  std::vector<char> value;
};

inline bool operator<=(const MyNum& n1, const MyNum& n2) {
  if (n1.size()>n2.size())
    return false;
  if (n1.size()<n2.size()) 
    return true;
  for (unsigned int i=n1.size();i>0;i--) {
    if (n2[i]<n1[i])
      return false;
  }
  return true;
}

#endif
