#include <cassert>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include "my_num.h"
#include <ctime>

int main(int argc,char* argv[]) {
  srand(time(NULL));
  assert(argc>2);
  std::ofstream out_str(argv[1]);
  s_t N = (s_t)ceil(pow(2,atoi(argv[2])));
  double alpha = atof(argv[3]);
  s_t N_sorted = (s_t)ceil(alpha*N);
  s_t N_unsorted = N-N_sorted;
  int* indices = new int[N_unsorted];
  for (s_t i=0;i<N_unsorted;i++) {
    indices[i] = (rand()%(N_sorted+1));
  }
  std::sort(indices,indices+N_unsorted);
  s_t cur=0;
  for (s_t i=0;i<N_sorted;i++) {
    if (!(i%(N_sorted/10)))
      std::cout<<"Another 10%\n";
    while (cur<N_unsorted&&indices[cur]<i) {
      MyNum num(N_sorted);
      num.write(out_str);
      cur++;
    }
    MyNum num(i);
    num.write(out_str);
  }
  while (cur<N_unsorted) {
    MyNum num(0);
    num.write(out_str);
    cur++;
  }
  delete [] indices;
  return 0;
}
