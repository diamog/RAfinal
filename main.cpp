#include <cassert>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <cmath>
#include <algorithm>
#include "my_num.h"
s_t nChoosek( s_t n, s_t k )
{
    if (k > n) return 0;
    if (k * 2 > n) k = n-k;
    if (k == 0) return 1;

    s_t result = n;
    for( s_t i = 2; i <= k; ++i ) {
        result *= (n-i+1);
        result /= i;
    }
    return result;
}
s_t myincreasingsseq(std::vector<store_t>& nums, std::vector<s_t>& indices) {
  std::vector<s_t> L;
  s_t max=1;
  s_t l = indices.size();
  for (unsigned int i=0;i<l;i++) {
    s_t temp = 1;
    for (unsigned int j=0;j<i;j++) {
      if (nums[indices[j]]<=nums[indices[i]])
        if (L[j]+1>temp)
          temp=L[j]+1;
    }
    if (temp>max)
      max=temp;
    L.push_back(temp);
  }
  return max;
}

bool testSubsequence(std::vector<store_t>& nums, s_t l, float alpha) {
  std::vector<s_t> indices;

  for (s_t i=0;i<l;i++) {
    indices.push_back(rand()%(nums.size()));
  }
  std::sort(indices.begin(),indices.end());
  s_t L = myincreasingsseq(nums,indices);
  return L>=ceil(alpha*l);
}


int main(int argc,char* argv[]) {
  srand(time(NULL));
  assert(argc>=3);

  //Input
  s_t N = pow(2,atoi(argv[1]));
  double alpha_in = atof(argv[2]);
  s_t N_sorted = ceil(alpha_in*N);
  s_t N_unsorted = N-N_sorted;

  //Create list of unsorted elements
  s_t* indices = new s_t[N_unsorted];
  for (s_t i=0;i<N_unsorted;i++) {
    indices[i] = rand()%(N_sorted+1);
  }
  std::sort(indices,indices+N_unsorted);

  //Create alpha_in sorted list
  std::vector<store_t> numbers;
  s_t cur=0;
  for (s_t i=0;i<N_sorted;i++) {
    while (cur<N_unsorted&&indices[cur]<i) {
      numbers.push_back((store_t)log(N_sorted)+1);
      cur++;
    }
    numbers.push_back((int)log(i+1));
  }
  while (cur<N_unsorted) {
    numbers.push_back(0);
    cur++;
  }
  delete [] indices;

  //continuously run tests until finished
  float alpha;
  int l;
  std::cout<<"Input l(0 to end): ";
  std::cin>>l;
  while (l!=0) {
    std::cout<<"Input alpha: ";
    std::cin>>alpha;
    
    //Calculate p*
    double pstar=0;
    std::clock_t start_ps = std::clock();
    for (s_t i =ceil(alpha*l);i<=l;i++) {
      pstar+=nChoosek(l,i)*pow(alpha,i)*pow(1-alpha,l-i);
    }
    std::cout<<"p* = "<<pstar<<'\n';
    std::cout<<"Computing p* took "<<(std::clock()-start_ps)/(double)CLOCKS_PER_SEC
             <<"seconds\n";

    //Run the test
    std::clock_t start_running = std::clock();
    unsigned int m = 100000;
    unsigned int worked=0;
    for (int i=0;i<m;i++) {
      worked+=testSubsequence(numbers,l,alpha);
    }
    double p = worked*1.0/m;
    std::cout<<"p = "<<p<<'\n';
    std::cout<<"p-p* = "<<p-pstar<<'\n';
    if (p>pstar) 
      std::cout<<"YES\n";
    else
      std::cout<<"NO\n";
    std::cout<<"Running algorithm took "<<(std::clock()-start_running)/(double)CLOCKS_PER_SEC<<"seconds\n";
  
    //refresh for another run
    std::cout<<"Input l(0 to end): ";
    std::cin>>l;
  }
  return 0;
}
