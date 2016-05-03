#include <cassert>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include "my_num.h"

int main(int argc,char* argv[]) {
  srand(time(NULL));
  assert(argc>2);
  std::ofstream out_str(argv[1]);
  s_t N = pow(2,atoi(argv[2]));
  double alpha = atof(argv[3]);
  s_t N_sorted = ceil(alpha*N);
  s_t N_unsorted = N-N_sorted;
  s_t* indices = new s_t[N_unsorted];
  for (s_t i=0;i<N_unsorted;i++) {
    indices[i] = rand()%(N_sorted+1);
  }
  std::sort(indices,indices+N_unsorted);
  s_t cur=0;
  for (s_t i=0;i<N_sorted;i++) {
    while (cur<N_unsorted&&indices[cur]<i) {
      out_str<<N_sorted<<'\n';
      //      MyNum num(N_sorted);
      //      num.write(out_str);
      cur++;
    }
    out_str<<i<<'\n';
    //    MyNum num(i);
    //num.write(out_str);
  }
  while (cur<N_unsorted) {
    out_str<<0<<'\n';
    //    MyNum num(0);
    //    num.write(out_str);
    cur++;
  }
  delete [] indices;
  return 0;
}
